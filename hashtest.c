//
// Created by sebto on 17/03/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include "hashops.h"
#include "hashtest.h"

int
main(int argc, char **argv) {

    size_t tableSize = 20;
    int *array = (int*)malloc(sizeof(int) * tableSize);
    hashTable_t *table = hashCreate(tableSize, &hashData, &dataCmp);
    for (int i = 0; i < tableSize; i++) {
        hashInsert(table, &array[i]);
    }
    printTable(table, stdout);

    return EXIT_SUCCESS;

}

int
dataCmp(void *int1, void *int2) {
    return *((int*)int1) - *((int*)int2);
}

int
hashData(size_t size, void *data) {
    return *((int*)data) % size;
}

void
printTable(hashTable_t *table, FILE *out) {
    listNode_t *curr = NULL;
    for (int i = 0; i < table->size; i++) {
        printf("Index %d: ", i);
        curr = table->array[i];
        while (curr != NULL) {
            printf("%d, ", *((int*)(curr->data)));
            curr = curr->next;
        }
        printf("\n");
    }
}
