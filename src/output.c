//
// Created by mvrmiranda on 20/06/2026.
//

#include "abuf.h"
#include "output.h"
#include "editor.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>

static void editorDrawRows(struct abuf *ab) {
    // Desenhando o número de linhas que o terminal possui
    for (int y = 0; y < E.screen_rows; y++) {
        // Verifica se é texto ou espaço vazio
        if (y >= E.num_rows) {
            // Linha vazia: desenha o til
            abAppend(ab, "~", 1);
        } else {
            // Linha com texto real
            int len = E.row.size;

            // Nunca desenha fora dos limites do terminal.
            if (len > E.screen_cols) len = E.screen_cols;

            abAppend(ab, E.row.chars, len);
        }

        abAppend(ab, "\x1b[K", 3);

        if (y < E.screen_rows - 1) {
            abAppend(ab, "\r\n", 2);
        }
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

    // 5. string dinâmica com snprintf para enviar a posição real (E.cy + 1, E.cx + 1)
    char buf[32];
    snprintf(buf, sizeof(buf), "\x1b[%d;%dH", E.cy + 1, E.cx + 1);

    // 6. Devolve o cursor para o topo
    abAppend(&ab, buf, (int)strlen(buf));

    // 7. Mostra o cursor novamente
    // h: ativar
    abAppend(&ab, "\x1b[?25h", 6);

    // Move o cursor de volta para o topo esquerdo.
    write(STDOUT_FILENO, ab.b, ab.len);

    abFree(&ab);
}