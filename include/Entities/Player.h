#ifndef PLAYER_H
#define PLAYER_H

#include "TMX/RectangleMapObject.h"
#include "Animation.h"
#include <SDL2/SDL_image.h>

enum WalkDirs
{
   WALK_DOWN, WALK_LEFT, WALK_RIGHT, WALK_UP
};

class Player
{
    public:
        Player(SDL_Renderer* renderer, RectangleMapObject* obj);
        virtual ~Player();

        void update();
        void render(SDL_Renderer* renderer);

        void walk(int dir);

        int getX() { return playerObject->x; }
        int getY() { return playerObject->y; }
        void setX(int x) { playerObject->x = x; }
        void setY(int y) { playerObject->y = y; }

        RectangleMapObject* getMapObject() { return playerObject; }
        Animation* getMovementAnim() { return movements; }

    private:
        RectangleMapObject* playerObject;
        SDL_Texture* spritesheet;

        Animation* movements;

        int speed;
        string spritesheetSrc;

        void loadMOProperties();
};

#endif // PLAYER_H
