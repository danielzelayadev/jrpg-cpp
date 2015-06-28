#ifndef TESTINPUT_H
#define TESTINPUT_H

#include "Input.h"
#include "TestScreen.h"

class TestInput : public Input
{
    public:
        TestInput(Screen* context);

        TestScreen* context;

        void keyDown(int keycode);
        void keyUp(int keycode);
        void keyTyped(char character);
        void mouseMove(int x, int y, int xrel, int yrel);
        void mouseButtonDown(int x, int y, int clicks, int button);
        void mouseButtonUp(int x, int y, int clicks, int button);

};

#endif // TESTINPUT_H
