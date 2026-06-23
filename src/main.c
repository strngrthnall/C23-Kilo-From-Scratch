#include "terminal.h"
#include "input.h"
#include "output.h"
#include "editor.h"
#include <stdlib.h>
#include <unistd.h>

// Instanciação do estado global do editor.
struct editorConfig E;

// Inicializando os subsistemas antes do loop principal
void initEditor(void) {
    // Inicializa o cursor no topo esquerdo (0,0)
    E.cx = 0;
    E.cy = 0;

    if (terminalGetWindowSize(&E.screen_rows, &E.screen_cols) == -1) {
        die("terminalGetWindowSize failed");
    }
}

void editorMoveCursor(int key) {
    switch (key) {
        case ARROW_LEFT:
            if (E.cx > 0) E.cx--;
            break;
        case ARROW_RIGHT:
            // Impede o cursor de ultrapassar a última linha do eixo x
            if (E.cx < E.screen_cols - 1) E.cx++;
            break;
        case ARROW_UP:
            if (E.cy > 0) E.cy--;
            break;
        case ARROW_DOWN:
            // Impede o cursor de ultrapassar a última linha do eixo y
            if (E.cy < E.screen_rows - 1) E.cy++;
            break;
    }
}

int main(void) {
    enableRawMode();
    initEditor();

    while (1) {
        editorRefreshScreen();
        const int c = editorReadKey();

        if (c == CTRL_KEY('q')) {
            write(STDOUT_FILENO, "\x1b[2J", 4);
            write(STDOUT_FILENO, "\x1b[H", 3);
            break;
        } else if (c == ARROW_DOWN || c == ARROW_LEFT || c == ARROW_RIGHT || c == ARROW_UP) {
            editorMoveCursor(c);
        }
    }
    return 0;
}
