#include <stdlib.h>
#include "vectors.h"

typedef struct Maze Maze;

struct Maze {
    char** content;
    Vector2* A;
    Vector2* B;
};

Maze* create_maze(char** content, int width, int height, Vector2* A, Vector2* B) {
    Maze* maze = malloc(sizeof(content) * width * height + sizeof(Maze*));

    maze->content = content;
    maze->A = A;
    maze->B = B;

    return maze;
}

void print_maze(int height, Maze* maze) {
    printf("A: ");
    print_vector2(maze->A);

    printf("B: ");
    print_vector2(maze->B);

    for (int j = 0; j < height; j++) {
        printf("%s\n", maze->content[j]);
    }
}

