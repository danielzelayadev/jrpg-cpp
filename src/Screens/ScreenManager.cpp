#include "Screens/ScreenManager.h"
#include "Input/Input.h"

ScreenManager::ScreenManager(string windowTitle, int w, int h)
{
    currentScreen = nullptr;
    done = false;

    setWindowWidth(w);
    setWindowHeight(h);

    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF | IMG_INIT_WEBP);

    window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h,
                              SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    fpsTimer = new Timer();
    capTimer = new Timer();
}

void ScreenManager::run()
{

   int frameCount = 0;
   fpsTimer->start();
   while(!done)
   {
      capTimer->start();

      handleInput();

      calculateFPS(frameCount);

      update();
      render();

      frameCount++;
      capFPS();
   }

   dispose();
}

void ScreenManager::exit()
{
   done = true;
}

void ScreenManager::handleInput()
{
   SDL_Event e;

   if(SDL_PollEvent(&e) > 0)
   {
       if(e.type == SDL_QUIT)
           exit();

       else if(currentScreen && currentScreen->input)
       {
          switch(e.type)
          {
             case SDL_KEYDOWN:
             if(e.key.keysym.sym == SDLK_ESCAPE) exit();
             currentScreen->input->keyDown(e.key.keysym.sym);
             currentScreen->input->keyTyped((char)e.key.keysym.sym);
             break;
             case SDL_KEYUP:
             currentScreen->input->keyUp(e.key.keysym.sym);
             break;
             case SDL_MOUSEMOTION:
             currentScreen->input->mouseMove(e.motion.x, e.motion.y, e.motion.xrel, e.motion.yrel);
             break;
             case SDL_MOUSEBUTTONDOWN:
             currentScreen->input->mouseButtonDown(e.button.x, e.button.y, e.button.clicks, e.button.button);
             break;
             case SDL_MOUSEBUTTONUP:
             currentScreen->input->mouseButtonUp(e.button.x, e.button.y, e.button.clicks, e.button.button);
             break;
          }
       }
   }

}

void ScreenManager::update()
{
   if(currentScreen)
      currentScreen->update();

}

void ScreenManager::render()
{
   SDL_RenderClear(renderer);

   if(currentScreen)
      currentScreen->render();

   SDL_RenderPresent(renderer);
}

void ScreenManager::setCurrentScreen(Screen* screen)
{
   if(currentScreen)
   {
      currentScreen->dispose();
      delete currentScreen;
   }

   currentScreen = screen;
   currentScreen->init();

}

void ScreenManager::dispose()
{
   delete fpsTimer;
   delete capTimer;

   currentScreen->dispose();
   delete currentScreen;

   SDL_DestroyRenderer(renderer);
   SDL_DestroyWindow(window);

   IMG_Quit();
   SDL_Quit();
}

void ScreenManager::setWindowTitle(string title)
{
   windowTitle = title;
}

void ScreenManager::setWindowWidth(int w)
{
   windowWidth = w;
}

void ScreenManager::setWindowHeight(int h)
{
   windowHeight = h;
}

string ScreenManager::getWindowTitle()
{
  return windowTitle;
}

int ScreenManager::getWindowWidth()
{
   return windowWidth;
}

int ScreenManager::getWindowHeight()
{
   return windowHeight;
}

void ScreenManager::calculateFPS(int frameCount)
{
   float avgFPS = frameCount / ( fpsTimer->getTicks() / 1000.f );

      if( avgFPS > 2000000 )
        avgFPS = 0;

      cout << avgFPS << endl;
}

void ScreenManager::capFPS()
{
    int frameTicks = capTimer->getTicks();

    if( frameTicks < TICKS_PER_FRAME)
      SDL_Delay( TICKS_PER_FRAME - frameTicks );

}
