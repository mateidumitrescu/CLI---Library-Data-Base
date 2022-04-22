// Copyright 2022 Rares Matei Dumitrescu mateidum828@gmail.com

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashtable_utils.h"
#include "structures.h"
#include "utils.h"
#include "books_utils.h"

#define HMAX 10  // standard number of buckets
#define B_MAX 40  // maximum nr of characters in a book name
#define KV_MAX 20  // maximum nr of characters in key or value
#define C_MAX 10  // standard command size
#define BUF 125

int main(void) {
    char command[C_MAX], line[BUF], book_name[B_MAX], key_name[KV_MAX], value_name[KV_MAX];
    int go = 1, def_number;
    hashtable_t *books_ht = ht_create(HMAX, hash_function_string, compare_function_strings,
                                      "books");
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
            
        }
    }
}