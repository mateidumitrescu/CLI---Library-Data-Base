// Copyright 2022 Rares Matei Dumitrescu mateidum828@gmail.com

#ifndef _HOME_MATEIDUMITRESCU_DOCUMENTS_TEMA2_SD_UTILS_H_
#define _HOME_MATEIDUMITRESCU_DOCUMENTS_TEMA2_SD_UTILS_H_

#define BUF 125
#define B_MAX 40

#include "structures.h"

// function to get the name of the book
void get_book_name(char line[BUF], char book_name[B_MAX]);

// function to compare 2 users ranking
int compare_users( const void* a, const void* b);

// function to compare 2 books ranking
int compare_books( const void* a, const void* b);

// function to end the day and program and print rankings
void day_is_over(hashtable_t *books_ht, hashtable_t *user_ht);

// function to resize a hashtable
void resize_hashtable(hashtable_t **ht, int hmax,
                      int dictionary_type);

#endif  // _HOME_MATEIDUMITRESCU_DOCUMENTS_TEMA2_SD_UTILS_H_
