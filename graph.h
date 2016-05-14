#include <stdlib.h>
#include <math.h>

typedef struct GraphNode GraphNode;
typedef struct GraphNodeListNode GraphNodeListNode;
typedef struct GraphNodeList GraphNodeList;

struct GraphNode {
    GraphNode* prev;
    Vector2* position;
    int f_value;
    int g_value;
    int h_value;

    int is_closed;

    GraphNode* next;
};

struct GraphNodeList {
    GraphNode* head;
    GraphNode* tail;
};

int distance(Vector2* source, Vector2* destination) {
    if (source == NULL || destination == NULL) {
        return 1000;
    }

    return abs(source->x - destination->x) + abs(source->y - destination->y);
}

int get_f_value(GraphNode* node, Vector2* prev) {
    return node->h_value + distance(prev, node->position);
}

GraphNode* create_graph_node(GraphNode* prev, Vector2* position, Vector2* goal) {
    GraphNode* graph_node = malloc(sizeof(GraphNode));

    graph_node->prev = prev;
    graph_node->position = position;
    graph_node->g_value = prev != NULL ? (prev->g_value + distance(position, prev->position)) : 0;
    graph_node->h_value = distance(position, goal);
    graph_node->f_value = graph_node->g_value + graph_node->h_value;
    graph_node->is_closed = 0;

    graph_node->next = NULL;

    return graph_node;
}

void print_graph_node(GraphNode* node) {
    printf("From: ");
    print_vector2(node->prev != NULL ? node->prev->position : NULL);
    printf("To:   ");
    print_vector2(node->position);
    printf("%s\n", node->is_closed ? "CLOSED" : "OPEN");
    printf("%d %d %d\n\n", node->f_value, node->g_value, node->h_value);
}

void print_path_cost_to(GraphNode* node) {
    printf("%d\n", node->g_value);
}

void print_path_to(GraphNode* node) {
    // todo: reverse the order
    for (GraphNode* current = node; current->prev != NULL; current = current->prev) {
        printf("- %s\n", get_vector2_name(subtract_vector2(
                        current->position, current->prev->position)));
    }
}

GraphNodeList* create_graph_node_list() {
    GraphNodeList* list = malloc(sizeof(GraphNodeList));

    list->head = NULL;
    list->tail = NULL;

    return list;
}

GraphNode* find_graph_node_by_position(GraphNodeList* list, Vector2* position) {
    for (GraphNode* current = list->head; current != NULL; current = current->next) {
        if (distance(current->position, position) == 0) {
            return current;
        }
    }
    return NULL;
}

void add_graph_node(GraphNodeList* list, GraphNode* graph_node) {
    GraphNode* existing_graph_node = find_graph_node_by_position(list, graph_node->position);

    if (existing_graph_node == NULL) {
        if (list->tail != NULL) {
            list->tail->next = graph_node;
            list->tail = graph_node;
        } else {
            list->head = list->tail = graph_node;
        }
    } else if(existing_graph_node->g_value > graph_node->g_value) {
        existing_graph_node->g_value = graph_node->g_value;
        existing_graph_node->prev = graph_node->prev;
    }
}

void add_graph_nodes(GraphNodeList* destination, GraphNodeList* source) {
    for (GraphNode* current = source->head; current != NULL; current = current->next) {
        add_graph_node(destination, current);
    }
}

void print_graph_node_list(GraphNodeList* list) {
    for (GraphNode* current = list->head; current != NULL; current = current->next) {
        print_graph_node(current);
    }
}

GraphNode* get_best_open_graph_node(GraphNodeList* list) {
    GraphNode* best_open_graph_node = NULL;
    for (GraphNode* current = list->head; current != NULL; current = current->next) {
        if (!current->is_closed && best_open_graph_node == NULL) {
            best_open_graph_node = current;
        } else if (!current->is_closed && current->f_value < best_open_graph_node->f_value) {
            best_open_graph_node = current;
        }
    }
    return best_open_graph_node;
}

Vector2* explore(Vector2* start, Vector2* move, Maze* maze) {
    Vector2* position = create_vector2(start->x, start->y);

    while (maze->content[position->y][position->x] != '*') {
        position = add_vector2(position, move);
    }

    position = subtract_vector2(position, move);

    return position;
}

GraphNodeList* explore_adjacent_graph_nodes(GraphNode* node, Maze* maze) {
    GraphNodeList* discoveries = create_graph_node_list();

    Vector2* position = node->position;

    Vector2* moves[4];

    moves[0] = explore(position, create_vector2( 0,  1), maze);
    moves[1] = explore(position, create_vector2( 0, -1), maze);
    moves[2] = explore(position, create_vector2(-1,  0), maze);
    moves[3] = explore(position, create_vector2( 1,  0), maze);

    for (int i = 0; i < 4; i++) {
        if (distance(position, moves[i]) != 0) {
            if (node->prev == NULL || distance(moves[i], node->prev->position) != 0) {
                GraphNode* movement = create_graph_node(node, moves[i], maze->B);
                add_graph_node(discoveries, movement);
            }
        }
    }

    node->is_closed = 1;

    return discoveries;
}

