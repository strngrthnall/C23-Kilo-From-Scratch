#include "terminal.h"
#include "input.h"
#include "output.h"
#include <stdio.h>



int main(void) {
    enableRawMode();

    while (1) {
        editorRefreshScreen();

        int c = editorReadKey();

        if (c == CTRL_KEY('q')) {
            printf("\x1b[2J");
            printf("\x1b[H");
            break;
        }

    }

    return 0;
}
