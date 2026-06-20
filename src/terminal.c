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

    // 4. Definição das ‘flags’
    // 4.1 ‘Flags’ de Entrada
    // IXON: Desliga Ctrl-S e Ctrl-Q
    // ICRNL: Desliga a tradução de \r para \n (Enter)
    // BRKINT, INPCK, ISTRIP: ‘Flags’ legadas desativadas por segurança
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);

    // 4.2 ‘Flags’ de Saída
    // OPOST: Desliga o processamento de saída
    raw.c_oflag &= ~(OPOST);

    // 4.3 ‘Flags’ de controle
    // CS8: Define o tamanho do caracter para 8 bits
    raw.c_cflag |= (CS8);

    // 4.4 ‘Flags’ Locais
    // ECHO: Desliga o eco de tela
    // ICANON: Lê byte a byte
    // IEXTEN: Desliga Ctrl-V
    // ISIG: Desliga dinais de interrupção como Ctrl-C e Ctrl-Z
    raw.c_lflag &= ~(ECHO| ICANON | IEXTEN | ISIG);

    // 4.5 Configuração de Timeout para o read()
    // VMIN: Número mínimo de bytes antes do read() retornar
    // VTIME: Tempo máximo de espera antes do read() retornar (em décimos de segundo)
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;

    // 5. Aplica as novas configurações ao terminal
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}