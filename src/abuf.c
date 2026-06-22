//
// Created by mvrmiranda on 22/06/2026.
//

#include "abuf.h"
#include <stdlib.h>
#include <string.h>

void abAppend(struct abuf *ab, const char *s, int len) {
    // Pede ao sistema para redimensionar o bloco de memória atual,
    // garantindo que tenha espaço para o tamanho antigo + o novo pedaço
    char *new_ptr = realloc(ab->b, ab->len + len);

    // Se o sistema negar a memória abortamos a anexação para não
    // causar um Segmentation Fault
    if (new_ptr == NULL) return;

    // Copia a nova string para o final do bloco de memória
    memcpy(&new_ptr[ab->len], s, len);

    // Atualiza a estrutura com o novo ponteiro e o novo tamanho total
    ab->b = new_ptr;
    ab->len += len;
}

void abFree(struct abuf *ab) {
    // Devolve a memória ao Sistema para evitar Memory Leaks
    free(ab->b);
}