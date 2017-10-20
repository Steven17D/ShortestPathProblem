//
// Created by Steven on 10/13/2017.
//

#include <stdio.h>
#include <afxres.h>
#include <assert.h>
#include "../properties.h"
#include "../graph.h"

void interactive_test(Graph *graph);

int main() {
    short int world_map[MAX_DIMENSION][MAX_DIMENSION];

    int x, y;
    for (x = 0; x < MAX_DIMENSION; ++x) {
        for (y = 0; y < MAX_DIMENSION; ++y) {
            world_map[x][y] = (short) abs(x - y);
        }
    }

    Graph* graph = Graph_Create(world_map);

#ifdef DIAGONAL
    assert(graph->position.x == 0 && graph->position.y == 0);
    assert(graph->adjacent_nodes_count == 3);
    assert(graph->value == 0);

    while (TRUE) {
        if (graph->position.x == MAX_DIMENSION/2 && graph->position.y == MAX_DIMENSION/2) {
            break;
        } else {
            int i;
            for (i = 0; i < graph->adjacent_nodes_count; ++i) {
                if (graph->adjacent_nodes[i]->position.x == graph->position.x + 1 &&
                        graph->adjacent_nodes[i]->position.y == graph->position.y + 1) {
                    graph = graph->adjacent_nodes[i];
                }
            }
        }
    }

    assert(graph->position.x == MAX_DIMENSION/2 && graph->position.y == MAX_DIMENSION/2);
    assert(graph->adjacent_nodes_count == 8);
    assert(graph->value == 0);
#else
    interactive_test(graph);
#endif

    Graph_Destroy(graph);
    return 0;
}

void interactive_test(Graph *graph) {
    BOOL quit = FALSE;
    while (quit == FALSE) {
        printf("At [%d, %d]\tvalue: %d\t%d available neighbors\n",
               graph->position.x, graph->position.y, graph->value, graph->adjacent_nodes_count);
        int i;
        Node *node;
        for (i = 0; i < graph->adjacent_nodes_count; ++i) {
            node = graph->adjacent_nodes[i];
            printf("%d. At [%d, %d]\tvalue: %d\t%d available neighbors\n",
                   i + 1, node->position.x, node->position.y, node->value, node->adjacent_nodes_count);
        }
        printf("Select neighbor to go to: ");
        int selected_neighbor;
        scanf("%d", &selected_neighbor);
        if (selected_neighbor == -1) {
            quit = TRUE;
        } else if (selected_neighbor > 0 && selected_neighbor <= graph->adjacent_nodes_count) {
            graph = graph->adjacent_nodes[selected_neighbor - 1];
        }
        printf("\n");
    }
}