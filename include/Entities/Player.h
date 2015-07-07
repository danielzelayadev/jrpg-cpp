#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player : public Entity
{
    public:
        Player(SDL_Renderer* renderer, RectangleMapObject* obj):Entity(renderer, obj) {}
        virtual ~Player();

        void walk(int dir);
};

#endif // PLAYER_H
