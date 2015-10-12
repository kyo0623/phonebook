#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "phonebook_opt.h"
#define lose  /* Choose hash function method djb2, sdbm, lose*/



/* FILL YOUR OWN IMPLEMENTATION HERE! */
static inline unsigned int hash(char lastName[])
{
    unsigned long value = 0;
    int c = 0;
    int length = strlen (lastName);
#ifdef djb2
    value = 5381;
    while(c <= length) {
        value = ((value << 5) + value) + lastName[c];
        c++;
    }
#endif
#ifdef sdbm
    while(c <= length) {
        value = lastName[c] + (value << 6) + (value << 16) - value;
        c++;
    }
#endif
#ifdef lose
    while(c <= length) {
        value += lastName[c];
        c++;
    }
#endif
    return value % hash_bucket_size;
}

entry *findName(char lastName[], entry **pHead)
{
    unsigned int key = hash(lastName);
    entry *node=pHead[key];
    while (pHead != NULL) {
        if (strcasecmp(lastName, node-> lastName) == 0)
            return node;
        node = node -> pNext;
    }
    return NULL;
}

void *append(char lastName[], entry **e)
{
    /* allocate memory for the new entry and put lastName */
    unsigned int key = hash(lastName);
    e[key] -> pNext = (entry *) malloc(sizeof(entry));
    e[key] = e[key] -> pNext;
    strcpy(e[key] -> lastName, lastName);
    e[key] -> pNext = NULL;
}
