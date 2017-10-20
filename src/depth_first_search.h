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
typedef Stack_PNode* Path;
define_Stack(Path)

int CalculatePathWeight(Path path) {
    UINT i;
    int path_weight = 0;
    for (i = 0; i < Stack_Size_PNode(path); ++i) {
        PNode current_item = Stack_PeekAt_PNode(path, i);
        path_weight += current_item->value;
    }
    return path_weight;
}

BOOL Predicate_PNode(PNode a, PNode b) {
    return a == b;
}

int PNode_formatter(String *str, PNode item) {
    String_Reserve(str, 32);
    int size = sprintf(String_CStr(str), "[%d, %d]", item->position.x, item->position.y);
    String_ShrinkToFit(str);
    return size;
}

int Path_formatter(String *str, Path item) {
    String_Reserve(str, 32);
    String *PNode_delimiter = String_CreateCopy("->");
    int size = Stack_format_PNode(item, str, PNode_formatter, PNode_delimiter);
    String_Destroy(PNode_delimiter);
    String_ShrinkToFit(str);
    return size;

}

int DepthFirstSearch(Graph *start_node, OUT Path* result) {
    *result = NULL;
    int minimal_path_weight = -1;

    // Init the first path
    Path initial_path = Stack_Create_PNode();
    Stack_Push_PNode(initial_path, start_node);

    // Init stack for all the paths
    Stack_Path *path_stack = Stack_Create_Path();
    Stack_Push_Path(path_stack, initial_path);

    while (Stack_Size_Path(path_stack) != 0) {
        // Handle path
        Path current_path = Stack_Pop_Path(path_stack);
        int current_path_weight = CalculatePathWeight(current_path);
        if (*result != NULL && current_path_weight > minimal_path_weight) {
            continue;
        }

#ifdef DEBUG
        // Print current path
        printf("Current path:\n");
        String* current_path_str = String_Create();
        String* PNode_delimiter_str = String_CreateCopy("->");
        Stack_format_PNode(current_path, current_path_str, PNode_formatter, PNode_delimiter_str);
        String_Destroy(PNode_delimiter_str);
        printf(String_CStr(current_path_str));
        String_Destroy(current_path_str);
        printf("\n");

        // Print path stack
        printf("Current stack:\n");
        String* current_stack_str = String_Create();
        String *Path_delimiter_str = String_CreateCopy("\n");
        Stack_format_Path(path_stack, current_stack_str, Path_formatter, Path_delimiter_str);
        String_Destroy(Path_delimiter_str);
        printf(String_CStr(current_stack_str));
        String_Destroy(current_stack_str);
        printf("\n");
#endif

        PNode current_node = Stack_Peek_PNode(current_path);

        UINT i; for (i = 0; i < current_node->adjacent_nodes_count; ++i) {
            PNode current_neighbor = current_node->adjacent_nodes[i];
            if (Stack_Find_PNode(current_path, current_neighbor, Predicate_PNode) == -1) {
                // Was not visited
                // Append node to current_path and add it the path_stack
                Path new_path = Stack_Create_PNode();
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
                    Stack_Push_Path(path_stack, new_path);
                } else {
                    Stack_Destroy_PNode(new_path);
                }
            }
        }
        Stack_Destroy_PNode(current_path);
    }

    if (*result != NULL) {
        String* shortest_path_str = String_Create();
        String* shortest_path_delimiter = String_CreateCopy("->");
        Stack_format_PNode(*result, shortest_path_str, PNode_formatter, shortest_path_delimiter);
        String_Destroy(shortest_path_delimiter);
        printf("Shortest path: %s\n", String_CStr(shortest_path_str));
        String_Destroy(shortest_path_str);
        printf("Path length: %d\n", Stack_Size_PNode(*result));
        printf("Path weight: %d\n", minimal_path_weight);
    } else {
        printf("There is no path\n");
    }

    Stack_Destroy_Path(path_stack);
    return minimal_path_weight;
}
