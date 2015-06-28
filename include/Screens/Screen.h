#ifndef SCREEN_H
#define SCREEN_H

class ScreenManager;
class Input;

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Screen
{
    public:
        Screen();
        Screen(ScreenManager* sm);

        ScreenManager* sm;
        Input* input;

        virtual void init() = 0;
        virtual void update() = 0;
        virtual void render() = 0;
        virtual void dispose() = 0;
};

#endif // SCREEN_H
