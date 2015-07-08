#include "TestScreen.h"
#include "TestInput.h"
#include "ScreenManager.h"

#include "TMX/TMXParser.h"

#include <sstream>

#include <iostream>

#include <fstream>

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

   npc = new NPC(sm->renderer,
    (RectangleMapObject*) ((ObjectLayer*)screenMap->getLayer("objects"))->getObject("Enemy"));

   cachedPlayerX = player->getX();
   cachedPlayerY = player->getY();

   mRenderer = new MapRenderer(screenMap, sm->renderer, &camera);

   string diagDir = npc->getMapObject()->getProperty("Dialogue");
   string text = "";
   loadDialogue(diagDir, &text);

   int h = 150;
   int sp = 50;
   SDL_Rect r = {0, sm->getWindowHeight() - h, sm->getWindowWidth(), h};
   db = new DialogueBox(sm->renderer, text, r);
}

void TestScreen::update()
{
   player->update();
   npc->update();
   wrapCamera();
   mRenderer->update();

   if(collisions())
   { player->setX(cachedPlayerX); player->setY(cachedPlayerY); } //Deberia de haber una accion especifica para cada colision
}

void TestScreen::render()
{
   mRenderer->renderLayer(0);

   player->render(sm->renderer);
   npc->render(sm->renderer);

   mRenderer->renderLayer(2);

   db->render();
}

void TestScreen::dispose()
{
   delete player;
   delete npc;
   delete db;
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

void TestScreen::loadDialogue(string dir, string* text)
{
     fstream diagFile(dir);

     if(diagFile.is_open())
     {
         getline(diagFile, *text);
         diagFile.close();
     }
}
