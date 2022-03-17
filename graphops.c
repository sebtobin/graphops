

/* header files */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "graphops.h"
#include "hashops.h"

/* functions */

graph_t*
graphCreate(size_t tableSize, int (*hashData)(size_t, void*), int (*dataCmp)(void*, void*)) {
    graph_t *newGraph = (graph_t*)malloc(sizeof(graph_t));
    assert(newGraph);
    newGraph->nodesTable = hashCreate(tableSize, hashData, dataCmp);
    assert(newGraph->nodesTable);
    newGraph->nNodes = 0;
    return newGraph;
}

graphNode_t*
graphNewNode(void* data) {
    graphNode_t *newNode = (graphNode_t*)malloc(sizeof(graphNode_t));
    assert(newNode);
    newNode->nextNodesSize = INIT_NEXT_NODES_SIZE;
    newNode->nextNodesLength = 0;
    newNode->nextNodes = (graphNode_t**)malloc(sizeof(graphNode_t*) * newNode->nextNodesSize);
    newNode->data = data;
    return newNode;
}

graphNode_t*
graphInsertEdge(graphNode_t *from, graphNode_t *to) {
    if (from->nextNodesLength == from->nextNodesSize) {
        from->nextNodesSize *= 2;
        from->nextNodes = realloc(from->nextNodes, sizeof(graphNode_t*) * from->nextNodesSize);
    }
    from->nextNodes[from->nextNodesLength++] = to;
    return to;
}

graphNode_t*
graphInsertNode(graph_t *graph, void* data, graphNode_t **from, int nFrom, graphNode_t **to, int nTo) {
    graphNode_t *newNode = graphNewNode(data);
    hashInsert(graph->nodesTable, newNode);
    newNode->index = graph->nNodes++;
    int i;
    if (from != NULL) {
        for (i = 0; i < nFrom; i++) {
            graphInsertEdge(from[i], newNode);
        }
    }
    if (to != NULL) {
        for (i = 0; i < nTo; i++) {
            graphInsertEdge(newNode, to[i]);
        }
    }
    return newNode;
}








