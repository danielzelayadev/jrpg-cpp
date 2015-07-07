#ifndef ENTITY_H
#define ENTITY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Animation.h"

#include "TMX/RectangleMapObject.h"

enum WalkDirs
{
   WALK_DOWN, WALK_LEFT, WALK_RIGHT, WALK_UP
};

class Entity
{
    public:
        Entity(SDL_Renderer* renderer, RectangleMapObject* obj);
        virtual ~Entity();

        void update();
        void render(SDL_Renderer* renderer);

        int getX() { return object->x; }
        int getY() { return object->y; }
        void setX(int x) { object->x = x; }
        void setY(int y) { object->y = y; }

        RectangleMapObject* getMapObject() { return object; }
        Animation* getMovementAnim() { return movements; }

    protected:
        RectangleMapObject* object;
        SDL_Texture* spritesheet;

        Animation* movements;

        int speed;
        string spritesheetSrc;

        void loadMOProperties();
};

#endif // ENTITY_H
