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

   player = new Player(sm->renderer,
    (RectangleMapObject*) ((ObjectLayer*)screenMap->getLayer("objects"))->getObject("Player") );

   cachedPlayerX = player->getX();
   cachedPlayerY = player->getY();

   mRenderer = new MapRenderer(screenMap, sm->renderer, &camera);
}

void TestScreen::update()
{
   player->update();
   wrapCamera();
   mRenderer->update();

   if(collisions())
   { player->setX(cachedPlayerX); player->setY(cachedPlayerY); } //Deberia de haber una accion especifica para cada colision
}

void TestScreen::render()
{
   mRenderer->renderLayer(0);

   player->render(sm->renderer);

   mRenderer->renderLayer(2);
}

void TestScreen::dispose()
{
   delete player;
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

bool TestScreen::collisions()
{
    RectangleMapObject* playerMO = player->getMapObject();

    vector<MapObject*> objects =  ( (ObjectLayer*)screenMap->getLayer("objects") )->getObjects();

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
