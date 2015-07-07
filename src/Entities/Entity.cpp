#include "Entity.h"

#include <sstream>

using std::stringstream;

Entity::Entity(SDL_Renderer* renderer, RectangleMapObject* obj)
{
    this->object = obj;

    loadMOProperties();

    spritesheet = IMG_LoadTexture(renderer, spritesheetSrc.c_str());
}

void Entity::loadMOProperties()
{
   stringstream strm;

   int framesX, framesY, frameW, frameH, animSpeed, animDir;

   strm << object->getProperty("FrameW");
   strm >> frameW;

   strm.clear();

   strm << object->getProperty("FrameH");
   strm >> frameH;

   strm.clear();

   strm << object->getProperty("FramesX");
   strm >> framesX;

   strm.clear();

   strm << object->getProperty("FramesY");
   strm >> framesY;

   strm.clear();

   strm << object->getProperty("Animation Speed");
   strm >> animSpeed;

   strm.clear();

   strm << object->getProperty("Animation Direction");
   strm >> animDir;

   strm.clear();

   movements = new Animation(framesX, framesY, frameW, frameH, animSpeed, animDir);

   strm << object->getProperty("Speed");
   strm >> speed;

   spritesheetSrc = object->getProperty("Spritesheet");
}

void Entity::update()
{
   movements->animate();
}

void Entity::render(SDL_Renderer* renderer)
{
   SDL_Rect frame = movements->getCurrentFrame();
   SDL_Rect rect = { object->x, object->y, frame.w, frame.h };

   SDL_RenderCopy(renderer, spritesheet, &frame, &rect);
}

Entity::~Entity()
{
   SDL_DestroyTexture(spritesheet);
   delete movements;
}
