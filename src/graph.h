//
// Created by Steven on 10/13/2017.
//

#include <malloc.h>
#include <afxres.h>
#include "properties.h"
#include "stack.h"

#ifndef SHORTESTPATHPROBLEM_GRAPH_H
#define SHORTESTPATHPROBLEM_GRAPH_H

typedef struct Node {
    POINTS position;
    short value;

    UINT adjacent_nodes_count;
    struct Node** adjacent_nodes; // Array of pointers to nodes
} Graph, Node;

typedef Graph* PGraph;
typedef Node* PNode;

Graph* Graph_Create(const short world_map[MAX_DIMENSION][MAX_DIMENSION]);
void Graph_Destroy(PGraph graph);

#endif //SHORTESTPATHPROBLEM_GRAPH_H
