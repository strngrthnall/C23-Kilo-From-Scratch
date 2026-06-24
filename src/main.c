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
    E.row = nullptr;

    if (terminalGetWindowSize(&E.screen_rows, &E.screen_cols) == -1) {
        die("terminalGetWindowSize failed");
    }

}

void editorMoveCursor(const int key) {
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

// Função para adicionar uma nova linha
void editorAppendRow(const char *s, const size_t len) {
    // O índice da nova linha será exatamente o número atual de linhas
    int at = E.num_rows;

    // 1. Redimensiona o array de linhas para caber mais uma struct erow
    erow *new_erow = realloc(E.row, sizeof(erow) * (at +1));
    if (new_erow == NULL) {
        // Falha de alocação
        return;
    }
    E.row = new_erow;

    // 2. preenche a nova linha com o tamanho do texto
    E.row[at].size = (int)len;

    // 3. Aloca memória estitamente necessária para os caracteres + 1 (para o '\0')
    E.row[at].chars = malloc(len + 1);

    // 4. Copia o texto para o bloco de memória alocado e adiciona o terminador
    memcpy(E.row[at].chars, s, len);
    E.row[at].chars[len] = '\0';

    // 5. Atualiza a contagem global de linhas
    E.num_rows++;
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
