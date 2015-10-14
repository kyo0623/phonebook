#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#define MAX_LAST_NAME_SIZE 16

/* original version */
typedef struct __PHONE_BOOK_ENTRY {
    char lastName[MAX_LAST_NAME_SIZE];
    char firstName[16];
    char email[16];
    char phone[10];
    char cell[10];
    char addr1[16];
    char addr2[16];
    char city[16];
    char state[2];
    char zip[5];
    struct __PHONE_BOOK_ENTRY *pNext;
} entry;

struct PHONE_BOOK {
    void (*initialize)(void);
    void (*move_node)(void);
    void (*new_node)(char lastName[], entry *node);
    entry *(*findName)(char lastname[], entry *pHead);
    void (*release)(void);
};

struct PHONE_BOOK PHONE_BOOK;
entry *pHead;
entry *e;

#endif
