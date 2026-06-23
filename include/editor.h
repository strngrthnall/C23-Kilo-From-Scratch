//
// Created by mvrmiranda on 20/06/2026.
//

#ifndef EDITOR_H
#define EDITOR_H

typedef struct erow {
    int size;
    char *chars;
} erow;

struct editorConfig {
    int cx, cy;
    int screen_rows;
    int screen_cols;
    int num_rows;
    erow row;
};

extern struct editorConfig E;

#endif //EDITOR_H
