#include "terminal.h"
#include "input.h"
#include <stdio.h>
#include <ctype.h>


int main(void) {
    enableRawMode();

    while (1) {
        int c = editorReadKey();

        if (c == CTRL_KEY('q')) {
            printf("\x1b[2J");
            printf("\x1b[H");
            break;
        }

        if (c >= 1000 || iscntrl(c)) {
            printf("%d\n", c);
        } else {
            printf("%d ('%c')\n",c, c);
        }
    }

    return 0;
}
