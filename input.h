#include <stdlib.h>

int  read_int(FILE* source) {
    unsigned long length = sizeof(char) * 5;
    char* ascii = malloc(length);

    fgets(ascii, length, source);

    return atoi(ascii);
}

Maze* read_maze(int width, int height, FILE* source) {
    char** content = malloc(sizeof(char) * width * height);
    Vector2* A = NULL;
    Vector2* B = NULL;

    for (int j = 0; j < height; j++) {
        content[j] = malloc(sizeof(char) * width + 1);

        fgets(content[j], width + 2, source);

        content[j][width] = '\0';

        for (int i = 0; i < width; i++) {
            if (content[j][i] == 'A') {
                A = create_vector2(i, j);
            } else if (content[j][i] == 'B') {
                B = create_vector2(i, j);
            }
        }
    }

    return create_maze(content, width, height, A, B);
}

