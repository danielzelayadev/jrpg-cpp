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

    Player* player = context->player;

    context->cachedPlayerX = player->getX();
    context->cachedPlayerY = player->getY();

    if(keycode == SDLK_w)
       player->walk(WALK_UP);

    if(keycode == SDLK_a)
       player->walk(WALK_LEFT);

    if(keycode == SDLK_s)
       player->walk(WALK_DOWN);

    if(keycode == SDLK_d)
       player->walk(WALK_RIGHT);
}

void TestInput::keyUp(int keycode)
{
    if(keycode == SDLK_w || keycode == SDLK_a || keycode == SDLK_s || keycode == SDLK_d)
       context->player->getMovementAnim()->stop();
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
