//
// Created by mvrmiranda on 20/06/2026.
//

#include "output.h"
#include <unistd.h>

static void editorDrawRows(void) {
    for (int y = 0; y < 24; y++) {
        write(STDOUT_FILENO, "~\r\n", 3);
    }
}

void editorRefreshScreen(void) {
    // Comando VT100: \x1b[2J
    // 'J' é o comando "Erase in Display" (Apagar na Tela)
    // '2' é o argumento que diz "Apague a tela inteira".
    write(STDOUT_FILENO, "\x1b[2J", 4);

    // Comando VT100: \x1b[H
    // 'H' é o comando "Cursor Position"
    // Sem argumentos, ele move o cursor para a linha 1, coluna 1
    write(STDOUT_FILENO, "\x1b[H", 3);

    editorDrawRows();

    // Move o cursor de volta para o topo esquerdo.
    write(STDOUT_FILENO, "\x1b[H", 3);
}