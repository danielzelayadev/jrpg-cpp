#include "TestScreen.h"
#include "TestInput.h"
#include "ScreenManager.h"

#include "MapParser.h"

void TestScreen::init()
{
   input = new TestInput(this);

   MapParser parser(sm->renderer);

   screenMap = parser.parse("Assets/Screens/Test/MapTest2.mp");

   mRenderer = new MapRenderer(screenMap);

}

void TestScreen::update()
{
}

void TestScreen::render()
{
   mRenderer->render(sm->renderer);
}

void TestScreen::dispose()
{
}
