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

void print_vector2(Vector2* vector2) {
    printf("(%d, %d)\n", vector2->x, vector2->y);
}

