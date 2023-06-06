#include "../linkedlist.h"
#include <stdio.h>
#include <assert.h>

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
void test_getHead(void);
void test_getTail(void);
void test_toArray(void);

int main(void) {
    test_generate();    
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

    error = linklist_destroy(&list);
    assert(list == NULL);
    assert(error == LINKEDLIST_OK);

    error = linklist_destroy(&list);
    assert(error == LINKEDLIST_INVALID_LIST);
}

void test_add(void) {
    
    /* Test normal use */
    LinkedList* list;
    int error;

    linklist_generate(&list);

    for (int i = 0; i < NUM_NODES; i++) {
        error = linklist_add(&i, list);
        assert(error == LINKEDLIST_OK);
    }

    Node* head = list->head; 
    for (int i = 0; i < NUM_NODES; i++) {
        assert(*((int *)head->data) == i);
        head = head->next;
    }

    assert(head == NULL);
    linklist_destroy(&list);
    
    int data = 1;
    error = linklist_add(&data, list);
    
    assert(error == LINKEDLIST_INVALID_LIST);
}

void test_clone(void) {
    LinkedList* list, * list2;
    int error;
    
    linklist_generate(&list);

    for (int i = 0; i < NUM_NODES; i++) {
        linklist_add(&i, list);
    }

    error = linklist_clone(&list2, list);
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

    assert(head2 != NULL);

    linklist_destroy(&list);
    linklist_destroy(&list2);
    
    linklist_generate(&list);
    error = linklist_clone(&list2, list);
    assert(error == LINKEDLIST_OK);
    assert(list2->head == NULL);
    
    linklist_destroy(&list);
    linklist_destroy(&list2);

    error = linklist_clone(&list2, list);
    assert(error == LINKEDLIST_INVALID_LIST);
}

void test_prepend(void) {
    LinkedList* list;
    int a = 1, b = 2, error;
    linklist_generate(&list);

    linklist_add(&a, list);
    error = linklist_prepend(&b, list);

    assert(error == LINKEDLIST_OK);
    assert(*((int *)list->head->data) == b);
    linklist_destroy(&list);

    linklist_prepend(&a, list);
    assert(error == LINKEDLIST_INVALID_LIST);
}

void test_insert(void) {
    LinkedList* list;
    linklist_generate(&list);
    int ins_data = 100, errno;
    
    for (int i = 0; i < NUM_NODES; i++) {
        linklist_add(&i, list);
    }
    
    /* Test invalid index */
    errno = linklist_insert(-1, &ins_data, list);
    assert(errno == LINKEDLIST_INVALID_INDEX);

    Node* head = list->head;
    for (int i = 0; i < NUM_NODES; i++) {
        assert(*((int *)head->data) == i);
        head = head->next;
    }

    /* Test normal use */
    errno = linklist_insert(3, &ins_data, list);
    assert(errno == LINKEDLIST_OK);

    head = list->head;
    int rev_step = 0;
    for (int i = 0; i < NUM_NODES + 1; i++) {
        assert(head != NULL);
        if (i == 2) {
            assert(*((int *)head->data) == ins_data);
            head = head->next;
            rev_step = 1;
            continue;
        }
        assert(*((int *)head->data) == i - rev_step);
        head = head->next;
    }

    linklist_destroy(&list);
}

void test_clear(void) {
    LinkedList* list;
    linklist_generate(&list);
    int error;

    for (int i = 0; i < NUM_NODES; i++) {
        linklist_add(&i, list);
    }

    error = linklist_clear(list);

    assert(error == LINKEDLIST_OK);
    assert(list != NULL);
    assert(list->head == NULL);

    linklist_destroy(&list);
    error = linklist_clear(list);
    assert(error == LINKEDLIST_INVALID_LIST);
}

void test_size(void) {
    LinkedList* list;

    linklist_generate(&list);
    
    for (int i = 0; i < NUM_NODES; i++) {
        linklist_add(&i, list);
    }

    int size = linklist_size(list);
    assert(size == NUM_NODES);

    linklist_clear(list);
    
    size = linklist_size(list);
    assert(size == 0);

    linklist_destroy(&list);
    assert(size == 0);
}

void test_indexOf(void) {

}

void test_getHead(void) {

}

void test_getTail(void) {

}

void test_toArray(void) {

}
