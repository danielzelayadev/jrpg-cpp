#ifndef INPUT_H
#define INPUT_H

#include "Screens/Screen.h"

class Input
{
    public:
        Input(Screen* context){}
        Input(){}

        virtual void keyDown(int keycode) = 0;
        virtual void keyUp(int keycode) = 0;
        virtual void keyTyped(char character) = 0;
        virtual void mouseMove(int x, int y, int xrel, int yrel) = 0;
        virtual void mouseButtonDown(int x, int y, int clicks, int button) = 0;
        virtual void mouseButtonUp(int x, int y, int clicks, int button) = 0;
};

#endif // INPUT_H
