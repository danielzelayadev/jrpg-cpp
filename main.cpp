#include "Screens/ScreenManager.h"
#include "TestScreen.h"

int main()
{
    ScreenManager sm("JRPG", 1024, 700);

    sm.setCurrentScreen(new TestScreen(&sm));

    sm.run();

//    sm.dispose();

    return 0;
}
