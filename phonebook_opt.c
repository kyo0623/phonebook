#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "phonebook_opt.h"
#define hash hash_lose  /* Choose hash function method djb2, sdbm, lose*/

/* FILL YOUR OWN IMPLEMENTATION HERE! */
static inline unsigned int hash_djb2(char lastName[])
{
    unsigned long value = 0;
    int c = 0;
    int length = strlen (lastName);
    value = 5381;
    while(c <= length) {
        value = ((value << 5) + value) + lastName[c];
        c++;
    }
    return value % hash_bucket_size;
}

static inline unsigned int hash_sdbm(char lastName[])
{
    unsigned long value = 0;
    int c = 0;
    int length = strlen (lastName);
    while(c <= length) {
        value = lastName[c] + (value << 6) + (value << 16) - value;
        c++;
    }
    return value % hash_bucket_size;
}

static inline unsigned int hash_lose(char lastName[])
{
    unsigned long value = 0;
    int c = 0;
    int length = strlen (lastName);
    while(c <= length) {
        value += lastName[c];
        c++;
    }
    return value % hash_bucket_size;
}

void initialize()
{
    int i;
    for(i=0 ; i < hash_bucket_size ; i++) {
        pHead[i] = (entry *) malloc(sizeof(entry));
        pHead[i] -> pNext = NULL;
        e[i] = pHead[i];
    }
}

static void append(char lastName[], entry **e)
{
    /* allocate memory for the new entry and put lastName */
    unsigned int key = hash(lastName);
    e[key] -> pNext = (entry *) malloc(sizeof(entry));
    e[key] = e[key] -> pNext;
    strcpy(e[key] -> lastName, lastName);
    e[key] -> pNext = NULL;
}

void new_node(char lastName[], entry **node)
{
    append(lastName, node);
}

void move_node()
{
    int i;
    for(i=0; i<hash_bucket_size; i++)
        e[i] = pHead[i];
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

void release()
{
    int i;
    for(i=0; i<hash_bucket_size; i++)
        free(pHead[i]);
}

struct PHONE_BOOK PHONE_BOOK = {
    .initialize = initialize,
    .move_node = move_node,
    .new_node = new_node,
    .findName = findName,
    .release = release
};
