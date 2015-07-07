#include "Player.h"

#include <sstream>
#include <iostream>

using namespace std;

Player::Player(SDL_Renderer* renderer, RectangleMapObject* obj)
{
    this->playerObject = obj;

    loadMOProperties();

    spritesheet = IMG_LoadTexture(renderer, spritesheetSrc.c_str());
}

void Player::loadMOProperties()
{
   stringstream strm;

   int framesX, framesY, frameW, frameH, animSpeed, animDir;

   strm << playerObject->getProperty("FrameW");
   strm >> frameW;

   strm.clear();

   strm << playerObject->getProperty("FrameH");
   strm >> frameH;

   strm.clear();

   strm << playerObject->getProperty("FramesX");
   strm >> framesX;

   strm.clear();

   strm << playerObject->getProperty("FramesY");
   strm >> framesY;

   strm.clear();

   strm << playerObject->getProperty("Animation Speed");
   strm >> animSpeed;

   strm.clear();

   strm << playerObject->getProperty("Animation Direction");
   strm >> animDir;

   strm.clear();

   movements = new Animation(framesX, framesY, frameW, frameH, animSpeed, animDir);

   strm << playerObject->getProperty("Speed");
   strm >> speed;

   spritesheetSrc = playerObject->getProperty("Spritesheet");
}

void Player::update()
{
   movements->animate();
}

void Player::render(SDL_Renderer* renderer)
{
   SDL_Rect frame = movements->getCurrentFrame();
   SDL_Rect rect = {playerObject->x, playerObject->y, playerObject->width, playerObject->height};

   SDL_RenderCopy(renderer, spritesheet, &frame, &rect);
}

void Player::walk(int dir)
{
   switch(dir)
   {
      case WALK_DOWN:
      playerObject->y += speed;
      break;
      case WALK_UP:
      playerObject->y -= speed;
      break;
      case WALK_LEFT:
      playerObject->x -= speed;
      break;
      case WALK_RIGHT:
      playerObject->x += speed;
      break;
   }

   if(!movements->isPlaying())
   {
      movements->setCurrentFrame(dir, 0);
      movements->play();
   }
}

Player::~Player()
{
   SDL_DestroyTexture(spritesheet);
   delete movements;
}
