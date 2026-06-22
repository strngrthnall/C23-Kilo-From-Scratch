//
// Created by mvrmiranda on 20/06/2026.
//

#include "input.h"
#include "terminal.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static bool verifyRead(char seq[], int num) {

    return read(STDIN_FILENO, &seq[num], 1) != 1;
}

int editorReadKey(void) {
    int nread;
    char c;

    while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
        if (nread == -1 && errno != EAGAIN) die("read");
    }

    if (c != '\x1b') {
        return c;
    }

    char seq[3];

    if (verifyRead(seq, 0)) return '\x1b';
    if (verifyRead(seq, 1)) return '\x1b';

    if (seq[0] == '[') {
        if (seq[1] >= '0' && seq[1] <= '9') {
            if (verifyRead(seq, 2)) return '\x1b';
            if (seq[2] == '~') {
                switch (seq[1]) {
                    case '1': return HOME_KEY;
                    case '3': return DEL_KEY;
                    case '4': return END_KEY;
                    case '5': return PAGE_UP;
                    case '6': return PAGE_DOWN;
                    case '7': return HOME_KEY;
                    case '8': return END_KEY;
                }
            }
        } else {
            switch (seq[1]) {
                case 'A': return ARROW_UP;
                case 'B': return ARROW_DOWN;
                case 'C': return ARROW_RIGHT;
                case 'D': return ARROW_LEFT;
                case 'H': return HOME_KEY;
                case 'F': return END_KEY;
            }
        }
    } else if (seq[0] == '0' || seq[0] == 'O') {
        switch (seq[1]) {
            case 'H': return HOME_KEY;
            case 'F': return END_KEY;
        }

    }

    printf("\r\n[DEBUG-ANSI] Seq Desconhecida: seq[0]=%d ('%c'), seq[1]=%d ('%c')\r\n",
           seq[0], seq[0], seq[1], seq[1]);

    return '\x1b';
}