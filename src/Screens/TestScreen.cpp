#include "TestScreen.h"
#include "TestInput.h"
#include "ScreenManager.h"

#include "TMX/TMXParser.h"

#include <sstream>

#include <iostream>

using namespace std;

void TestScreen::init()
{
   input = new TestInput(this);

   camera = {0, 0, sm->getWindowWidth(), sm->getWindowHeight()};

   TMXParser parser;

   screenMap = parser.parse("Assets/Screens/Test Screen/Maps/FirstMap.tmx");

   camMoveX = screenMap->getTileWidth();
   camMoveY = screenMap->getTileHeight();

   playerMO = (RectangleMapObject*)
                    ((ObjectLayer*)screenMap->getLayer("objects"))->getObject("Player");

   cachedPlayerX = playerMO->x;
   cachedPlayerY = playerMO->y;

   playerSS = IMG_LoadTexture(sm->renderer, playerMO->getProperty("Spritesheet").c_str());

   stringstream strm;

   strm << playerMO->getProperty("FrameW");
   strm >> frameW;

   strm.clear();

   strm << playerMO->getProperty("FrameH");
   strm >> frameH;

   strm.clear();

   strm << playerMO->getProperty("FramesX");
   strm >> framesX;

   strm.clear();

   strm << playerMO->getProperty("FramesY");
   strm >> framesY;

   frame = {0, 0, frameW, frameH};

   mRenderer = new MapRenderer(screenMap, sm->renderer, &camera);
}

void TestScreen::update()
{
   if(play)
     animate();

   else stopAnimations();

   wrapCamera();
   mRenderer->update();
   if(collisions())
    { playerMO->x = cachedPlayerX; playerMO->y = cachedPlayerY; } //Deberia de haber una accion especifica para cada colision
}

void TestScreen::render()
{
   mRenderer->renderLayer(0);

   SDL_Rect pr = {playerMO->x, playerMO->y, playerMO->width, playerMO->height};

   SDL_RenderCopy(sm->renderer, playerSS, &frame, &pr);

   mRenderer->renderLayer(2);
}

void TestScreen::dispose()
{
   SDL_DestroyTexture(playerSS);
   delete playerMO;
   delete input;
   delete mRenderer;
   delete screenMap;
}

void TestScreen::wrapCamera()
{
    if(camera.x + camera.w > screenMap->getWidth())
       camera.x -= camMoveX;

    if(camera.x < 0)
       camera.x = 0;

    if(camera.y + camera.h > screenMap->getHeight())
       camera.y -= camMoveY;

    if(camera.y < 0)
       camera.y = 0;
}

void TestScreen::animate()
{
   frame.y = frame.h * dir;

   if(frameCtr >= switchFrame)
   {
      frame.x += frame.w;

      if(frame.x >= (frame.w * framesX)) frame.x = 0;

      frameCtr = 0;
   }

   frameCtr++;
}

void TestScreen::stopAnimations()
{
    frameCtr = 0;
    frame.x = 0;
}

bool TestScreen::collisions()
{
    vector<MapObject*> objects = ((ObjectLayer*)screenMap->getLayer("objects"))->getObjects();

    for(int i = 0; i < objects.size(); i++)
    {
       if(objects[i] != playerMO && objects[i]->shapeType == RECTANGLE)
       {
           RectangleMapObject* rmo = (RectangleMapObject*)objects[i];

           if(playerMO->x < rmo->x + rmo->width && playerMO->x + playerMO->width > rmo->x &&
              playerMO->y < rmo->y + rmo->height && playerMO->y + playerMO->height > rmo->y)
                  return true;
       }
    }

    return false;
}
