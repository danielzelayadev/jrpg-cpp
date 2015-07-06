#include "Timer.h"

Timer::Timer()
{
    stop();
}

void Timer::start()
{
    started = true;

    paused = false;

    startTicks = SDL_GetTicks();
    pauseTicks = 0;
}

void Timer::stop()
{
    startTicks = 0;
    pauseTicks = 0;

    started = false;
    paused = false;
}

void Timer::pause()
{
    if( started && !paused )
    {
        paused = true;

        pauseTicks = SDL_GetTicks() - startTicks;
        startTicks = 0;
    }
}

void Timer::resume()
{
    if( started && paused )
    {
        paused = false;

        startTicks = SDL_GetTicks() - pauseTicks;

        pauseTicks = 0;
    }
}

Uint32 Timer::getTicks()
{
    Uint32 time = 0;

    if( started )
    {
        if( paused )
            time = pauseTicks;

        else
            time = SDL_GetTicks() - startTicks;
    }

    return time;
}
