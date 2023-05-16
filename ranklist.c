#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <malloc.h>
#include <stdlib.h>

#define SIZE_OF_ARRAY 1000001
#define DEFAULT_OPERATIONS 4
#define OPERATION_NAME_SIZE 7
#define STRING_SIZE 16

typedef struct Pair {
    int k;
    char *v;
} Pair;

typedef struct Tree {
    int *cell_height;
    Pair key;
    struct Tree **next;
    struct Tree **previous;
} Tree;

Tree *initSkipList(int m);

bool mapEmpty(Tree l);

Tree *succ(Tree *x);

Tree **skip(Tree *l, int m, int k, Tree **p);

int operationRecognition(int m, Tree *l, Tree *tree, int *array_of_heights, Tree **p,
                         char *operation, int j);

char *lookup(Tree *l, int m, int k, Tree **p);

void insert(Tree *l, int m, int k, Tree *x, Tree **p, int *array_of_heights);

void change(Tree *x, Tree *const *p, const int *array_of_heights, int i);

void delete(Tree *l, int m, int k, Tree **p);

int rank(Tree *l, int m, int k);

int gettingOperationNumber(char *operation);

void freeAndNull(int j, int *array_of_heights, Tree *l, Tree *tree, Tree **p);

void arrayOfHeightsUPD(Tree *l, int m, int k, int *array_of_heights);
//void freeTree(Tree *tree, int j);

int main() {
//    int n, m, j;
    int j, m;
    char operation[OPERATION_NAME_SIZE];
//    scanf("%d", &n);
    m = log2(SIZE_OF_ARRAY);
    int *array_of_heights = malloc(m * sizeof(int));
    Tree *l = initSkipList(m);
    Tree *tree = malloc(SIZE_OF_ARRAY * sizeof(Tree));
    Tree **pTree = malloc(m * sizeof(Tree *));
    j = 0;
    while (true) {
        scanf("%s", operation);
        if (0 == (strcmp(operation, "END"))) {
            break;
        }
        j = operationRecognition(m, l, tree, array_of_heights, pTree, operation, j);
    }
    freeAndNull(j, array_of_heights, l, tree, pTree);
    return 0;
}

Tree *initSkipList(int m) {
    Tree *l = malloc(sizeof(Tree));
    l->next = malloc(m * sizeof(Tree *));
    l->cell_height = malloc(m * sizeof(int));
    for (int i = 0; i < m; ++i) {
        l->next[i] = NULL;
    }
    return l;
}

bool mapEmpty(Tree l) {
    return NULL == l.next[0];
}

Tree *succ(Tree *x) {
    return x->next[0];
}

Tree **skip(Tree *l, int m, int k, Tree **p) {
    Tree *x = l;
    for (int i = m - 1; i >= 0; --i) {
        while (NULL != x->next[i] && x->next[i]->key.k < k) {
            x = x->next[i];
        }
        p[i] = x;
    }
    return p;
}

int operationRecognition(int m, Tree *l, Tree *tree, int *array_of_heights, Tree **p,
                         char *operation, int j) {
    int k;
    char v[STRING_SIZE];
    switch (gettingOperationNumber(operation)) {
        case 0:
            scanf("%d %s", &k, v);
            tree[j].key.v = malloc((strlen(v) + 1) * sizeof(char));
            strcpy(tree[j].key.v, v);
            tree[j].key.k = k;
            insert(l, m, k, &tree[j++], p, array_of_heights);
            break;
        case 1:
            scanf("%d", &k);
            printf("%s\n", lookup(l, m, k, p));
            break;
        case 2:
            scanf("%d", &k);
            delete(l, m, k, p);
            break;
        case 3:
            scanf("%d", &k);
            printf("%d\n", rank(l, m, k));
            break;
        case -1:
            printf("ERROR: wrong input operation");
            break;
    }
    return j;
}

char *lookup(Tree *l, int m, int k, Tree **p) {
    skip(l, m, k, p);
    Tree *x = succ(p[0]);
    if (mapEmpty(*l) || x->key.k != k) {
        printf("PANIC");
    }
    return x->key.v;
}

void insert(Tree *l, int m, int k, Tree *x, Tree **p, int *array_of_heights) {
    arrayOfHeightsUPD(l, m, k, array_of_heights);
    p = skip(l, m, k, p);
    if (NULL != p[0]->next[0] && k == p[0]->next[0]->key.k) {
        printf("PANIC");
    }
    x->next = malloc(m * sizeof(Tree *));
    x->cell_height = malloc(m * sizeof(int));
    int r, i;
    r = rand() * 2;
    i = 0;
    while (i < m && 0 == r % 2) {
        x->next[i] = p[i]->next[i];
        p[i]->next[i] = x;
        change(x, p, array_of_heights, i);
        r /= 2;
        ++i;
    }
    while (i < m) {
        ++p[i]->cell_height[i];
        x->next[i] = NULL;
        ++i;
    }
}

void arrayOfHeightsUPD(Tree *l, int m, int k, int *array_of_heights) {
    Tree *l_copy = l;
    for (int i = m - 1; i >= 0; --i) {
        if (i == m - 1) {
            array_of_heights[i] = 0;
        } else {
            array_of_heights[i] = array_of_heights[i + 1];
        }
        while (l_copy->next[i] != NULL && l_copy->next[i]->key.k < k) {
            array_of_heights[i] += l_copy->cell_height[i];
            l_copy = l_copy->next[i];
        }
    }
}

void change(Tree *x, Tree *const *p, const int *array_of_heights, int i) {
    int tmp;
    tmp = array_of_heights[0] - array_of_heights[i];
    x->cell_height[i] = p[i]->cell_height[i] - tmp;
    p[i]->cell_height[i] = tmp + 1;
}

void delete(Tree *l, int m, int k, Tree **p) {
    p = skip(l, m, k, p);
    Tree *x = succ(p[0]);
    if (NULL == x || x->key.k != k) {
        printf("PANIC");
    }
    int i = 0;
    while (i < m && p[i]->next[i] == x) {
        p[i]->cell_height[i] += x->cell_height[i] - 1;
        p[i]->next[i] = x->next[i];
        ++i;
    }
    while (i < m) {
        --p[i]->cell_height[i];
        ++i;
    }
}

int rank(Tree *l, int m, int k) {
    Tree *x = l;
    int i, result;
    result = 0;
    for (i = m - 1; i >= 0; i--)
        while (x->next[i] != NULL && x->next[i]->key.k < k) {
            result += x->cell_height[i];
            x = x->next[i];
        }
    return result;
}

int gettingOperationNumber(char *operation) {
    const char *array_of_operation[] = {"INSERT", "LOOKUP", "DELETE", "RANK"};
    for (int i = 0; i < DEFAULT_OPERATIONS; ++i) {
        if (0 == strcmp(operation, array_of_operation[i])) {
            return i;
        }
    }
    return -1;
}

/*
void freeTree(Tree *tree, int j) {
    for (int i = 0; i < j; ++i) {
        free(tree[i].key.v);
        tree[i].key.v = NULL;
        free(tree[i].next);
        tree[i].next = NULL;
        free(tree[i].cell_height);
        tree[i].cell_height = NULL;
    }
    free(tree);
    tree = NULL;
}
*/
void freeAndNull(int j, int *array_of_heights, Tree *l, Tree *tree, Tree **p) {
    for (int i = 0; i < j; ++i) {
        free(tree[i].key.v);
        tree[i].key.v = NULL;
        free(tree[i].next);
        tree[i].next = NULL;
        free(tree[i].cell_height);
        tree[i].cell_height = NULL;
    }
    free(array_of_heights);
    array_of_heights = NULL;
    free(p);
    p = NULL;
    free(l->next);
    l->next = NULL;
    free(l->cell_height);
    l->cell_height = NULL;
    free(l);
    l = NULL;
    free(tree);
    tree = NULL;
}
