#include "../linkedlist.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define NUM_NODES 5

void test_generate(void);
void test_add(void);
void test_clone(void);
void test_prepend(void);
void test_insert(void);
void test_clear(void);
void test_size(void);
void test_destroy(void);
void test_indexOf(void);
void test_get(void);
void test_getHead(void);
void test_getTail(void);
void test_toArray(void);

int compareIntegers(void* a, void* b);

int main(void) {
    test_generate();
    test_destroy();
    test_add();
    test_clone();
    test_prepend();
    test_insert();

    printf("All Tests Cleared!\n");
    fflush(stdout);
    return 0;
}

void test_generate(void) {
    LinkedList* list;
    int error = linklist_generate(&list);

    assert(error == LINKEDLIST_OK);
    assert(list != NULL);
    assert(list->head == NULL);
}

void test_destroy(void) {
    LinkedList* list;
    int error;

    linklist_generate(&list);
    assert(list != NULL);

    error = linklist_destroy(&list, &free);
    assert(list == NULL);
    assert(error == LINKEDLIST_OK);

    error = linklist_destroy(&list, &free);
    assert(error == LINKEDLIST_INVALID_LIST);
}

void test_add(void) {
    
    /* Test normal use */
    LinkedList* list;
    int error;

    linklist_generate(&list);

    for (int i = 0; i < NUM_NODES; i++) {
        error = linklist_add(&i, sizeof(int), list);
        assert(error == LINKEDLIST_OK);
    }

    Node* head = list->head; 
    for (int i = 0; i < NUM_NODES; i++) {
        assert(*((int *)head->data) == i);
        head = head->next;
    }

    assert(head == NULL);
    linklist_destroy(&list, &free);
    
    int data = 1;
    error = linklist_add(&data, sizeof(int), list);
    
    assert(error == LINKEDLIST_INVALID_LIST);
}

void test_clone(void) {
    LinkedList* list, * list2;
    int error;
    
    linklist_generate(&list);

    for (int i = 0; i < NUM_NODES; i++) {
        linklist_add(&i, sizeof(int), list);
    }

    error = linklist_clone(&list2, list, sizeof(int));
    assert(error == LINKEDLIST_OK);
    assert(list2 != NULL);
    assert(list != list2);
    
    Node* head = list->head, * head2 = list2->head;
    for (int i = 0; i < NUM_NODES; i++) {
        assert(head2 != NULL);
        assert(*((int *)head2->data) == *((int *)head->data));
        head2 = head2->next;
        head = head->next;
    }

    assert(head2 == NULL);

    linklist_destroy(&list, &free);
    linklist_destroy(&list2, &free);
    
    linklist_generate(&list);
    error = linklist_clone(&list2, list, sizeof(int));
    assert(error == LINKEDLIST_OK);
    assert(list2->head == NULL);
    
    linklist_destroy(&list, &free);
    linklist_destroy(&list2, &free);

    error = linklist_clone(&list2, list, sizeof(int));
    assert(error == LINKEDLIST_INVALID_LIST);
}

void test_prepend(void) {
    LinkedList* list;
    int a = 1, b = 2, error;
    linklist_generate(&list);

    linklist_add(&a, sizeof(int), list);
    error = linklist_prepend(&b, sizeof(int), list);

    assert(error == LINKEDLIST_OK);
    assert(*((int *)list->head->data) == b);
    linklist_destroy(&list, &free);

    error = linklist_prepend(&a, sizeof(int), list);
    assert(error == LINKEDLIST_INVALID_LIST);
}

void test_insert(void) {
    LinkedList* list;
    linklist_generate(&list);
    int ins_data = 100, errno;
    
    for (int i = 0; i < NUM_NODES; i++) {
        linklist_add(&i, sizeof(int), list);
    }
    
    /* Test invalid index */
    errno = linklist_insert(-1, &ins_data, sizeof(int), list);
    assert(errno == LINKEDLIST_INVALID_INDEX);

    Node* head = list->head;
    for (int i = 0; i < NUM_NODES; i++) {
        assert(*((int *)head->data) == i);
        head = head->next;
    }

    /* Test normal use */
    int insertionIndex = 2;
    errno = linklist_insert(insertionIndex, &ins_data, sizeof(int), list);
    assert(errno == LINKEDLIST_OK);

    head = list->head;
    int rev_step = 0;
    for (int i = 0; i < NUM_NODES + 1; i++) {
        assert(head != NULL);
        if (i == insertionIndex) {
            assert(*((int *)head->data) == ins_data);
            head = head->next;
            rev_step = 1;
            continue;
        }
        assert(*((int *)head->data) == i - rev_step);
        head = head->next;
    }

    linklist_destroy(&list, &free);
}

void test_clear(void) {
    LinkedList* list;
    linklist_generate(&list);
    int error;

    for (int i = 0; i < NUM_NODES; i++) {
        linklist_add(&i, sizeof(int), list);
    }

    error = linklist_clear(list);

    assert(error == LINKEDLIST_OK);
    assert(list != NULL);
    assert(list->head == NULL);

    linklist_destroy(&list, &free);
    error = linklist_clear(list);
    assert(error == LINKEDLIST_INVALID_LIST);
}

void test_size(void) {
    LinkedList* list;
    linklist_generate(&list);
    
    for (int i = 0; i < NUM_NODES; i++) {
        linklist_add(&i, sizeof(int), list);
    }

    int size = linklist_size(list);
    assert(size == NUM_NODES);

    linklist_clear(list);
    
    size = linklist_size(list);
    assert(size == 0);

    linklist_destroy(&list, &free);
    assert(size == 0);
}

void test_indexOf(void) {
    LinkedList* list;
    linklist_generate(&list);

    for (int i = 0; i < NUM_NODES; i++) {
        linklist_add(&i, sizeof(int), list);
    }

    int index;
    for (int i = 0; i < NUM_NODES; i++) {
        index = linklist_indexOf(&i, list, (int (*)(void*, void*))&compareIntegers);
        assert(index == i);
    }
    
    int val = NUM_NODES;
    index = linklist_indexOf(&val, list, (int (*)(void*, void*))&compareIntegers);
    assert(index == LINKEDLIST_INVALID_INDEX);
    linklist_destroy(&list, &free);

    index = linklist_indexOf(&val, list, (int (*)(void*, void*))&compareIntegers);
    assert(index == LINKEDLIST_INVALID_LIST);
}

void test_get(void) {
    LinkedList* list;
    linklist_generate(&list);

    for (int i = 0; i < NUM_NODES; i++) {
        linklist_add(&i, sizeof(int), list);
    }

    int* val;
    for (int i = 0; i < NUM_NODES; i++) {
        val = (int*) linklist_get(i, list);
        assert(val != NULL);
        assert(*val == i);
    }

    val = (int*) linklist_get(NUM_NODES, list);
    assert(val == NULL);

    linklist_clear(list);
    val = (int*) linklist_get(NUM_NODES - 1, list);
    assert(val == NULL);

    linklist_destroy(&list, &free);
}


void test_getHead(void) {
    LinkedList* list;
    linklist_generate(&list);
    int* val;

    val = (int*) linklist_getHead(list);
    assert(val == NULL);

    for (int i = 0; i < NUM_NODES; i++) {
        linklist_add(&i, sizeof(int), list);
    }

    val = (int*) linklist_getHead(list);
    assert(val != NULL);
    assert(*val == 0);

    linklist_clear(list);
    val = (int*) linklist_getHead(list);
    assert(val == NULL);

    linklist_destroy(&list, &free);
}

void test_getTail(void) {
    LinkedList* list;
    linklist_generate(&list);
    int* val;

    val = (int*) linklist_getTail(list);
    assert(val == NULL);

    for (int i = 0; i < NUM_NODES; i++) {
        linklist_add(&i, sizeof(int), list);
    }

    val = (int*) linklist_getTail(list);
    assert(val != NULL);
    assert(*val == NUM_NODES - 1);

    linklist_clear(list);
    val = (int*) linklist_getTail(list);
    assert(val == NULL);
    linklist_destroy(&list, &free);
}

void test_toArray(void) {
    LinkedList* list;
    linklist_generate(&list);
    int* array, values[NUM_NODES];
    
    array = (int*) linklist_toArray(list);
    assert(array == NULL);

    for (int i = 0; i < NUM_NODES; i++) {
        values[i] = i;
        linklist_add(&i, sizeof(int), list);
    }


    array = (int*) linklist_toArray(list);
    assert(array != NULL);

    for (int i = 0; i < NUM_NODES; i++) {
        assert(array[i] == values[i]);
    }

    free(array);
    linklist_destroy(&list, &free);
}

int compareIntegers(void* a, void* b) {
    int ia = *(int*) a;
    int ib = *(int*) b;
    
    return ia - ib;
}
