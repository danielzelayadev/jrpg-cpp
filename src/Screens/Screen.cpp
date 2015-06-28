#include "Screens/Screen.h"
#include "Screens/ScreenManager.h"

Screen::Screen()
{
}

Screen::Screen(ScreenManager* sm)
{
    this->sm = sm;
    this->input = nullptr;
}
