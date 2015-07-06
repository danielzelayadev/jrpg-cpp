#ifndef PLAYER_H
#define PLAYER_H

#include "TMX/RectangleMapObject.h"

class Player
{
    public:
        Player(RectangleMapObject* obj);
        virtual ~Player();

    private:
        RectangleMapObject* playerObject;

        void loadMOProperties();
};

#endif // PLAYER_H
