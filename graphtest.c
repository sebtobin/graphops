
/* header files */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include "graphtest.h"
#include "graphops.h"

/* macros */

#define DEFAULT_ARRAY_SIZE 5

/* main function */

int
main(int argc, char **argv) {

    graph_t *graph = graphCreate(DEFAULT_ARRAY_SIZE, &hashData, &dataCmp);
    int arrayLength = DEFAULT_ARRAY_SIZE;
    int array[5] = {0, 1, 2, 3, 4};
    int i;

    for (i=0; i<arrayLength; i++) {
        printf("%d, ", array[i]);
    }
    printf("\n\n");

    graphNode_t *prev = NULL, *curr = NULL;
    for (i=0; i<arrayLength; i++) {
        curr = graphInsertNode(graph, &array[i], NULL, 0, NULL, 0);
        if (prev != NULL) {
            graphInsertEdge(prev, curr);
        }
        prev = curr;
    }

    printTable(graph->nodesTable, stdout);
    printAdjacencyList(graph, stdout);

    return EXIT_SUCCESS;
}

int
dataCmp(void *graphNode1, void *graphNode2) {
    return *((int*)(((graphNode_t*)graphNode1)->data)) - *((int*)(((graphNode_t*)graphNode2)->data));
}

int
hashData(size_t size, void *graphNode) {
    return *((int*)(((graphNode_t*)graphNode)->data)) % size;
}

void
printAdjacencyList(graph_t *graph, FILE* out) {
    int i, j;
    listNode_t *curr = NULL;
    printf("\nAdjacency List:\n\n");
    for (i = 0; i < graph->nodesTable->size; i++) {
        if ((curr = graph->nodesTable->array[i]) != NULL) {
            while (curr != NULL) {
                fprintf(out, "%d: ", ((graphNode_t*)curr->data)->index);
                for (j = 0; j < ((graphNode_t*)curr->data)->nextNodesLength; j++) {
                    fprintf(out, "%d, ", ((graphNode_t*)curr->data)->nextNodes[j]->index);
                }
                curr = curr->next;
                fprintf(out, "\n");
            }
        }
    }
    printf("\n");
}

void
printTable(hashTable_t *table, FILE *out) {
    listNode_t *curr = NULL;
    printf("\nHash Table:\n\n");
    for (int i = 0; i < table->size; i++) {
        fprintf(out, "Index %d: ", i);
        curr = table->array[i];
        while (curr != NULL) {
            fprintf(out, "%d, ", *((int*)(curr->data)));
            curr = curr->next;
        }
        fprintf(out, "\n");
    }
    printf("\n");
}