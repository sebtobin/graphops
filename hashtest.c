
/* header files */

#include <stdio.h>
#include <stdlib.h>
#include "hashops.h"
#include "hashtest.h"

/* functions */

int
main(int argc, char **argv) {

    size_t tableSize = 6;
    int *array = (int*)malloc(sizeof(int) * tableSize);
    /* manual array modification for testing */
    array[2] = 2; array[5] = 22;

    /* creating hash table and inserting array contents */
    hashTable_t *table = hashCreate(tableSize, &hashData, &dataCmp);
    for (int i = 0; i < tableSize; i++) {
        hashInsert(table, &array[i]);
    }

    /* printing hash table */
    printTable(table, stdout);

    /* freeing hash table */
    hashFreeTable(table);

    return EXIT_SUCCESS;

}

/* cmp function for int, with int ptr params */
int
dataCmp(void *intPtr1, void *intPtr2) {
    return *((int*)intPtr1) - *((int*)intPtr2);
}

/* hash function for int, using % of size, with int ptr param,  */
int
hashData(size_t size, void *data) {
    return *((int*)data) % size;
}

/* function to print hash table to a file */
void
printTable(hashTable_t *table, FILE *out) {
    listNode_t *curr = NULL;
    fprintf(out, "Hash Table:\n\n");
    for (int i = 0; i < table->size; i++) {
        fprintf(out, "Index %d: ", i);
        curr = table->array[i];
        while (curr != NULL) {
            fprintf(out, "%d, ", *((int*)(curr->data)));
            curr = curr->next;
        }
        fprintf(out, "\n");
    }
    fprintf(out, "\n");
}
