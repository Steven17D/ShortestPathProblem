//
// Created by Steven on 10/13/2017.
//

#include "graph.h"

#ifdef DIAGONAL
#define DEFAULT_NEIGHBOR_COUNT 8
#else
#define DEFAULT_NEIGHBOR_COUNT 4
#endif

int ComparePNode(const void *a, const void *b);

Graph *Graph_Create(const short world_map[MAX_DIMENSION][MAX_DIMENSION]) {
    Node* nodes[MAX_DIMENSION][MAX_DIMENSION] = { NULL };

    SHORT x, y;
    for (x = 0; x < MAX_DIMENSION; ++x) {
        for (y = 0; y < MAX_DIMENSION; ++y) {
            nodes[x][y] = (Node*) malloc(sizeof(Node));
            POINTS p; p.x = x; p.y = y;
            nodes[x][y]->position = p;
            nodes[x][y]->value = world_map[x][y];
            nodes[x][y]->adjacent_nodes = (Node**) malloc(sizeof(Node*) * DEFAULT_NEIGHBOR_COUNT);
        }
    }

    for (x = 0; x < MAX_DIMENSION; ++x) {
        for (y = 0; y < MAX_DIMENSION; ++y) {
            unsigned short counter = 0;
#ifdef DIAGONAL
            int neighbors[DEFAULT_NEIGHBOR_COUNT][2] = {
                    {x-1, y+1}, {x, y+1}, {x+1, y+1},
                    {x-1, y},             {x+1, y},
                    {x-1, y-1}, {x, y-1}, {x+1, y-1}
            };
#else
            int neighbors[DEFAULT_NEIGHBOR_COUNT][2] = {
                                {x, y+1},
                    {x-1, y},             {x+1, y},
                                {x, y-1}
            };
#endif
            int i;
            int neighbor_x, neighbor_y;
            for (i = 0; i < DEFAULT_NEIGHBOR_COUNT; ++i) {
                neighbor_x = neighbors[i][0], neighbor_y = neighbors[i][1];
                if ((neighbor_x >= 0 && neighbor_x < MAX_DIMENSION) && (neighbor_y >= 0 && neighbor_y < MAX_DIMENSION)) {
                    // On board
                    nodes[x][y]->adjacent_nodes[counter] = nodes[neighbor_x][neighbor_y];
                    ++counter;
                }
            }

            nodes[x][y]->adjacent_nodes = realloc(nodes[x][y]->adjacent_nodes, sizeof(Node*) * counter);
            nodes[x][y]->adjacent_nodes_count = counter;

            qsort(nodes[x][y]->adjacent_nodes, nodes[x][y]->adjacent_nodes_count, sizeof(Node*), ComparePNode);
        }
    }

    return nodes[0][0];
}

define_Stack(PGraph)

BOOL Predicate_PGraph(PGraph a, PGraph b) { return a == b; }

void __Graph_Destroy(PGraph node, Stack_PGraph* stack) {
    if (Stack_Find_PGraph(stack, node, Predicate_PGraph) != -1) {
        // Node was visited
        return;
    }
    Stack_Push_PGraph(stack, node);
    int i;
    for (i = 0; i < node->adjacent_nodes_count; ++i) {
        __Graph_Destroy(node->adjacent_nodes[i], stack);
    }
}

void Graph_Destroy(PGraph graph) {
    Stack_PGraph* stack = Stack_Create_PGraph();
    __Graph_Destroy(graph, stack);
    Node* currentNode;
    UINT i;
    for (i = 0; i < Stack_Size_PGraph(stack); ++i) {
        currentNode = Stack_PeekAt_PGraph(stack, i);
        free(currentNode->adjacent_nodes);
        free(currentNode);
    }
    Stack_Destroy_PGraph(stack);
}

int ComparePNode(const void *a, const void *b) {
    return ((*(PNode*)a)->value - (*(PNode*)b)->value);
}
