//
// Created by mvrmiranda on 20/06/2026.
//

#ifndef INPUT_H
#define INPUT_H

// Macro de bits para mapear combinações com a tecla Ctrl.
// Ela zera os bits 5 e 6 do caractere, que é exatamente o
// que o terminal faz fisicamente quando apertamos
// Ctrl + Alguma tecla
#define CTRL_KEY(k) ((k) & 0x1f)

enum editorKey {
    ARROW_LEFT = 1000,
    ARROW_RIGHT,
    ARROW_UP,
    ARROW_DOWN,
    DEL_KEY,
    HOME_KEY,
    END_KEY,
    PAGE_UP,
    PAGE_DOWN,
};

int editorReadKey(void);

#endif //INPUT_H
