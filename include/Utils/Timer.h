#ifndef TIMER_H
#define TIMER_H

#include <SDL2/SDL.h>

class Timer
{
    public:
        Timer();

        void start();
        void stop();
        void pause();
        void resume();

        Uint32 getTicks();

        bool isStarted() { return started; }
        bool isPaused()  { return started && paused; }

    private:

        Uint32 startTicks;

        Uint32 pauseTicks;

        bool paused;
        bool started;
};

#endif // TIMER_H
