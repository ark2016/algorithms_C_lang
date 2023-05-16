#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <limits.h>

struct Elem {
    struct Elem *prev, *next;
    int v;
};


struct Elem *initDoubleLinkedList() {
    struct Elem *l = (struct Elem *) malloc(sizeof(struct Elem));
    (*l).prev = l;
    (*l).next = l;
    return l;
}

bool listEmpty(struct Elem *l) {
    return l->next == l;
}

size_t listLength(struct Elem *l) {
    int len = 0;
    struct Elem *x = l;
    while (x->next != l) {
        ++len;
        x = x->next;
    }
    return len;
}

/*
struct Elem * listSearch(struct Elem *l, struct Elem *v){
    struct Elem  *x = l->next;
    while (x != l && x->v != v){
        x = x->next;
    }
}
*/

void insertAfter(struct Elem *x, struct Elem *y) {
    struct Elem *z = x->next;
    x->next = y;
    y->prev = x;
    y->next = z;
    z->prev = y;
}

void delete(struct Elem *pElem) {
    if (listEmpty(pElem)) {
        printf("ERROR: empty list\n");
    }
    struct Elem *a_elem, *b_elem;
    a_elem = pElem->prev;
    b_elem = pElem->next;
    a_elem->next = b_elem;
    b_elem->prev = a_elem;
    pElem->prev = NULL;
    pElem->next = NULL;
}

void insertSort(struct Elem *structElem) {
    struct Elem *next = structElem->next;
    struct Elem *loc = next->prev;
    while (next != structElem) {
        while (loc != structElem && next->v < loc->v)
            loc = loc->prev;
        delete(next);
        insertAfter(loc, next);
        next = next->next;
        loc = next->prev;
    }
}

int main() {
    int number;
    scanf("%d", &number);
    struct Elem *doubleLinkedList = initDoubleLinkedList();
    struct Elem *elem = malloc(number * sizeof(struct Elem));
    for (int i = 0; i < number; ++i) {
        int now;
        scanf("%d", &now);
        elem[i].v = now;
        insertAfter(doubleLinkedList->prev, &elem[i]);
    }
    insertSort(doubleLinkedList);
    struct Elem *next = doubleLinkedList->next;
    while (next != doubleLinkedList) {
        printf("%d\n", next->v);
        next = next->next;
    }
    free(elem);
    free(doubleLinkedList);
    elem = NULL;
    doubleLinkedList = NULL;
    return 0;
}
