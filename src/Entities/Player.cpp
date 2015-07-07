#include "Player.h"

void Player::walk(int dir)
{
   switch(dir)
   {
      case WALK_DOWN:
      object->y += speed;
      break;
      case WALK_UP:
      object->y -= speed;
      break;
      case WALK_LEFT:
      object->x -= speed;
      break;
      case WALK_RIGHT:
      object->x += speed;
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
