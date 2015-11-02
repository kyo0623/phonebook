#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#define MAX_LAST_NAME_SIZE 16
#define HASHING_ALGORITHM
#define hash_bucket_size 26000

/* original version */
typedef struct __PHONE_BOOK_ENTRY {
    char firstName[16];
    char email[16];
    char phone[10];
    char cell[10];
    char addr1[16];
    char addr2[16];
    char city[16];
    char state[2];
    char zip[5];
} detail_entry;

typedef struct __last_name_ENTRY {
    char lastName[MAX_LAST_NAME_SIZE];
    detail_entry *detail;
    struct __last_name_ENTRY *pNext;
} entry;

struct PHONE_BOOK {
    void (*initialize)(void);
    void (*move_node)(void);
    void (*new_node)(char lastName[], entry **node);
    entry *(*findName)(char lastname[], entry **pHead);
    void (*release)(void);
};

struct PHONE_BOOK PHONE_BOOK;
entry *pHead[hash_bucket_size];
entry *e[hash_bucket_size];

#endif
