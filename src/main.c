#include "terminal.h"
#include <stdio.h>
#include <ctype.h>
#include <unistd.h> /* API Posix standard */
#include <errno.h>
#include <stdlib.h>

void die(const char *s) {
    perror(s);
    exit(1);
}

int main(void) {
    enableRawMode();

    while (1) {
        char c = '\0';

        if (read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN) {
            die("read failed");
        }

        if (c == 'q') {
            break;
        }

        if (c == '\0') {
            continue;
        }

        if (iscntrl(c)) {
            printf("%d\n", c);
        } else {
            printf("%d ('%c')\n",c, c);
        }
    }

    return 0;
}
