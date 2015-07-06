#include "Animation.h"

Animation::Animation(int framesX, int framesY, int frameW, int frameH, Uint32 ms, int direction)
{
     this->framesX = framesX;
     this->framesY = framesY;
     this->frameW = frameW;
     this->frameH = frameH;

     this->ms = ms;

     this->direction = direction;

     frame = { 0, 0, frameW, frameH };
}

void Animation::setCurrentFrame(int row, int col)
{
    if(row < 0 || row >= framesY) row = frame.y / frameH;

    if(col < 0 || col >= framesX) col = frame.x / frameW;

    frame.x = frameW * col;
    frame.y = frameH * row;
}

void Animation::animate()
{
   if(timer.isStarted() && !timer.isPaused())
   {
       if(timer.getTicks() >= ms)
       {
          int col = frame.x / frameW, row = frame.y / frameH;

          if(direction == HORIZONTAL)
          {
             col++;
             if(col >= framesX) col = 0;
          }

          else if(direction == VERTICAL)
          {
             row++;
             if(row >= framesY) row = 0;
          }

          setCurrentFrame(row, col);
          timer.stop();
          timer.start();
       }
   }
}

void Animation::stop()
{
   timer.stop();

   if(direction == HORIZONTAL)
   setCurrentFrame(-1, 0);

   else if(direction == VERTICAL)
   setCurrentFrame(0, -1);
}
