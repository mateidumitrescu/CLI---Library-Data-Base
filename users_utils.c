// Copyright 2022 Rares Matei Dumitrescu mateidum828@gmail.com

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "structures.h"
#include "hashtable_utils.h"

#define U_MAX 20
#define B_MAX 40

void add_user(hashtable_t *users_ht, char user_name[U_MAX]) {
    if (ht_has_key(users_ht, user_name)) {
        printf("User is already registered.\n");
        return;
    }
    int user_name_size = strlen(user_name);
    user_info_t user;
    user.points = 100;  // every user gets 100 points at registration
    user.banned = 0;
    user.has_borrowed = 0;
    ht_put(users_ht, user_name, user_name_size, NULL, 0, &user);
}

void borrow_book(hashtable_t *users_ht, hashtable_t *books_ht, char user_name[U_MAX],
                 char book_name[B_MAX], int borrow_days) {
    if (ht_has_key(users_ht, user_name)) {
        user_info_t *user = (user_info_t *)ht_get_details(users_ht, user_name);
        if (user->banned) {
            printf("You are banned from this library.\n");
            return;
        } else if (ht_has_key(books_ht, book_name)) {
            book_info_t *book = (book_info_t *)ht_get_details(books_ht, book_name);
            if (book->borrowed) {
                printf("The book is borrowed.\n");
                return;
            } else if (user->has_borrowed) {
                printf("You have already borrowed a book.\n");
                return;
            } else {
                // changing details of book and user
                user->has_borrowed = 1;
                user->borrow_period = borrow_days;
                book->borrowed = 1;
                book->purchases += 1;
                ht_put(users_ht, user_name, strlen(user_name), book_name, strlen(book_name),
                       user);
            }
        } else {
            printf("The book is not in the library.\n");
            return;
        }
    } else {
        printf("You are not registered yet.\n");
    }
}