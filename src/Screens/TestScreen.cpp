#include "TestScreen.h"
#include "TestInput.h"
#include "ScreenManager.h"

#include "TMX/TMXParser.h"

#include <iostream>

using namespace std;

void TestScreen::init()
{
   input = new TestInput(this);

   camera = {0, 0, sm->getWindowWidth(), sm->getWindowHeight()};

   TMXParser parser;

   screenMap = parser.parse("Assets/Screens/TMX Test/FirstMap.tmx");

   camMoveX = screenMap->getTileWidth();
   camMoveY = screenMap->getTileHeight();

   mRenderer = new MapRenderer(screenMap, sm->renderer, &camera);
}

void TestScreen::update()
{
   wrapCamera();
}

void TestScreen::render()
{
   mRenderer->render();
}

void TestScreen::dispose()
{
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
