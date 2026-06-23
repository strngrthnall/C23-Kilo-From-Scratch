#include "terminal.h"
#include "input.h"
#include "output.h"
#include "editor.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

// Instanciação do estado global do editor.
struct editorConfig E;

// Inicializando os subsistemas antes do loop principal
void initEditor(void) {
    // Inicializa o cursor no topo esquerdo (0,0)
    E.cx = 0;
    E.cy = 0;
    E.num_rows = 0; // Inicializa sem nenhuma linha;

    if (terminalGetWindowSize(&E.screen_rows, &E.screen_cols) == -1) {
        die("terminalGetWindowSize failed");
    }

    // --- MOCK TEMPORÁRIO ---
    // Injeção de linha manual, para testar a renderização.
    E.num_rows = 1;
    E.row.size = 13; // Tamanho de "Hello, world!"

    // Alocando memória para 12 letras + 1 byte nulo ('\0')
    E.row.chars = malloc(14);

    // Copia os bytes para o bloco alocado
    memcpy(E.row.chars, "Hello, world!", 13);
    E.row.chars[13] = '\0'; // Finaliza a string de forma segura
    // -----------------------
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
