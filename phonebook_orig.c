#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "phonebook_orig.h"

void initialize()
{
    pHead = (entry *) malloc(sizeof(entry));
    e = pHead;
    e->pNext = NULL;
}

entry *append(char lastName[], entry *e)
{
    /* allocate memory for the new entry and put lastName */
    e->pNext = (entry *) malloc(sizeof(entry));
    e = e->pNext;
    strcpy(e->lastName, lastName);
    e->pNext = NULL;
    return e;
}

void new_node(char lastName[], entry *node)
{
    e = append(lastName, node);
}

void move_node()
{
    e = pHead;
}

entry *findName(char lastname[], entry *pHead)
{
    while (pHead != NULL) {
        if (strcasecmp(lastname, pHead->lastName) == 0)
            return pHead;
        pHead = pHead->pNext;
    }
    return NULL;
}

void release()
{
    free(pHead);
}

struct PHONE_BOOK PHONE_BOOK = {
    .initialize = initialize,
    .move_node = move_node,
    .new_node = new_node,
    .findName = findName,
    .release = release
};
