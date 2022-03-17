
#ifndef HASHOPS_H
#define HASHOPS_H

/* structs */

typedef struct listNode {
    struct listNode *next;
    void *data;
} listNode_t;

typedef struct {
    listNode_t **array;
    size_t size;
    int (*hashData)(size_t, void*);
    int (*dataCmp)(void* data1, void *data2);
} hashTable_t;

/* prototypes */

hashTable_t* hashCreate(size_t size, int (*hashData)(size_t, void*), int (*dataCmp)(void*, void*));
listNode_t* hashInsert(hashTable_t *table, void *data);
listNode_t* hashLookup(hashTable_t *table, void *data);
void* hashDelete(hashTable_t *table, void *data);
void hashFreeTable(hashTable_t *table);
void hashFreeTableAndData(hashTable_t *table, void (*freeData)(void*));
void hashFreeList(listNode_t *head);
void hashFreeListAndData(listNode_t *head, void (*freeData)(void*));


#endif
