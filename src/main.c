#include "terminal.h"
#include <stdio.h>
#include <ctype.h>
#include <unistd.h> /* API Posix standard */

int main() {
    enableRawMode();

    char c;

    // STDIN_FILENO: É uma constante que representa o File Descriptor
    // (Descritor de Arquivo) número 0.
    while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q') {
        if (iscntrl(c) /* Avalia se o byte lido é imprìmivel */) {
            printf("%d\n", c);
        } else {
            printf("%d ('%c')\n", c, c);
        }
    }

    return 0;
}
