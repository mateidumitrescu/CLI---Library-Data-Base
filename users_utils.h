// Copyright 2022 Rares Matei Dumitrescu mateidum828@gmail.com

#ifndef USERS_UTILS_H_
#define USERS_UTILS_H_

#define U_MAX 20

// function to add a user in hashtable
void add_user(hashtable_t *users_ht, char user_name[U_MAX]);

// function to borrow a book for a user
void borrow_book(hashtable_t *users_ht, hashtable_t *books_ht, char user_name[U_MAX],
                 char book_name[B_MAX], int borrow_days);

// function to return a book for a user
void return_book(hashtable_t *users_ht, hashtable_t *books_ht, char book_name[B_MAX],
                 char user_name[U_MAX], int days_since_borrowed, int rating);

// function to declare a book has been lost
void report_lost(hashtable_t *books_ht, hashtable_t *users_ht,
                 char user_name[U_MAX], char book_name[U_MAX]);

#endif  // USERS_UTILS_H_