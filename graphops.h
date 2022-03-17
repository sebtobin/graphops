
#ifndef GRAPHOPS_H
#define GRAPHOPS_H

/* header files */

#include "hashops.h"

/* structs */

typedef struct graphNode {
    int index;
    struct graphNode **nextNodes;
    size_t nextNodesSize;
    int nextNodesLength;
    void *data;
} graphNode_t;

typedef struct graph {
    hashTable_t *nodesTable;
    int nNodes;
    /* TBD
    graphNode_t **subGraphs;
     */
} graph_t;

/* prototypes */

graph_t* graphCreate(size_t tableSize, int (*hashData)(size_t, void*), int (*dataCmp)(void*, void*));
graphNode_t* graphNewNode(void *data);
graphNode_t* graphInsertEdge(graphNode_t *from, graphNode_t *to);
graphNode_t* graphInsertNode(graph_t *graph, void *data, graphNode_t **from, int nFrom, graphNode_t **to, int nTo);
void freeGraphNode(void *node);
void graphFreeGraph(graph_t *graph);
void graphFreeGraphAndData(graph_t *graph);

#endif
