#include <stdlib.h>
#include <math.h>

typedef struct GraphNode GraphNode;
typedef struct GraphNodeList GraphNodeList;

struct GraphNode {
    Vector2* prev;
    Vector2* position;
    int f_value;
    int g_value;
    int h_value;
};

int distance(Vector2* source, Vector2* destination) {
    return abs(source->x - destination->x) + abs(source->y - destination->y);
}

int get_f_value(GraphNode* node, Vector2* prev) {
    return node->h_value + distance(prev, node->position);
}

GraphNode* create_graph_node(Vector2* position, Vector2* goal) {
    GraphNode* graph_node = malloc(sizeof(GraphNode*));

    graph_node->prev = NULL;
    graph_node->position = position;
    graph_node->f_value = 9999;
    graph_node->g_value = 9999;
    graph_node->h_value = distance(position, goal);

    return graph_node;
}

