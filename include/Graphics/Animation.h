#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL2/SDL.h>
#include "Timer.h"

#include <string>

using std::string;

enum AnimationDirs
{
   HORIZONTAL, VERTICAL
};

class Animation
{
    public:
        Animation(int framesX, int framesY, int frameW, int frameH, Uint32 ms, int direction);

        void animate();

        void play() { timer.start(); }
        void pause() { timer.pause(); }
        void resume() { timer.resume(); }
        void stop() { timer.stop(); }

        void setAnimationSpeed(Uint32 ms) { this->ms = ms; }
        Uint32 setAnimationSpeed() { return ms; }

        void setCurrentFrame(int row, int col);
        SDL_Rect getCurrentFrame() { return frame; }

        bool isPlaying() { return timer.isStarted(); }
        bool isPaused() { return timer.isPaused(); }

    private:
        SDL_Rect frame;

        Timer timer;

        int direction;

        Uint32 ms;

        int framesX;
        int framesY;
        int frameW;
        int frameH;
};

#endif // ANIMATION_H
