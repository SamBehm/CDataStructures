
/* Structures Definitions */

typedef struct Node Node;
typedef struct LinkedList LinkedList;

struct Node {
    void*       data;
    Node*       next;
};

struct LinkedList {
    Node*       head;
};

/* Function Declarations */
LinkedList* linklist_generate(int num_nodes);
LinkedList* linklist_clone(LinkedList* list);
int linklist_add(void* data, LinkedList* list);
int linklist_prepend(void* data, LinkedList* list);
int linklist_insert(int index, void* data, LinkedList* list);
int linklist_clear(LinkedList* list);
int linklist_size(LinkedList* list);
int linklist_destroy(LinkedList* list);
int linklist_indexOf(void* data, LinkedList* list, int (*compare)(void* a, void* b));
void* linklist_head(LinkedList* list);
void* linklist_tail(LinkedList* list);
void** linklist_toArray(LinkedList* list);
