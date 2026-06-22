//
// Created by mvrmiranda on 20/06/2026.
//

#include "terminal.h"
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdio.h>

// Variável estática (privada a este arquivo) para guardar
// o estado original do terminal
static struct termios orig_termios;

// Trata erros fatais limpando a tela e encerrando o programa
void die(const char *s) {
    write(STDOUT_FILENO, "\x1b[2J", 4);
    write(STDOUT_FILENO, "\x1b[H", 3);
    perror(s);
    exit(1);
}

// Função privada para restaurar o terminal ao sair.
static void disableRawMode(void) {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1) {
        die("tcsetattr (disableRawMode)");
    }
}

void enableRawMode(void) {
    // 1. Salva os atributos atuais do terminal
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) {
        die("tcgetattr");
    }

    // 2. Garante que o disableRawMode será chamada automaticamente
    // quando o programa fechar
    if (atexit(disableRawMode) != 0) {
        die("atexit");
    }

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
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) {
        die("tcsetattr (enableRawMode)");
    }
}

static int terminalGetCursorPosition(int *rows, int *cols) {
    char buf[32];
    unsigned int i = 0;

    // Device Status Report
    if (write(STDOUT_FILENO, "\x1b[6n", 4) != 4) return -1;

    while (i < sizeof(buf) -1) {
        if (read(STDIN_FILENO, &buf[i], 1) != 1) break;
        if (buf[i] == 'R') break;
        i++;
    }

    buf[i] = '\0';

    if (buf[0] != '\x1b' || buf[1] != '[') return -1;

    if (sscanf(&buf[2], "%d;%d", rows, cols) != 2) return -1;

    return 0;

}

int terminalGetWindowSize(int *rows, int *cols) {
    struct winsize ws;

    // TIOCGWINSZ: "Terminal IOCtl Get WINdow SiZe"
    // Retorna -1 se falhar, ou se as colunas forem 0.
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
        if (write(STDOUT_FILENO, "\x1b[999C\x1b[999B", 12) != 12) return -1;
        return terminalGetCursorPosition(rows, cols);
    } else {
        // Ponteiros para "devolver" dois valores na mesma função
        *cols = ws.ws_col;
        *rows = ws.ws_row;
        return 0;
    }
}