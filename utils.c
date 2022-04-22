// Copyright 2022 Rares Matei Dumitrescu mateidum828@gmail.com

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUF 125
#define B_MAX 40

void shift_letters(char book_name[B_MAX]) {
    int len = strlen(book_name);
    for (int i = 0; i < len; i++) {
        book_name[i] = book_name[i + 1];
    }
}

void get_book_name(char line[BUF], char book_name[B_MAX]) {
    int count = 0;
    int line_index = 0;
    int book_index = 0;
    while (count < 2) {
        if (line[line_index] != '"') {
            book_name[book_index] = line[line_index];
            book_index++;
        } else {
            count++;
        }
        line_index++;
    }
    book_name[book_index] = '\0';
    shift_letters(book_name);
}