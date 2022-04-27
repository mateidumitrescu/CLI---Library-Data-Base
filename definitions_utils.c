// Copyright 2022 Rares Matei Dumitrescu mateidum828@gmail.com

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "/home/mateidumitrescu/Documents/Tema2-sd/structures.h"
#include "/home/mateidumitrescu/Documents/Tema2-sd/hashtable_utils.h"
#include "/home/mateidumitrescu/Documents/Tema2-sd/definitions_utils.h"
#include "utils.h"

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

        unsigned int id = books_ht->hash_function(book_name) % books_ht->hmax;
        ll_node_t *node = books_ht->buckets[id]->head;
        key_value_t *data;

        while (node != NULL) {
            data = node->data;
            if (strcmp((char *)data->key, book_name) == 0)
                break;
            node = node->next;
        }

        ht_put(definitions_ht, key_name, key_size, value_name,
               value_size, NULL, DEFINITIONS);
        if (definitions_ht->size > definitions_ht->hmax) {
            resize_hashtable(&definitions_ht, definitions_ht->hmax, DEFINITIONS);
        }
        data->value = definitions_ht;

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
        hashtable_t *definitions_ht =
        (hashtable_t *)ht_get(books_ht, book_name);
        if (ht_has_key(definitions_ht, key_name)) {
            ht_remove_entry(definitions_ht, key_name, DEFINITIONS);
        } else {
            printf("The definition is not in the book.\n");
        }
    } else {
        printf("The book is not in the library.\n");
    }
}
