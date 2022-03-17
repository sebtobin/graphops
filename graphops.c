/* Polymorphic unweighted directional graph implementation in C with create and insert
 * node operations. Each node in the graph can store a pointer to any structure.
 * The graph structure uses a hashtable to store all nodes, allowing O(1) insert
 * and O(1) lookup to retrieve the most recently created node containing the same data.
 * Built such that the insert edge and create node functions do not need to be called
 * directly by the program using the library, thought insert edge may be used for
 * scenarios where edges need to be inserted without inserting any new node.
 *
 * Written by Sebastian Tobin Couzens
 */

/* header files */

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "graphops.h"
#include "hashops.h"

/* macros */

#define INIT_NEXT_NODES_SIZE 1

/* functions */

/* Creates a new graph and returns a graph_t ptr
 * PARAMS:
 * tableSize - size of the hash table to be used to store nodes
 * *hashData - ptr to hash function for hashing nodes, may use node data
 * *dataCmp - cmp function for nodes to be used for node lookup, may use node data
 */
graph_t*
graphCreate(size_t tableSize, int (*hashData)(size_t, void*), int (*dataCmp)(void*, void*)) {
    /* create new hash table struct */
    graph_t *newGraph = (graph_t*)malloc(sizeof(graph_t));
    assert(newGraph);
    /* create hash table to store nodes, initialise nNodes to 0 */
    newGraph->nodesTable = hashCreate(tableSize, hashData, dataCmp);
    assert(newGraph->nodesTable);
    newGraph->nNodes = 0;
    return newGraph;
}

/* Creates a new graph node and returns a graphNode_t ptr
 * PARAMS:
 * *data - void ptr, which points to the data, to be stored in the node
 */
graphNode_t*
graphNewNode(void *data) {
    /* create new node struct */
    graphNode_t *newNode = (graphNode_t*)malloc(sizeof(graphNode_t));
    assert(newNode);
    /* malloc nextNodes array and initialise buddy size and length variable */
    newNode->nextNodesSize = INIT_NEXT_NODES_SIZE;
    newNode->nextNodesLength = 0;
    newNode->nextNodes = (graphNode_t**)malloc(sizeof(graphNode_t*) * newNode->nextNodesSize);
    /* store ptr to the data */
    newNode->data = data;
    return newNode;
}

/* Inserts an edge between 2 nodes in the graph
 * PARAMS:
 * *from - node from which the edge goes
 * *to - node to which the edge goes
 */
graphNode_t*
graphInsertEdge(graphNode_t *from, graphNode_t *to) {
    /* double nextNode array length if no more unused cells */
    if (from->nextNodesLength == from->nextNodesSize) {
        from->nextNodesSize *= 2;
        from->nextNodes = realloc(from->nextNodes, sizeof(graphNode_t*) * from->nextNodesSize);
    }
    /* store ptr in 'from' node toward 'to' node */
    from->nextNodes[from->nextNodesLength++] = to;
    return to;
}

/* Inserts a node into the graph, stores ptr to the data, and creates
 * specified edges from existing nodes
 * PARAMS:
 * *graph - ptr to the graph being modified
 * *data - void ptr, which points to the data, to be stored in the node
 * **from - array of node ptrs whose nodes will point to the new node
 * nFrom - number of node ptrs in **from
 * **to - array of node ptrs to which the new node will point
 * nTo - number of node ptrs in **to
 */
graphNode_t*
graphInsertNode(graph_t *graph, void *data, graphNode_t **from, int nFrom, graphNode_t **to, int nTo) {
    /* create new node with initialised variables, and insert in hashtable */
    graphNode_t *newNode = graphNewNode(data);
    hashInsert(graph->nodesTable, newNode);
    newNode->index = graph->nNodes++;
    int i;
    /* create edges specified in from** and to** arrays */
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

/* Frees a graph node, to be passed to free hash table function
 * to free all nodes in the table
 * PARAMS:
 * *node - node to be freed
 */
void
freeGraphNode(void *node) {
    free(((graphNode_t*)node)->nextNodes);
    free(node);
}

/* Frees a graph node and frees the data void ptr, assumes that the
 * data struct does not include further pointers that need to be freed
 * PARAMS:
 * *node - node to be freed
 */
void
freeGraphNodeAndData(void *node) {
    free(((graphNode_t*)node)->data);
    freeGraphNode(node);
}

/* Frees node table and graph, does not free data
 * PARAMS:
 * *graph - graph to be freed
 */
void
graphFreeGraph(graph_t *graph) {
    hashFreeTableAndData(graph->nodesTable, &graphFreeNode);
    free(graph);
}

/* Frees node table and graph, including data
 * PARAMS:
 * *graph - graph to be freed
 * *freeData - free function for the data
 */
void
graphFreeGraphAndData(graph_t *graph, void (*freeData)(void*)) {
    hashFreeTableAndData(graph->nodesTable, freeData);
    free(graph);
}








