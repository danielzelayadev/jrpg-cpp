#ifndef TESTSCREEN_H
#define TESTSCREEN_H

#include "Screen.h"
#include "TMX/Map.h"
#include "MapRenderer.h"

#include "TMX/RectangleMapObject.h"

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
        int cachedPlayerX, cachedPlayerY;
        int playerSpeed = 5;

        int framesX, framesY;

        bool play = false;
        int dir = -1;
        int switchFrame = 8;
        int frameCtr = 0;

        int camMoveX;
        int camMoveY;

        void wrapCamera();
        void animate();
        void stopAnimations();
        bool collisions();

        void init();
        void update();
        void render();
        void dispose();
};

#endif // TESTSCREEN_H
