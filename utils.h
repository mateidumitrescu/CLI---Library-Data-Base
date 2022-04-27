// Copyright 2022 Rares Matei Dumitrescu mateidum828@gmail.com

#ifndef _HOME_MATEIDUMITRESCU_DOCUMENTS_TEMA2_SD_UTILS_H_
#define _HOME_MATEIDUMITRESCU_DOCUMENTS_TEMA2_SD_UTILS_H_

#define BUF 125
#define B_MAX 40

#include "structures.h"

// function to get the name of the book
void get_book_name(char line[BUF], char book_name[B_MAX]);

// function to sort an array of ranking books
void sort_arr_books(book_ranking_t *arr, unsigned int size);

// function to sort an array of ranking users
void sort_arr_users(user_ranking_t *arr, unsigned int size);

// function to end the day and program and print rankings
void day_is_over(hashtable_t *books_ht, hashtable_t *user_ht);

// function to resize a hashtable
void resize_hashtable(hashtable_t **ht, int hmax,
                      char dictionary_type[B_MAX]);

#endif  // _HOME_MATEIDUMITRESCU_DOCUMENTS_TEMA2_SD_UTILS_H_
