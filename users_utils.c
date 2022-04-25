// Copyright 2022 Rares Matei Dumitrescu mateidum828@gmail.com

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "structures.h"
#include "hashtable_utils.h"
#include "books_utils.h"

#define U_MAX 20
#define B_MAX 40
#define DEFINITIONS "definitions"  // Macros for dictionary types
#define BOOKS "books"  // Macros for dictionary types
#define USERS "users"  // Macros for dictionary types

void add_user(hashtable_t *users_ht, char user_name[U_MAX]) {
    if (ht_has_key(users_ht, user_name)) {
        printf("User is already registered.\n");
        return;
    }
    int user_name_size = strlen(user_name) + 1;
    user_info_t user;
    user.points = 100;  // every user gets 100 points at registration
    user.banned = 0;
    user.has_borrowed = 0;
    ht_put(users_ht, user_name, user_name_size, NULL, 0, &user, USERS);
}

void borrow_book(hashtable_t *users_ht, hashtable_t *books_ht,
                 char user_name[U_MAX],
                 char book_name[B_MAX], int borrow_days) {
    if (ht_has_key(users_ht, user_name)) {
        user_info_t *user = (user_info_t *)ht_get_details(users_ht, user_name);
        if (user->banned) {
            printf("You are banned from this library.\n");
            return;
        } else if (user->has_borrowed) {
            printf("You have already borrowed a book.\n");
            return;
        } else if (ht_has_key(books_ht, book_name)) {
            book_info_t *book =
            (book_info_t *)ht_get_details(books_ht, book_name);
            if (user->has_borrowed) {
                printf("You have already borrowed a book.\n");
                return;
            } else if (book->borrowed) {
                printf("The book is borrowed.\n");
                return;
            } else {
                // changing details of book and user,
                // everything was checked about the user
                user->has_borrowed = 1;
                user->borrow_period = borrow_days;
                book->borrowed = 1;
                ht_put(users_ht, user_name, strlen(user_name) + 1, book_name,
                       strlen(book_name) + 1,
                       user, USERS);
            }
        } else {
            printf("The book is not in the library.\n");
            return;
        }
    } else {
        printf("You are not registered yet.\n");
    }
}

void return_book(hashtable_t *users_ht, hashtable_t *books_ht,
                 char book_name[B_MAX],
                 char user_name[U_MAX], int days_since_borrowed,
                 int rating) {
    user_info_t *user = (user_info_t *)ht_get_details(users_ht, user_name);
    if (user->banned) {
        printf("You are banned from this library.\n");
        return;
    } else if (user->has_borrowed) {
        char *borrowed_book = (char *)ht_get(users_ht, user_name);
        if (strcmp(book_name, borrowed_book)) {
            printf("You didn't borrow this book.\n");
            return;
        } else {
            // returning the book starts here if
            // everything was checked about the user
            int days_diff = user->borrow_period - days_since_borrowed;
            if (days_diff >= 0) {
                user->points += days_diff;
            } else {
                user->points += 2 * days_diff;
            }
            if (user->points < 0) {
                printf("The user %s has been banned from this library.\n",
                user_name);
                user->banned = 1;
            }
            user->has_borrowed = 0;
            user->borrow_period = 0;
            book_info_t *book =
            (book_info_t *)ht_get_details(books_ht, book_name);
            book->borrowed = 0;
            book->purchases += 1;
            book->sum_of_ratings += rating;
            book->rating =
            (double)(book->sum_of_ratings) / (double)(book->purchases);
            ht_put(users_ht, user_name, strlen(user_name) + 1,
                   NULL, 0, user, USERS);
        }
    } else {
        printf("You didn't borrow this book.\n");
        return;
    }
}

void report_lost(hashtable_t *books_ht, hashtable_t *users_ht,
                 char user_name[U_MAX], char book_name[U_MAX]) {
    if (ht_has_key(users_ht, user_name)) {
        user_info_t *user = (user_info_t *)ht_get_details(users_ht, user_name);
        if (user->banned) {
            printf("You are banned from this library.\n");
            return;
        }
        remove_book_from_ht(books_ht, book_name);
        user->points -= 50;
        user->has_borrowed = 0;
        user->borrow_period = 0;
        if (user->points < 0) {
            user->banned = 1;
            printf("The user %s has been banned from this library.\n",
                   user_name);
        }
        ht_put(users_ht, user_name, strlen(user_name), NULL, 0, user, USERS);
    } else {
        printf("You are not registered yet.\n");
    }
}
