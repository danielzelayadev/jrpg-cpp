#ifndef PLAYER_H
#define PLAYER_H

#include "TMX/RectangleMapObject.h"
#include "Animation.h"

enum WalkDirs
{
   WALK_DOWN, WALK_LEFT, WALK_RIGHT, WALK_UP
};

class Player
{
    public:
        Player(RectangleMapObject* obj);
        virtual ~Player();

        void update();
        void render(SDL_Renderer* renderer);

        void walk(int dir);

    private:
        RectangleMapObject* playerObject;
        SDL_Texture* spritesheet;

        Animation* movements;

        int speed;
        string spritesheetSrc;

        void loadMOProperties();
};

#endif // PLAYER_H
