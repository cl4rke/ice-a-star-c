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

int get_f_value(GraphNode* node) {
    return node->g_value * 2 + node->h_value * 3;
}

GraphNode* create_graph_node(GraphNode* prev, Vector2* position, Vector2* goal) {
    GraphNode* graph_node = malloc(sizeof(GraphNode));

    graph_node->prev = prev;
    graph_node->position = position;
    graph_node->g_value = prev != NULL ? (prev->g_value + distance(position, prev->position)) : 0;
    graph_node->h_value = distance(position, goal);
    graph_node->f_value = get_f_value(graph_node);
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

void print_prev_then_current_graph_node_position(GraphNode* node) {
    if (node->prev->prev != NULL) {
        print_prev_then_current_graph_node_position(node->prev);
    }
    printf("- %s\n", get_vector2_name(subtract_vector2(
                    node->position, node->prev->position)));
}

void print_path_to(GraphNode* node) {
    print_prev_then_current_graph_node_position(node);
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
            while (list->tail->next) {
                list->tail = list->tail->next;
            }
        } else {
            list->head = list->tail = graph_node;
        }
    } else if(existing_graph_node->g_value > graph_node->g_value) {
        existing_graph_node->g_value = graph_node->g_value;
        existing_graph_node->prev = graph_node->prev;
    }
}

void add_graph_nodes(GraphNodeList* destination, GraphNodeList* source) {
    for (GraphNode* node = source->head; node != NULL; node = node->next) {
        add_graph_node(destination, node);
    }
}

void print_graph_node_list(GraphNodeList* list) {
    int i = 0;
    for (GraphNode* current = list->head; current != NULL; current = current->next) {
        if (current == list->head) {
            printf("HEAD:\n");
        } else if (current == list->tail) {
            printf("TAIL:\n");
        }
        print_graph_node(current);
        i++;
    }
    printf("Length: %d\n\n", i);
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

    moves[0] = create_vector2( 0,  1);
    moves[1] = create_vector2( 0, -1);
    moves[2] = create_vector2(-1,  0);
    moves[3] = create_vector2( 1,  0);

    for (int i = 0; i < 4; i++) {
        if (node->prev == NULL || !same_vector2_direction(moves[i],
                    subtract_vector2(node->prev->position, position))) {
            Vector2* explore_move = explore(position, moves[i], maze);

            if (distance(position, explore_move) != 0) {
                GraphNode* movement = create_graph_node(node, explore_move, maze->B);
                add_graph_node(discoveries, movement);
            }
        }
    }

    node->is_closed = 1;

    return discoveries;
}

