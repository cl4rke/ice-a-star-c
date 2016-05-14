#include <stdio.h>
#include <stdlib.h>
#include "maze.h"
#include "input.h"
#include "graph.h"

int main() {
    FILE* file_source = fopen("input.txt", "r");

    int cases_count = read_int(file_source);

    for (int case_number = 0; case_number < cases_count; case_number++) {
        int height = read_int(file_source),
            width  = read_int(file_source);

        Maze* maze = read_maze(width, height, file_source);

        GraphNodeList* graph_node_list = create_graph_node_list();
        add_graph_node(graph_node_list, create_graph_node(NULL, maze->A, maze->B));

        int search_is_successful = 1;
        GraphNode* goal;

        while ((goal = find_graph_node_by_position(graph_node_list, maze->B)) == NULL) {
            GraphNode* node_to_explore = get_best_open_graph_node(graph_node_list);

            if (node_to_explore == NULL) {
                search_is_successful = 0;
                break;
            }

            add_graph_nodes(graph_node_list, explore_adjacent_graph_nodes(node_to_explore, maze));
        }

        printf("Case #%d: ", case_number + 1);

        if (search_is_successful) {
            print_path_cost_to(goal);
            print_path_to(goal);
        } else {
            printf("no solution\n");
        }
        printf("\n");

        free(maze);
        free(graph_node_list);
    }

    fclose(file_source);
}

