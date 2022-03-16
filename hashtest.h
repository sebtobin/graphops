#ifndef HASHTEST_H
#define HASHTEST_H

void printTable(hashTable_t *table, FILE *out);
int hashData(size_t size, void *data);
int dataCmp(void *int1, void *int2);

#endif
