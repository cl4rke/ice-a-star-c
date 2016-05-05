#include <stdlib.h>

Maze* read_maze(int width, int height, FILE* source) {
    char** content = malloc(sizeof(char*) * height);
    Vector2* A;
    Vector2* B;

    for (int j = 0; j < height; j++) {
        content[j] = malloc(sizeof(char) * width);

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

    return create_maze(content, A, B);
}

