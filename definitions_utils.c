// Copyright 2022 Rares Matei Dumitrescu mateidum828@gmail.com

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "structures.h"
#include "hashtable_utils.h"

#define HMAX 10
#define B_MAX 40
#define KV_MAX 20
#define C_MAX 10
#define BUF 125
#define DEFINITIONS "definitions"  // Macros for dictionary types
#define BOOKS "books"  // Macros for dictionary types
#define USERS "users"  // Macros for dictionary types

void add_definition(hashtable_t *books_ht, char book_name[B_MAX],
                    char key_name[KV_MAX], char value_name[KV_MAX]) {
    if (ht_has_key(books_ht, book_name)) {
        hashtable_t *definitions_ht = (hashtable_t *)ht_get(books_ht,
                                                            book_name);
        int key_size = strlen(key_name) + 1;
        int value_size = strlen(value_name) + 1;
        ht_put(definitions_ht, key_name, key_size, value_name,
               value_size, NULL, DEFINITIONS);
    } else {
        printf("The book is not in the library.\n");
    }
}

void get_definition(hashtable_t *books_ht, char book_name[B_MAX],
                    char key_name[KV_MAX]) {
    if (ht_has_key(books_ht, book_name)) {
        hashtable_t *definitions_ht = (hashtable_t *)ht_get(books_ht,
                                                            book_name);
        if (ht_has_key(definitions_ht, key_name)) {
            char *value_name = (char *)ht_get(definitions_ht, key_name);
            printf("%s\n", value_name);  
        } else {
            printf("The definition is not in the book.\n");
        }
    } else {
        printf("The book is not in the library.\n");
    }
}

void remove_definition(hashtable_t *books_ht, char book_name[B_MAX],
                       char key_name[KV_MAX]) {
    if (ht_has_key(books_ht, book_name)) {
        hashtable_t *definitions_ht = (hashtable_t *)ht_get(books_ht, book_name);
        if (ht_has_key(definitions_ht, key_name)) {
            ht_remove_entry(definitions_ht, key_name, DEFINITIONS);
        } else {
            printf("The definition is not in the book.\n");
        }
    } else {
        printf("The book is not in the library.\n");
    }
}
