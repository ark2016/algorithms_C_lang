/*//==============================================================================================================
Операция SearchByRank : A x N -> P для ассоциативного массива возвращает словарную пару с заданным номером в 
отсортированной последовательности входящих в ассоциативный массив словарных пар.

Модифицируйте представление и реализацию бинарного дерева поиска, чтобы операция SearchByRank для него работала 
за время O(h), где h — высота дерева.

Составьте программу ranktree.c, демонстрирующую работоспособность реализованной операции.

Формат входных данных. Первая строка, считываемая со стандартного потока ввода, содержит общее количество 
выполняемых операций n (0 < n <= 100 000). Каждая из следующих n строк содержит описание операции.

Операция либо имеет форму INSERT k v (добавить в список с пропусками словарную пару, в которой ключ k  — целое 
число, значение v — строка, составленная из латинских букв; -1 000 000 000 < k < 1 000 000 000, len(v) < 10)), 
либо форму LOOKUP k (вывести строку, связанную с ключом k), либо форму DELETE k (удалить строку, связанную с 
ключом k), либо форму SEARCH x (вывести строку, связанную с ключом, имеющим порядковый номер x).

Можно считать, что последовательность операций составлена правильно.

Формат результата работы программы. Для каждой операции LOOKUP вывести в стандартный поток вывода строку, 
связанную с ключом k. Для каждой операции SEARCH вывести в стандартный поток вывода строку, связанную с ключом, 
имеющим порядковый номер x.

Указание. Представление бинарного дерева поиска нужно модифицировать следующим образом: в каждую вершину нужно 
добавить поле count, содержащее размер поддерева с корнем в данной вершине. Размер поддерева — это количество 
вершин в нём.
*///==============================================================================================================
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdbool.h>

#define DEFAULT_OPERATIONS 4

typedef struct Pair {
    int key;
    int serialNumber;
} Pair;

typedef struct Elem {
    Pair pair;
    char *value;
    struct Elem *parent;
    struct Elem *left;
    struct Elem *right;
} Elem;

typedef struct Tree {
    Elem *root;
} Tree;

Tree initTree(Tree *tree);

bool isEmptyTree(Tree tree);

Elem *initCleanElem(int key, char *value, Elem *cleanElem);

Elem *treeDescend(Tree *tree, int key);

void treeInsert(Tree *tree, int key, char *value);

void treeReplace(Tree *tree, Elem *elemX, Elem *elemY);

Elem *minimum(Elem *elem);

Elem *succ(Elem *elem);

void increasingTheSerialNumberOfATreeBranch(Tree *tree, int key);

void treeDelete(Tree *tree, int key);

Elem *treeSearchByRank(Tree *tree, int rank);

Elem *treeLookup(Tree *tree, int x);

int gettingOperationNumber(char *operation);

Tree operationRecognition(char *operation, char *word, int *x, Tree *tree);

void freeTreeRoot(Elem *elem);

void freeTree(Tree tree);

int main() {
    char *word = NULL;
    char operation[7];
    int x;
    Tree tree;
    tree = initTree(&tree);
    while (true) {
        scanf("%s", operation);
        if (0 == strcmp(operation, "END")) {
            break;
        }
        tree = operationRecognition(operation, word, &x, &tree);
    }
    freeTree(tree);
    return 0;
}

Tree initTree(Tree *tree) {
    (*tree).root = NULL;
    return *tree;
}

bool isEmptyTree(Tree tree) {
    return NULL == tree.root;
}

Elem *initCleanElem(int key, char *value, Elem *cleanElem) {
    cleanElem = (Elem *) malloc(sizeof(Elem));
    cleanElem->pair.key = key;
    cleanElem->value = value;
    cleanElem->pair.serialNumber = 0;
    cleanElem->parent = NULL;
    cleanElem->left = NULL;
    cleanElem->right = NULL;
    return cleanElem;
}

Elem *treeDescend(Tree *tree, int key) {
    Elem *root = tree->root;
    while (root && root->pair.key != key) {
        if (key < root->pair.key) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return root;
}

void treeInsert(Tree *tree, int key, char *value) {
    Elem *cleanElem = NULL;
    cleanElem = initCleanElem(key, value, cleanElem);
    if (!tree->root) {
        tree->root = cleanElem;
    } else {
        Elem *root = tree->root;
        for (;;) {
            if (key == root->pair.key) {
                printf("PANIC\n");
            }
            ++root->pair.serialNumber;
            if (key < root->pair.key) {
                if (!root->left) {
                    root->left = cleanElem;
                    cleanElem->parent = root;
                    break;
                }
                root = root->left;
            } else {
                if (!root->right) {
                    root->right = cleanElem;
                    cleanElem->parent = root;
                    break;
                }
                root = root->right;
            }
        }
    }
}

void treeReplace(Tree *tree, Elem *elemX, Elem *elemY) {
    if (tree->root == elemX) {
        tree->root = elemY;
        if (elemY) {
            elemY->parent = NULL;
        }
    } else {
        Elem *parent = elemX->parent;
        if (elemY) {
            elemY->parent = parent;
        }
        if (parent->left == elemX) {
            parent->left = elemY;
        } else {
            parent->right = elemY;
        }
    }
}

Elem *minimum(Elem *elem) {
    if (!elem) {
        return elem;
    } else {
        while (elem->left) {
            --elem->pair.serialNumber;
            elem = elem->left;
        }
        return elem;
    }
}

Elem *succ(Elem *elem) {
    if (elem->right) {
        return minimum(elem->right);
    } else {
        Elem *parent = elem->parent;
        while (parent && elem == parent->right) {
            elem = parent;
            parent = parent->parent;
        }
        return parent;
    }
}

void increasingTheSerialNumberOfATreeBranch(Tree *tree, int key) {
    Elem *node = tree->root;
    while (node && node->pair.key != key) {
        --node->pair.serialNumber;
        if (key < node->pair.key) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
}

void treeDelete(Tree *tree, int key) {
    Elem *elemX = treeDescend(tree, key);
    increasingTheSerialNumberOfATreeBranch(tree, key);
    if (!elemX) {
        printf("PANIC\n");
    }
    if (!elemX->left && !elemX->right) {
        treeReplace(tree, elemX, NULL);
    } else if (!elemX->left) {
        treeReplace(tree, elemX, elemX->right);
    } else if (!elemX->right) {
        treeReplace(tree, elemX, elemX->left);
    } else {
        Elem *elemY = succ(elemX);
        treeReplace(tree, elemY, elemY->right);
        elemX->left->parent = elemY;
        elemY->left = elemX->left;
        if (elemX->right) {
            elemX->right->parent = elemY;
        }
        elemY->right = elemX->right;
        elemY->pair.serialNumber = elemX->pair.serialNumber - 1;
        treeReplace(tree, elemX, elemY);
    }
    free(elemX->value);
    free(elemX);
}

Elem *treeSearchByRank(Tree *tree, int rank) {
    Elem *root = tree->root;
    while (root) {
        if (root->left) {
            if (root->left->pair.serialNumber + 1 == rank) {
                return root;
            } else if (root->left->pair.serialNumber + 1 > rank) {
                root = root->left;
            } else {
                rank -= root->left->pair.serialNumber + 2;
                root = root->right;
            }
        } else if (rank) {
            --rank;
            root = root->right;
        } else {
            return root;
        }
    }
}

Elem *treeLookup(Tree *tree, int x) {
    Elem *elem = treeDescend(tree, x);
    if (!elem) {
        printf("PANIC\n");
    }
    return elem;
}

int gettingOperationNumber(char *operation) {
    const char *arrayOfOperation[] = {"INSERT", "LOOKUP", "DELETE", "SEARCH"};
    for (int i = 0; i < DEFAULT_OPERATIONS; ++i)
        if (0 == strcmp(operation, arrayOfOperation[i])) {
            return i;
        }
    return -1;
}

Tree operationRecognition(char *operation, char *word, int *x, Tree *tree) {
    switch (gettingOperationNumber(operation)) {
        case 0:
            scanf("%d", x);
            word = (char *) malloc(sizeof(char) * 10);
            scanf("%s", word);
            treeInsert(tree, (*x), word);
            break;
        case 1:
            scanf("%d", x);
            printf("%s\n", treeLookup(tree, (*x))->value);
            break;
        case 2:
            scanf("%d", x);
            treeDelete(tree, (*x));
            break;
        case 3:
            scanf("%d", x);
            printf("%s\n", treeSearchByRank(tree, (*x))->value);
            break;
        case -1:
            printf("ERROR: wrong input operation\n");
            break;
    }
    return (*tree);
}

void freeTreeRoot(Elem *elem) {
    if (elem->right) {
        freeTreeRoot(elem->right);
    }
    if (elem->left) {
        freeTreeRoot(elem->left);
    }
    free(elem->value);
    elem->right = NULL;
    free(elem);
    elem = NULL;
}

void freeTree(Tree tree) {
    if (tree.root)
        freeTreeRoot(tree.root);
}
