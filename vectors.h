#include <stdlib.h>

typedef struct Vector2 Vector2;

struct Vector2 {
    int x;
    int y;
};

Vector2* create_vector2(int x, int y) {
    Vector2* vector2 = malloc(sizeof(Vector2*));

    vector2->x = x;
    vector2->y = y;

    return vector2;
}

Vector2* add_vector2(Vector2* destination, Vector2* source) {
    return create_vector2(destination->x + source->x, destination->y + source->y);
}

Vector2* subtract_vector2(Vector2* destination, Vector2* source) {
    return create_vector2(destination->x - source->x, destination->y - source->y);
}

char* get_vector2_name(Vector2* vector2) {
    if (vector2->x < 0) {
        return "left";
    } else if (vector2->x > 0) {
        return "right";
    } else if (vector2->y < 0) {
        return "up";
    } else if (vector2->y > 0) {
        return "down";
    }
    return "unknown";
}

void print_vector2(Vector2* vector2) {
    if (vector2 != NULL) {
        printf("(%d, %d)\n", vector2->x, vector2->y);
    } else {
        printf("NULL\n");
    }
}

