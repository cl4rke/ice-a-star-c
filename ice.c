#include <stdio.h>
#include <stdlib.h>
#include "maze.h"
#include "input.h"
#include "graph.h"

int main() {
    FILE* file_source = fopen("input.txt", "r");

    int height = read_int(file_source),
        width  = read_int(file_source);

    printf("%d %d\n", width, height);

    int case_number = 0;

    GraphNodeList* graph_node_list = create_graph_node_list();

    Maze* maze = read_maze(width, height, file_source);

    fclose(file_source);

    printf("Printing maze...\n");
    print_maze(height, maze);

    printf("Creating start graph node...\n");
    GraphNode* start = create_graph_node(NULL, maze->A, maze->B);

    printf("Adding start to list...\n");
    add_graph_node(graph_node_list, start);

    printf("Printing list...\n");
    print_graph_node_list(graph_node_list);

    GraphNode* goal;
    while ((goal = find_graph_node_by_position(graph_node_list, maze->B)) == NULL) {
        printf("Exploring...\n");

        GraphNode* node_to_explore = get_best_open_graph_node(graph_node_list);
        print_graph_node(node_to_explore);

        GraphNodeList* discoveries = explore_adjacent_graph_nodes(node_to_explore, maze);

        printf("Printing discoveries...\n");
        print_graph_node_list(discoveries);

        printf("Adding all discoveries to list...\n");
        add_graph_nodes(graph_node_list, discoveries);

        printf("Printing list...\n");
        print_graph_node_list(graph_node_list);
    }

    print_graph_node(goal);
    printf("Case #%d: ", case_number + 1);
    print_path_cost_to(goal);
    print_path_to(goal);

    free(start);
    free(graph_node_list);
    free(maze);
}

