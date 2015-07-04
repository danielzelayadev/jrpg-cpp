#include "Screens/ScreenManager.h"
#include "TestScreen.h"

int main()
{
    ScreenManager sm("JRPG", 1024, 672);

    sm.setCurrentScreen(new TestScreen(&sm));

    sm.run();

    return 0;
}
