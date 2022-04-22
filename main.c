// Copyright 2022 Rares Matei Dumitrescu mateidum828@gmail.com

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashtable_utils.h"
#include "structures.h"
#include "utils.h"
#include "books_utils.h"
#include "definitions_utils.h"
#include "users_utils.h"

#define U_MAX 20  // maximum nr of characters in user name
#define HMAX 10  // standard number of buckets
#define B_MAX 40  // maximum nr of characters in a book name
#define KV_MAX 20  // maximum nr of characters in key or value
#define C_MAX 10  // standard command size
#define BUF 125
#define DEFINITIONS "definitions"  // Macros for dictionary types
#define BOOKS "books"  // Macros for dictionary types
#define USERS "users"  // Macros for dictionary types

int main(void) {
    char command[C_MAX], line[BUF], book_name[B_MAX], key_name[KV_MAX],
         value_name[KV_MAX], user_name[U_MAX];
    int go = 1, def_number;
    hashtable_t *books_ht = ht_create(HMAX, hash_function_string, compare_function_strings,
                                      BOOKS);
    hashtable_t *users_ht = ht_create(HMAX, hash_function_string, compare_function_strings,
                                      USERS);
    while (go) {
        scanf("%s", command);
        if (strcmp(command, "ADD_BOOK") == 0) {
            fgets(line, BUF, stdin);
            get_book_name(line, book_name);
            sscanf(line + strlen(book_name) + 4, "%d", &def_number); // number of definitions
            add_book_in_ht(books_ht, book_name, def_number);  // beginning of hashtables
        } else if (strcmp(command, "GET_BOOK") == 0) {
            fgets(line, BUF, stdin);
            get_book_name(line, book_name);
            print_book_details(books_ht, book_name);
        } else if (strcmp(command, "RMV_BOOK") == 0) {
            fgets(line, BUF, stdin);
            get_book_name(line, book_name);
            remove_book_from_ht(books_ht, book_name);
        } else if (strcmp(command, "ADD_DEF") == 0) {
            fgets(line, BUF, stdin);
            get_book_name(line, book_name);
            sscanf(line + strlen(book_name) + 4, "%s%s", key_name, value_name);
            add_definition(books_ht, book_name, key_name, value_name);
        } else if (strcmp(command, "GET_DEF") == 0) {
            fgets(line, BUF, stdin);
            get_book_name(line, book_name);
            sscanf(line + strlen(book_name) + 4, "%s", key_name);
            get_definition(books_ht, book_name, key_name);
        } else if (strcmp(command, "RMV_DEF") == 0) {
            fgets(line, BUF, stdin);
            get_book_name(line, book_name);
            sscanf(line + strlen(book_name) + 4, "%s", key_name);
            remove_definition(books_ht, book_name, key_name);
        } else if (strcmp(command, "ADD_USER") == 0) {
            scanf("%s", user_name);
            add_user(users_ht, user_name);
        }
    }
}