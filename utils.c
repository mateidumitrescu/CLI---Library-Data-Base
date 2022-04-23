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

void sort_arr_books(book_ranking_t *arr, unsigned int size) {
    for (unsigned int i = 0; i < size; i++) {
        for (unsigned int j = i + 1; j < size; j++) {
            if (arr[i].rating < arr[j].rating) {
                book_ranking_t aux = arr[i];
                arr[i] = arr[j];
                arr[j] = aux;
            } else if (arr[i].rating == arr[j].rating) {
                if (arr[i].purchases < arr[j].purchases) {
                    book_ranking_t aux = arr[i];
                    arr[i] = arr[j];
                    arr[j] = aux;
                } else if (arr[i].purchases == arr[j].purchases) {
                    if (strcmp(arr[i].name, arr[j].name) > 0) {
                        book_ranking_t aux = arr[i];
                        arr[i] = arr[j];
                        arr[j] = aux;
                    }
                }
            }
        }
    }
}

void sort_arr_users(user_ranking_t *arr, unsigned int size) {
    for (unsigned int i = 0; i < size; i++) {
        for (unsigned int j = i + 1; j < size; j++) {
            if (arr[i].points < arr[j].points) {
                user_ranking_t aux = arr[i];
                arr[i] = arr[j];
                arr[j] = aux;
            } else if (arr[i].points == arr[j].points) {
                if (strcmp(arr[i].name, arr[j].name) > 0) {
                    user_ranking_t aux = arr[i];
                    arr[i] = arr[j];
                    arr[j] = aux;
                }
            }
        }
    }
}

void day_is_over(hashtable_t *books_ht, hashtable_t *users_ht) {
    if (books_ht->size > 0) {
        printf("Books ranking:\n");
        book_ranking_t *arr_books = malloc(books_ht->size * sizeof(book_ranking_t));
        int index = 0;
        for (unsigned int i = 0; i < books_ht->hmax; i++) {
            ll_node_t *current = books_ht->buckets[i]->head;
            while (current != NULL) {
                key_value_t *book = (key_value_t *)current->data;
                strcpy(arr_books[index].name, book->key);
                book_info_t *book_details = (book_info_t *)ht_get_details(books_ht, book->key);
                arr_books[index].purchases = book_details->purchases;
                arr_books[index].rating = book_details->rating;
                index++;
                current = current->next;
            }
        }
        sort_arr_books(arr_books, books_ht->size);
        for (unsigned int i = 0; i < books_ht->size; i++) {
            printf("%d. Name:%s Rating:%.3f Purchases:%d\n", i + 1, arr_books[i].name, arr_books[i].rating, arr_books[i].purchases);
        }
        free(arr_books);  // free auxiliars
    }
    if (users_ht->size > 0) {
        // now sorting for users
        printf("Users ranking:\n");
        // firstly, we count how many users are not banned
        unsigned int count_users = 0;
        for (unsigned int i = 0; i < users_ht->size; i++) {
            ll_node_t *current = users_ht->buckets[i]->head;
            while (current != NULL) {
                key_value_t *user = (key_value_t *)current->data;
                user_info_t *user_details = (user_info_t *)ht_get_details(users_ht, user->key);
                if (!user_details->banned) {
                    count_users++;
                }
                current = current->next;
            }
        }
        int index = 0;
        user_ranking_t *arr_users = malloc(count_users * sizeof(user_ranking_t));
        for (unsigned int i = 0; i < users_ht->size; i++) {
            ll_node_t *current = users_ht->buckets[i]->head;
            while (current != NULL) {
                key_value_t *user = (key_value_t *)current->data;
                user_info_t *user_details = (user_info_t *)ht_get_details(users_ht, user->key);
                if (!user_details->banned) {
                    strcpy(arr_users[index].name, user->key);
                    arr_users[index].points = user_details->points;
                    index++;
                }
                current = current->next;
            }
        }
        sort_arr_users(arr_users, count_users);
        for (unsigned int i = 0; i < count_users; i++) {
            printf("%d. Name:%s Points:%d\n", i + 1, arr_users[i].name, arr_users[i].points);
        }
        free(arr_users);  // free auxiliars
    }
    
}