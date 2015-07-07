#ifndef NPC_H
#define NPC_H

#include "Entity.h"

class NPC : public Entity
{
    public:
        NPC(SDL_Renderer* renderer, RectangleMapObject* obj):Entity(renderer, obj) {}
        virtual ~NPC();
};

#endif // NPC_H
