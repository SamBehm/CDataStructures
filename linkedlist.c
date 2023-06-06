#include "linkedlist.h"
#include <stdlib.h>
#include <string.h>

int linklist_generate(LinkedList** list) {
    LinkedList* llist = malloc(sizeof(LinkedList*));
    
    if (llist == NULL) {
        return LINKEDLIST_MEM_ERROR;
    }
    
    llist->head = NULL;
    *list = llist;
    
    return LINKEDLIST_OK;
}

int linklist_clone(LinkedList** dstlist, LinkedList* srclist, size_t dataSize) {
    LinkedList* newlist;
    int error;
    
    if (srclist == NULL) {
        return LINKEDLIST_INVALID_LIST;
    }

    error = linklist_generate(&newlist);
    if (error != LINKEDLIST_OK) {
        return error;
    }

    Node* cnode = srclist->head;
    while (cnode != NULL) {
        error = linklist_add(cnode->data, dataSize, newlist);
        
        if (error != LINKEDLIST_OK) {
            linklist_destroy(&newlist, &free);
            return error;
        }
        
        cnode = cnode->next;
    }
    
    *dstlist = newlist;
    return LINKEDLIST_OK;
}

int linklist_add(void* data, size_t dataSize, LinkedList* list) {
    if (list == NULL) {
        return LINKEDLIST_INVALID_LIST;
    }
    
    Node* newNode, * tail;
    newNode = linklist_createNode(data, dataSize, NULL);
    if (newNode == NULL) {
        return LINKEDLIST_MEM_ERROR;
    }

    tail = list->head;
    if (tail == NULL) {
        list->head = newNode;
        return LINKEDLIST_OK;
    }

    while(tail->next != NULL) {
        tail = tail->next;
    }
    tail->next = newNode;

    return LINKEDLIST_OK;
}

int linklist_prepend(void* data, size_t dataSize, LinkedList* list) {
    if (list == NULL) {
        return LINKEDLIST_INVALID_LIST;
    }

    Node* newNode;
    newNode = linklist_createNode(data, dataSize, list->head);
    if (newNode == NULL) {
        return LINKEDLIST_MEM_ERROR;
    }

    list->head = newNode;
    newNode = NULL;

    return LINKEDLIST_OK;
}

int linklist_insert(int index, void* data, size_t dataSize, LinkedList* list) {
    if (list == NULL) {
        return LINKEDLIST_INVALID_LIST;
    }

    if (index < 0) {
        return LINKEDLIST_INVALID_INDEX;
    }

    Node* newNode, * prevNode = list->head;
    int i = 0;
    while (i < index - 1 && prevNode != NULL) {
        prevNode = prevNode->next;
        i++;
    }

    if (prevNode == NULL) {
        return LINKEDLIST_INVALID_INDEX;
    }

    newNode = linklist_createNode(data, dataSize, prevNode->next);
    if (newNode == NULL) {
        return LINKEDLIST_MEM_ERROR;
    }
    
    prevNode->next = newNode;
    return LINKEDLIST_OK;
}

int linklist_clear(LinkedList* list) {
    return 0;
}

int linklist_size(LinkedList* list) {
    return 0;
}

int linklist_destroy(LinkedList** list, void (*destroyFunction)(void*)) {
    if (list == NULL || *list == NULL) {
        return LINKEDLIST_INVALID_LIST;
    }
    
    LinkedList* dlist = *list;

    Node* cnode = dlist->head, * temp;
    while (cnode != NULL) {
        temp = cnode->next;
        (*destroyFunction)(cnode->data);
        free(cnode);
        cnode = temp;
    }
    temp = NULL;

    free(dlist);
    dlist = NULL;
    *list = NULL;
    return LINKEDLIST_OK;
}

int linklist_indexOf(void* data, LinkedList* list, int (*compare)(void* a, void* b)) {
    return 0;
}

void* linklist_get(int index, LinkedList* list) {
    return NULL;
}

void* linklist_getHead(LinkedList* list) {
    return NULL;
}

void* linklist_getTail(LinkedList* list) {
    return NULL;
}

void* linklist_toArray(LinkedList* list) {
    return NULL;
}

Node* linklist_createNode(void* data, size_t dataSize, Node* next) {
    Node* node = malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }

    node->next = next;
    node->data = malloc(dataSize);
    if (node->data == NULL) {
        return NULL;
    }

    memcpy(node->data, data, dataSize);
    return node;
}
