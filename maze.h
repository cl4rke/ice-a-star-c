#include <stdlib.h>

typedef struct Vector2 Vector2;
typedef struct Maze Maze;

struct Vector2 {
    int x;
    int y;
};

struct Maze {
    char** content;
    Vector2* A;
    Vector2* B;
};

Vector2* create_vector2(int x, int y) {
    Vector2* vector2 = malloc(sizeof(Vector2*));

    vector2->x = x;
    vector2->y = y;

    return vector2;
}

Maze* create_maze(char** content, Vector2* A, Vector2* B) {
    Maze* maze = malloc(sizeof(Maze*));

    maze->content = content;
    maze->A = A;
    maze->B = B;

    return maze;
}

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

void print_maze(int width, int height, Maze* maze) {
    Vector2* A = maze->A;
    Vector2* B = maze->B;

    printf("A: %d, %d\n", A->x, A->y);
    printf("B: %d, %d\n", B->x, B->y);

    for (int j = 0; j < height; j++) {
        printf("%s\n", maze->content[j]);
    }
}

