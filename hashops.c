/* Polymorphic hashtable implementation in C, with create, insert, lookup,
 * delete and free operations. Uses linked list chaining for collision handling.
 * No prevention for the insertion of duplicate data. Insert, lookup and delete
 * all take void* data as a parameter, rather than a <key, pair> implementation.
 *
 * Written by Sebastian Tobin-Couzens
 */

/* header files */

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "hashops.h"

/* functions */

/* Creates a new hash table and returns a hashTable_t pointer
 * PARAMS:
 * size - size of table array, prime number recommended to reduce collisions
 * *hashData - hash function for the data
 * *dataCmp - cmp function for the data, return 0 for equal, else return not 0
 */
hashTable_t*
hashCreate(size_t size, int (*hashData)(size_t, void*), int (*dataCmp)(void*, void*)) {
    /* create new hash table struct */
    hashTable_t *table = (hashTable_t*)malloc(sizeof(hashTable_t));
    assert(table);
    /* set size, function ptrs and allocate array of said size */
    table->size = size;
    table->array = (listNode_t**)calloc(size, sizeof(listNode_t*));
    table->hashData = hashData;
    table->dataCmp = dataCmp;
    assert(table->array);
    return table;
}

/* Inserts data into the hash table, returns the linked list node for the data,
 * else returns NULL if *data is NULL
 * PARAMS:
 * *table - the table into which the data is being inserted
 * *data - the data to be inserted
 */
listNode_t*
hashInsert(hashTable_t *table, void *data) {
    /* return NULL if no data is given */
    if (! data) return NULL;
    /* get array index for the data using hash function */
    int index = table->hashData(table->size, data);
    /* malloc a new linked list node */
    listNode_t *newNode = (listNode_t*)malloc(sizeof(listNode_t));
    assert(newNode);
    /* point the new linked list node to list head */
    newNode->next = table->array[index];
    /* said new linked list node as head of the list */
    table->array[index] = newNode;
    /* store the address of the data in the new node */
    newNode->data = data;
    return newNode;
}

/* Looks up data, returns the linked list node of the data if a match is found,
 * else returns null if *data is null or no match is found
 * PARAMS:
 * *table - the table in which the data is being searched
 * *data - the data to be looked up
 */
listNode_t*
hashLookup(hashTable_t *table, void *data) {
    /* return NULL if no data is given */
    if (! data) return NULL;
    /* hash data and get its array index */
    int index = table->hashData(table->size, data);
    listNode_t *curr = table->array[index];
    /* loop through linked list, return void ptr to data if there is a match */
    while (curr != NULL) {
        if (! table->dataCmp(data, curr->data)) {
            return curr;
        }
        curr = curr->next;
    }
    /* return NULL if no match is found */
    return NULL;
}

/* Deletes and frees the first (most recently inserted) linked list node
 * containing *data from the table, returns the data ptr
 * PARAMS:
 * *table - the table in which the data is being deleted
 * *data - the data for which the containing node will be deleted
 */
void*
hashDelete(hashTable_t *table, void *data) {
    /* return NULL if no data is given */
    if (! data) return NULL;
    /* hash data and get its array index */
    int index = table->hashData(table->size, data);
    listNode_t *curr = table->array[index];
    listNode_t *prev = NULL;
    /* loop through linked list, return void ptr to data if there is a match */
    while (curr != NULL) {
        if (! table->dataCmp(data, curr->data)) {
            if (prev) {
                prev->next = curr->next;
            }
            else {
                table->array[index] = curr->next;
            }
            void* temp = curr->data;
            free(curr);
            return temp;
        }
        prev = curr;
        curr = curr->next;
    }
    return NULL;
}

/* Frees a hashtable and the contained array of pointers,
 * does not free the data
 * PARAMS:
 * *table - the table being freed
 */
void
hashFreeTable(hashTable_t *table) {
    /* free each linked list at each array index */
    for (int i = 0; i < table->size; i++) {
        hashFreeList(table->array[i]);
    }
    /* free array and the table itself */
    free(table->array);
    free(table);
}

/* Frees a hashtable and the contained array of pointers,
 * including the data
 * PARAMS:
 * *table - the table being freed
 * *freeData - function ptr to data specific free function
 */
void
hashFreeTableAndData(hashTable_t *table, void (*freeData)(void*)) {
    /* free each linked list at each array index */
    for (int i = 0; i < table->size; i++) {
        hashFreeListAndData(table->array[i], freeData);
    }
    /* free array and the table itself */
    free(table->array);
    free(table);
}

/* Frees a linked list, does not free data, for when data wasn't
 * malloc'd or freeing can be handled by calling program
 * PARAMS:
 * *head - head of the linked list
 */
void
hashFreeList(listNode_t *head) {
    listNode_t *prev = NULL;
    /* loop through and free all nodes and data in the list */
    while (head != NULL) {
        prev = head;
        head = head->next;
        free(prev);
    }
}

/* Frees a linked list, including the data ptr at each node
 * PARAMS:
 * *head - head of the linked list
 * *freeData - function ptr to data specific free function
 */
void
hashFreeListAndData(listNode_t *head, void (*freeData)(void*)) {
    listNode_t *prev = NULL;
    /* loop through and free all nodes and data in the list */
    while (head != NULL) {
        prev = head;
        head = head->next;
        freeData(prev->data);
        free(prev);
    }
}




