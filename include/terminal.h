//
// Created by mvrmiranda on 20/06/2026.
//

#ifndef TERMINAL_H
#define TERMINAL_H

// Ativando o raw mode do terminal
void enableRawMode(void);

// Obtém as dimensões atuais do terminal
int terminalGetWindowSize(int *rows, int *cols);

// Trata erros fatais limpando a tela e encerrando o programa
void die(const char *s);


#endif //TERMINAL_H
