#include <string.h>
#include <stdio.h>

#include <3ds.h>

#include "move.h"


int main(int argc, char **argv) {

    gfxInitDefault();
    consoleInit(GFX_TOP, NULL);

    printf("Press A to move NTR Screenshots\n");
    printf("Press START to quit\n\n");

    // Main loop
    while (aptMainLoop()) {

        gspWaitForVBlank();
        hidScanInput();

        u32 kDown = hidKeysDown();
        if (kDown & KEY_START)
            break; // break in order to return to hbmenu

        if (kDown & KEY_A)
            startMvSS();

        // Flush and swap framebuffers
        gfxFlushBuffers();
        gfxSwapBuffers();
    }

    gfxExit();
    return 0;
}
