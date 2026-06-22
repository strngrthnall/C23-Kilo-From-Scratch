//
// Created by mvrmiranda on 20/06/2026.
//

#include "abuf.h"
#include "output.h"
#include "editor.h"
#include <unistd.h>

static void editorDrawRows(struct abuf *ab) {
    // Desenhando o número de linhas que o terminal possui
    for (int y = 0; y < E.screen_rows; y++) {
        abAppend(ab, "~\r\n", 3);
    }
}

void editorRefreshScreen(void) {
    // Inicializa o buffer vazio
    struct abuf ab = ABUF_INIT;

    // 1. Esconde o cursor:
    // Comando VT100: \x1b[?25l
    // ?: Entra em modo privado do terminal
    // 25: Modo de visibilidade do cursor
    // l: desativar
    abAppend(&ab, "\x1b[?25l", 6);

    // 2. Limpa o Ecrã
    // Comando VT100: \x1b[2J
    // 'J' é o comando "Erase in Display" (Apagar na Tela)
    // '2' é o argumento que diz "Apague a tela inteira".
    abAppend(&ab, "\x1b[2J", 4);

    // 3. Move o cursor para o topo
    // Comando VT100: \x1b[H
    // 'H' é o comando "Cursor Position"
    // Sem argumentos, ele move o cursor para a linha 1, coluna 1
    abAppend(&ab, "\x1b[H", 3);

    // 4. Desenha a Interface
    editorDrawRows(&ab);

    // 5. Devolve o cursor para o topo
    abAppend(&ab, "\x1b[H", 3);

    // 6. Mostra o cursor novamente
    // h: ativar
    abAppend(&ab, "\x1b[?25h", 6);

    // Move o cursor de volta para o topo esquerdo.
    write(STDOUT_FILENO, ab.b, ab.len);

    abFree(&ab);
}