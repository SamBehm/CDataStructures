#include <stddef.h>

/* Structures and Enums Definitions */
typedef struct Node Node;
typedef struct LinkedList LinkedList;

enum {
    LINKEDLIST_INVALID_INDEX = -2,
    LINKEDLIST_INVALID_LIST,
    LINKEDLIST_OK,
    LINKEDLIST_MEM_ERROR,
};

struct Node {
    void*       data;
    Node*       next;
};

struct LinkedList {
    Node*       head;
};

/* Function Declarations */
int linklist_generate(LinkedList** list);
int linklist_clone(LinkedList** dstlist, LinkedList* srclist, size_t dataSize);
int linklist_add(void* data, size_t dataSize, LinkedList* list);
int linklist_prepend(void* data, size_t dataSize, LinkedList* list);
int linklist_insert(int index, void* data, size_t dataSize, LinkedList* list);
int linklist_clear(LinkedList* list);
int linklist_size(LinkedList* list);
int linklist_destroy(LinkedList** list, void (*destroyFunction)(void*));
int linklist_indexOf(void* data, LinkedList* list, int (*compare)(void* a, void* b));
void* linklist_get(int index, LinkedList* list);
void* linklist_getHead(LinkedList* list);
void* linklist_getTail(LinkedList* list);
void* linklist_toArray(LinkedList* list);
