//
// Created by mvrmiranda on 22/06/2026.
//

#ifndef ABUF_H
#define ABUF_H

// Estrutura do Append Buffer
struct abuf {
    char *b;
    int len;
};

// Macro para inicializar um buffer vazio
#define ABUF_INIT {NULL, 0}

// Adiciona texto ao fim do buffer
void abAppend(struct abuf *ab, const char *s, int len);

// Libera memória do buffer
void abFree(struct abuf *ab);

#endif //ABUF_H
