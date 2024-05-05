
#include "raylibinterface.h"
#include "network.h"

int main()
{
    that_createRaylibWindow();
	that_initNetwork();

    do
    {
        that_updateRaylibState();  // Program State, Mouse and Keyboard are updated.

        that_updateRaylibLoop();   // Draws everything

		that_checkNetwork();       // Network Interface

    } while(!that_isRaylibClosed());

    that_networkCleanup();
    that_closeRaylibWindow();
    return 0;
}

