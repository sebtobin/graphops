
#ifndef GRAPHOPS_H
#define GRAPHOPS_H

/* header files */

#include "hashops.h"

/* macros */

#define INIT_NEXT_NODES_SIZE 1

/* structs */

typedef struct graphNode {
    int index;
    struct graphNode **nextNodes;
    size_t nextNodesSize;
    int nextNodesLength;
    void* data;
} graphNode_t;

typedef struct graph {
    hashTable_t *nodesTable;
    int nNodes;
    /* to be implemented
    graphNode_t **subGraphs;
     */
} graph_t;

/* prototypes */

graph_t* graphCreate(size_t tableSize, int (*hashData)(size_t, void*), int (*dataCmp)(void* data1, void *data2));
graphNode_t* graphNewNode(void* data);
graphNode_t* graphInsertEdge(graphNode_t *from, graphNode_t *to);
graphNode_t* graphInsertNode(graph_t *graph, void* data, graphNode_t **from, int nFrom, graphNode_t **to, int nTo);

#endif
