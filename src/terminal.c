//
// Created by mvrmiranda on 20/06/2026.
//

#include "terminal.h"
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

// Variável estática (privada a este arquivo) para guardar
// o estado original do terminal
static struct termios orig_termios;

// Função privada para restaurar o terminal ao sair.
static void disableRawMode(void) {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode(void) {
    // 1. Salva os atributos atuais do terminal
    tcgetattr(STDIN_FILENO, &orig_termios);

    // 2. Garante que o disableRawMode será chamada automaticamente
    // quando o programa fechar
    atexit(disableRawMode);

    // 3. faz uma cópia da estrutura original para podermos modificar
    struct termios raw = orig_termios;

    // 4. Desliga as flags ECHO (eco de tela) e ICANON (modo canônico)
    raw.c_lflag &= ~(ECHO| ICANON);

    // 5. Aplica as novas configurações ao terminal
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}