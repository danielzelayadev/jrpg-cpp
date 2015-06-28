#ifndef TESTSCREEN_H
#define TESTSCREEN_H

#include "Screen.h"
#include "Map.h"
#include "MapRenderer.h"

class TestScreen : public Screen
{
    public:
        TestScreen(ScreenManager* sm):Screen(sm){}

        Map* screenMap;
        MapRenderer* mRenderer;

        void init();
        void update();
        void render();
        void dispose();
};

#endif // TESTSCREEN_H
