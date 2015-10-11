#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "phonebook_opt.h"



/* FILL YOUR OWN IMPLEMENTATION HERE! */
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

unsigned int hash(char lastName[])
{
    /* djb2 */
    unsigned long value = 5381;
    int c = 0;
    while(c <= (int) strlen (lastName)) {
        value = ((value << 5) + value) + lastName[c];   //sol * 33 + lastName[c]
        c++;
    }
    return value % hash_bucket_size;
}
