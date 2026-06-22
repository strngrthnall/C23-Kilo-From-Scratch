#include "terminal.h"
#include "input.h"
#include "output.h"
#include "editor.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

// Instanciação do estado global do editor.
struct editorConfig E;

// Inicializando os subsistemas antes do loop principal
void initEditor(void) {
    if (terminalGetWindowSize(&E.screen_rows, &E.screen_cols) == -1) {
        die("terminalGetWindowSize failed");
    }
}

int main(void) {
    enableRawMode();
    initEditor();

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
