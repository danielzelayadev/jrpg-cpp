#ifndef TESTSCREEN_H
#define TESTSCREEN_H

#include "Screen.h"
#include "TMX/Map.h"
#include "MapRenderer.h"

class TestScreen : public Screen
{
    public:
        TestScreen(ScreenManager* sm):Screen(sm){}

        friend class TestInput;

    private:

        Map* screenMap;
        MapRenderer* mRenderer;

        SDL_Rect camera;

        int camMoveX;
        int camMoveY;

        void wrapCamera();

        void init();
        void update();
        void render();
        void dispose();
};

#endif // TESTSCREEN_H
