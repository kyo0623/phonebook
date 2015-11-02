#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "phonebook_opt.h"
#define hash hash_soundex  /* Choose hash function method djb2, sdbm, lose*/

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

static inline void soundex(char *input, char *output)
{
    int i = 1, index = 1;
    char temp;
    output[0] = input[0];
    while(input[i] != '\0' && index < 4)
    {
        if(input[i] == 'b' || input[i] == 'p' || input[i] == 'f' || input[i] == 'v')
            temp = '1';
        else if(input[i] == 'c' || input[i] == 's' || input[i] == 'k' ||
                input[i] == 'g' || input[i] == 'j' || input[i] == 'q' || 
                input[i] == 'x' || input[i] == 'z')
            temp = '2';
        else if(input[i] == 'd' || input[i] == 't')
            temp = '3';
        else if(input[i] == 'l')
            temp = '4';
        else if(input[i] == 'm' || input[i] == 'n')
            temp = '5';
        else if(input[i] == 'r')
            temp = '6';
        else
            temp = '0';
        if(temp != '0' && temp != output[index-1])
        {
            output[index] = temp;
            index++; 
        }
        i++;
    }
    while(index < 4)
        output[index++] = '0';
    output[index] = '\0';
}

static inline unsigned int hash_soundex(char lastName[])
{
    char output[5];
    soundex(lastName, output);
    unsigned long value = 0;
    value += (output[0] - 97) * 1000;
    value += (output[1] - 48) * 100;
    value += (output[2] - 48) * 10;
    value += (output[3] - 48);
    return value;
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
        printf("%s\n", node -> lastName);
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
