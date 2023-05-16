#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <malloc.h>

#define BUFFER 1000
typedef struct Elem {
    struct Elem *next;
    char *word;
} Elem;

void swap(Elem *p, char *per);

void freeString(char *str);

void free_pString(char **strings, int i);

void printAndFreeElem(Elem *list, Elem *p);

Elem *initElem(char *data);

void insert(char *data, Elem *list);

bool compare(char *s1, char *s2);

Elem *bsort(Elem *list);

void swap(Elem *p, char *per);

Elem *getElem(const char *str, char **strings,    int len, Elem *list);

int main() {
    char *string, *str, **strings;
    int i, len;
    Elem *list, *p;
    string = calloc(BUFFER, sizeof(char));
    fgets(string, BUFFER, stdin);
    len = strlen(string);
    string[len - 1] = '\0';
    strings = malloc(sizeof(char *) * BUFFER);
    str = calloc((BUFFER + 1), sizeof(char));
    str[0] = ' ';
    for (i = 0; i < len; ++i) {
        str[i + 1] = string[i];
    }
    str[len] = '\0';
    len = strlen(str);
    for (i = 0; i < BUFFER; ++i) {
        strings[i] = calloc(BUFFER, sizeof(char));
    }
    list = getElem(str, strings,  len, list);
    list = bsort(list);
    printAndFreeElem(list, p);
    printf("\n");
    freeString(str);
    freeString(string);
    free_pString(strings, i);
    return 0;
}

void printAndFreeElem(Elem *list, Elem *p) {
    while (list) {
        printf("%s ", list->word);
        p = list;
        list = list->next;
        free(p);
        p = NULL;
    }
}

void free_pString(char **strings, int i) {
    for (i = 0; i < BUFFER; ++i) {
        free(strings[i]);
        strings[i] = NULL;
    }
    free(strings);
    strings = NULL;
}

void freeString(char *str) {
    free(str);
    str = NULL;
}

Elem *getElem(const char *str, char **strings, int len, Elem *list) {
    int i,  j, k, count;
    i = 1;
    count = 0;
    while (i < len) {
        if (str[i - 1] == ' ' && str[i] != ' ') {
            j = 0;
            k = count;
            while (str[i] != ' ' && i < len) {
                strings[k][j] = str[i];
                ++j;
                ++i;
            }
            strings[k][j] = '\0';
            if (!k) {
                list = initElem(strings[k]);
            } else {
                insert(strings[k], list);
            }
            ++count;
        }
        ++i;
    }
    return list;
}

void swap(Elem *p, char *per) {
    per = p->word;
    p->word = p->next->word;
    p->next->word = per;
}

Elem *initElem(char *data) {
    Elem *elem = malloc(sizeof(Elem));
    elem->word = data;
    elem->next = NULL;
    return elem;
}

void insert(char *data, Elem *list) {
    Elem *pElem;
    pElem = initElem(data);
    Elem *p = list;
    while (p->next) {
        p = p->next;
    }
    p->next = pElem;
}

bool compare(char *s1, char *s2) {
    return strlen(s1) > strlen(s2);
}

Elem *bsort(Elem *list) {
    Elem *p;
    Elem *l;
    char *per;
    if (list) {
        l = list;
        while (l) {
            p = list;
            while (p->next) {
                if (!p->word || !p->next->word) {
                    break;
                }
                if (compare(p->word, p->next->word)) {
                    swap(p, per);
                }
                p = p->next;
            }
            l = l->next;
        }
    }
    return list;
}
