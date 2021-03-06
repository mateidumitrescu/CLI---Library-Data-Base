// Copyright 2022 Rares Matei Dumitrescu mateidum828@gmail.com

#ifndef _HOME_MATEIDUMITRESCU_DOCUMENTS_TEMA2_SD_BOOKS_UTILS_H_
#define _HOME_MATEIDUMITRESCU_DOCUMENTS_TEMA2_SD_BOOKS_UTILS_H_

#define B_MAX 40

// function to add a book in hashtable
void add_book_in_ht(hashtable_t **books_ht, char book_name[B_MAX],
                    int def_number, int *hmax_books, int *hmax_defs);

// function to print the details of a book
void print_book_details(hashtable_t *books_ht, char book_name[B_MAX]);

// function to remove a book from hashtable
void remove_book_from_ht(hashtable_t *books_ht, char book_name[B_MAX]);

#endif  // _HOME_MATEIDUMITRESCU_DOCUMENTS_TEMA2_SD_BOOKS_UTILS_H_
