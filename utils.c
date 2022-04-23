// Copyright 2022 Rares Matei Dumitrescu mateidum828@gmail.com

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUF 125
#define B_MAX 40

#include "structures.h"
#include "hashtable_utils.h"

void shift_letters(char book_name[B_MAX]) {
    int len = strlen(book_name);
    for (int i = 0; i < len; i++) {
        book_name[i] = book_name[i + 1];
    }
}

void get_book_name(char line[BUF], char book_name[B_MAX]) {
    int pos = 0;
    while (line[pos] != '"') {
        pos++;
    }
    int book_index = 0;
    int count = 0;
    while (count < 2) {
        if (line[pos] != '"') {
            book_name[book_index] = line[pos];
            book_index++;
        } else {
            count++;
        }
        pos++;
    }
    book_name[book_index] = '\0';
    //shift_letters(book_name);
}

void day_is_over(hashtable_t *books_ht, hashtable_t *user_ht) {
    printf("Books ranking:\n");
    void *arr = malloc(books_ht->size * sizeof(book_ranking_t));
}