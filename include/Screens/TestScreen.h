#ifndef TESTSCREEN_H
#define TESTSCREEN_H

#include "Screen.h"
#include "TMX/Map.h"
#include "MapRenderer.h"

#include "Player.h"
#include "NPC.h"

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

        SDL_Rect camera;

        Player* player;
        NPC* npc;

        int cachedPlayerX, cachedPlayerY;

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
