#include "TestInput.h"

TestInput::TestInput(Screen* context)
{
    this->context = (TestScreen*)context;
}

void TestInput::keyDown(int keycode)
{
    if(keycode == SDLK_DOWN)
       context->camera.y += context->camMoveY;

    if(keycode == SDLK_UP)
       context->camera.y -= context->camMoveY;

    if(keycode == SDLK_RIGHT)
       context->camera.x += context->camMoveX;

    if(keycode == SDLK_LEFT)
       context->camera.x -= context->camMoveX;
}

void TestInput::keyUp(int keycode)
{
}

void TestInput::keyTyped(char character)
{
}

void TestInput::mouseMove(int x, int y, int xrel, int yrel)
{
}

void TestInput::mouseButtonDown(int x, int y, int clicks, int button)
{
}

void TestInput::mouseButtonUp(int x, int y, int clicks, int button)
{
}
