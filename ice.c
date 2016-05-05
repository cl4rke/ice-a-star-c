#include <stdio.h>
#include <stdlib.h>
#include "maze.h"
#include "input.h"

int main() {
    FILE* file_source = fopen("input.txt", "r");

    int width = 5;
    int height = 6;

    Maze* maze = read_maze(5, 6, file_source);

    fclose(file_source);

    printf("Printing maze...\n");
    print_maze(5, 6, maze);
}

