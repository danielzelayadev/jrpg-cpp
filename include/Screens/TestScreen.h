#ifndef TESTSCREEN_H
#define TESTSCREEN_H

#include "Screen.h"
#include "TMX/Map.h"
#include "MapRenderer.h"

#include "TMX/RectangleMapObject.h"

#include "Animation.h"

enum Dirs
{
   DOWN, LEFT, RIGHT, UP
};

class TestScreen : public Screen
{
    public:
        TestScreen(ScreenManager* sm):Screen(sm){}

        friend class TestInput;

    private:

        Map* screenMap;
        MapRenderer* mRenderer;

        SDL_Rect camera, frame;

        RectangleMapObject* playerMO;
        SDL_Texture* playerSS;
        int frameW, frameH;
        int animationSpeed;
        int cachedPlayerX, cachedPlayerY;
        int playerSpeed = 3;

        int framesX, framesY;

        Animation* anim;

        int dir = -1;

        int camMoveX;
        int camMoveY;

        void wrapCamera();
        bool collisions();

        void init();
        void update();
        void render();
        void dispose();
};

#endif // TESTSCREEN_H
