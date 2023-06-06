/* Structures and Enums Definitions */
typedef struct Node Node;
typedef struct LinkedList LinkedList;

enum {
    LINKEDLIST_INVALID_INDEX = -2,
    LINKEDLIST_INVALID_LIST,
    LINKEDLIST_OK,
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
int linklist_clone(LinkedList** dstlist, LinkedList* srclist);
int linklist_add(void* data, LinkedList* list);
int linklist_prepend(void* data, LinkedList* list);
int linklist_insert(int index, void* data, LinkedList* list);
int linklist_clear(LinkedList* list);
int linklist_size(LinkedList* list);
int linklist_destroy(LinkedList** list);
int linklist_indexOf(void* data, LinkedList* list, int (*compare)(void* a, void* b));
void* linklist_get(int index, LinkedList* list);
void* linklist_getHead(LinkedList* list);
void* linklist_getTail(LinkedList* list);
void* linklist_toArray(LinkedList* list);
