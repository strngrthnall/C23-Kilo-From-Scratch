#define _DEFAULT_SOURCE

#include "terminal.h"
#include "input.h"
#include "output.h"
#include "editor.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>


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

    // --- MOCK TEMPORÁRIO ---
    // Injetamos múltiplas linhas sequenciais para testar o array dinâmico
    editorAppendRow("Linha 1: Engenharia de Sistemas em C.", 37);
    editorAppendRow("Linha 2: O array dinamico funciona perfeitamente.", 49);
    editorAppendRow("Linha 3: Buffer de anexacao eliminou o flickering.", 49);
    editorAppendRow("Linha 4: Reta final da Issue 1.2 alcançada com sucesso.", 55);
    // -----------------------

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
        die("editorAppendRow: realloc");
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

void editorOpen(const char *filename) {
    // Tenta abrir o ficheiro em modo dde leitura ("r" - read)
    FILE *fp = fopen(filename, "r");
    if (!fp) die("fopen"); // Se o ficheiro não existir ou não tivermos permissão, crashamos

    char *line = NULL;     // O ponteiro onde o getline() vai guardar a linha lida
    size_t linecap = 0;    // A capacidade de memória que o getline() já alocou
    ssize_t linelen;       // O tamanho da linha efetivamente lida (ssize_t porque pode ser -1 no erro/EOF)

    // O getline() devovle -1 quando chega ao fim do ficheiro (EOF)
    while ((linelen = getline(&line, &linecap, fp)) != -1) {
        // --- DATA SANITIZATION ---
        // Ficheiros podem ter \n (Linux/Mac) ou \r\n (Windows) no final de cada linha.
        // O nosso motor de renderização (output.c) já insere \r\n na tela.
        // Portanto, temos de "aparar" estes caracteres finais do texto lido.
        while (linelen > 0 && (line[linelen - 1] == '\n' || line[linelen - 1] == '\r')) {
            linelen--;
        }

        // Passa a linha limpa para o array dinâmico
        editorAppendRow(line, linelen);
    }

    free(line);

    fclose(fp);
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
