// Copyright 2022 Rares Matei Dumitrescu mateidum828@gmail.com

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "/home/mateidumitrescu/Documents/Tema2-sd/utils.h"
#include "/home/mateidumitrescu/Documents/Tema2-sd/structures.h"
#include "/home/mateidumitrescu/Documents/Tema2-sd/hashtable_utils.h"
#include "/home/mateidumitrescu/Documents/Tema2-sd/books_utils.h"

#define B_MAX 40
#define KV_MAX 20
#define HMAX 10
#define DEFINITIONS "definitions"  // Macros for dictionary types
#define BOOKS "books"  // Macros for dictionary types
#define USERS "users"  // Macros for dictionary types

void add_book_in_ht(hashtable_t **books_ht, char book_name[B_MAX],
                    int def_number, int *hmax_books, int *hmax_defs) {
    hashtable_t *definitions_hashtable = ht_create(*hmax_defs, hash_function_string,
                                                   compare_function_strings,
                                                   DEFINITIONS);
    char key_name[KV_MAX];
    char value_name[KV_MAX];
    while (def_number > 0) {
        scanf("%s%s", key_name, value_name);
        int key_size = strlen(key_name) + 1;
        int value_size = strlen(value_name) + 1;
        // adding key and definition in ht
        ht_put(definitions_hashtable, key_name, key_size, value_name,
               value_size, NULL, DEFINITIONS);
        if (definitions_hashtable->size > definitions_hashtable->hmax) {
            resize_hashtable(&definitions_hashtable, *hmax_defs, DEFINITIONS);
        }
        def_number--;
    }
    int book_size = strlen(book_name) + 1;
    book_info_t book_info;
    book_info.purchases = 0;
    book_info.rating = 0;
    book_info.sum_of_ratings = 0;
    book_info.borrowed = 0;  // setting details at 0 when adding a new book
    ht_put(*books_ht, book_name, book_size, definitions_hashtable,
           sizeof(*definitions_hashtable),
           &book_info, BOOKS);
    if ((*books_ht)->size > (*books_ht)->hmax) {
        resize_hashtable(books_ht, *hmax_books, BOOKS);
    }
    free(definitions_hashtable);
}

void print_book_details(hashtable_t *books_ht, char book_name[B_MAX]) {
    if (ht_has_key(books_ht, book_name)) {
        printf("Name:%s ", book_name);
        // getting information of the book to print it
        book_info_t *book_info = (book_info_t *)ht_get_details(books_ht,
                                                               book_name);
        printf("Rating:%.3f ", book_info->rating);
        printf("Purchases:%d\n", book_info->purchases);
    } else {
        printf("The book is not in the library.\n");
    }
}

void remove_book_from_ht(hashtable_t *books_ht, char book_name[B_MAX]) {
    if (ht_has_key(books_ht, book_name)) {
        ht_remove_entry(books_ht, book_name, BOOKS);
    } else {
        printf("The book is not in the library.\n");
    }
}
