
#ifndef GRAPHTEST_H
#define GRAPHTEST_H

#include "graphops.h"

int hashData(size_t size, void *graphNode);
int dataCmp(void *graphNode1, void *graphNode2);
void printAdjacencyList(graph_t *graph, FILE* out);
void printTable(hashTable_t *table, FILE *out);

#endif
