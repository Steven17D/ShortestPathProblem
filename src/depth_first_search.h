//
// Created by Steven on 10/12/2017.
//

#include "properties.h"
#include "graph.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
//#define DEBUG

define_Stack(PNode)
typedef Stack_PNode* PStack_PNode;
define_Stack(PStack_PNode)

int DepthFirstSearch(Graph *start_node, OUT PStack_PNode* result);
int CalculatePathWeight(PStack_PNode path);

BOOL Predicate_PNode(PNode a, PNode b) {
    return a == b;
}

int DepthFirstSearch(Graph *start_node, OUT PStack_PNode* result) {
    *result = NULL;
    int minimal_path_weight = -1;

    // Init the first path
    PStack_PNode initial_path = Stack_Create_PNode();
    Stack_Push_PNode(initial_path, start_node);

    // Init stack for all the paths
    Stack_PStack_PNode *path_stack = Stack_Create_PStack_PNode();
    Stack_Push_PStack_PNode(path_stack, initial_path);

    while (Stack_Size_PStack_PNode(path_stack) != 0) {
        // Handle path
        PStack_PNode current_path = Stack_Pop_PStack_PNode(path_stack);
        int current_path_weight = CalculatePathWeight(current_path);
        if (*result != NULL && current_path_weight > minimal_path_weight) {
            continue;
        }

#ifdef DEBUG
        // Print current path
        printf("Current path:\n");
        UINT k; for (k = 0; k < Stack_Size_PNode(current_path); ++k) {
            PNode debug_node = Stack_PeekAt_PNode(current_path, k);
            printf("[%d, %d]->", debug_node->position.x, debug_node->position.y);
        } printf("\n");

        // Print path stack
        printf("Current stack:\n");
        UINT kk; for (kk = 0; kk < Stack_Size_PStack_PNode(path_stack); ++kk) {
            PStack_PNode debug_path = Stack_PeekAt_PStack_PNode(path_stack, kk);
            UINT kkk; for (kkk = 0; kkk < Stack_Size_PNode(debug_path); ++kkk) {
                PNode debug_node = Stack_PeekAt_PNode(debug_path, kkk);
                printf("[%d, %d]->", debug_node->position.x, debug_node->position.y);
            } printf("\n");
        } printf("\n");
#endif

        PNode current_node = Stack_Peek_PNode(current_path);

        UINT i; for (i = 0; i < current_node->adjacent_nodes_count; ++i) {
            PNode current_neighbor = current_node->adjacent_nodes[i];
            if (Stack_Find_PNode(current_path, current_neighbor, Predicate_PNode) == -1) {
                // Was not visited
                // Append node to current_path and add it the path_stack
                PStack_PNode new_path = Stack_Create_PNode();
                UINT j; for (j = 0; j < Stack_Size_PNode(current_path); ++j) {
                    Stack_Push_PNode(new_path, Stack_PeekAt_PNode(current_path, j));
                }
                Stack_Push_PNode(new_path, current_neighbor);

                int new_path_weight = current_path_weight + current_neighbor->value;
                if (current_neighbor->position.x == MAX_DIMENSION-1 && current_neighbor->position.y == MAX_DIMENSION-1) {
                    // Found successful path
                    // Update shortest path if found shorted one
                    if (*result == NULL) {
                        *result = new_path;
                        minimal_path_weight = new_path_weight;
                    } else if (minimal_path_weight > new_path_weight) {
                        Stack_Destroy_PNode(*result);
                        *result = new_path;
                        minimal_path_weight = new_path_weight;
                    } else {
                        Stack_Destroy_PNode(new_path);
                    }
                } else if (*result == NULL || minimal_path_weight > new_path_weight ) {
                    Stack_Push_PStack_PNode(path_stack, new_path);
                } else {
                    Stack_Destroy_PNode(new_path);
                }
            }
        }
        Stack_Destroy_PNode(current_path);
    }

    assert(minimal_path_weight == CalculatePathWeight(*result));

    if (*result != NULL) {
        UINT q; for (q = 0; q < Stack_Size_PNode(*result); ++q) {
            PNode current_item = Stack_PeekAt_PNode(*result, q);
            printf("[%d, %d]->", current_item->position.x, current_item->position.y);
        } printf("\n");
        printf("Path length: %d\n", Stack_Size_PNode(*result));
        printf("Path weight: %d\n", minimal_path_weight);
    } else {
        printf("There is no path\n");
    }

    Stack_Destroy_PStack_PNode(path_stack);
    return minimal_path_weight;
}

int CalculatePathWeight(PStack_PNode path) {
    UINT i;
    int path_weight = 0;
    for (i = 0; i < Stack_Size_PNode(path); ++i) {
        PNode current_item = Stack_PeekAt_PNode(path, i);
        path_weight += current_item->value;
    }
    return path_weight;
}
