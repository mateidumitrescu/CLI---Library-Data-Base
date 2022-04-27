// Copyright 2022 Rares Matei Dumitrescu mateidum828@gmail.com

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "/home/mateidumitrescu/Documents/Tema2-sd/structures.h"
#include "/home/mateidumitrescu/Documents/Tema2-sd/hashtable_utils.h"
#include "/home/mateidumitrescu/Documents/Tema2-sd/utils.h"

#define DEFINITIONS "definitions"  // Macros for dictionary types
#define BOOKS "books"  // Macros for dictionary types
#define USERS "users"  // Macros for dictionary types

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
    printf("Books ranking:\n");
    if (books_ht->size > 0) {
        book_ranking_t *arr_books =
        malloc(books_ht->size * sizeof(book_ranking_t));
        int index = 0;
        for (unsigned int i = 0; i < books_ht->hmax; i++) {
            ll_node_t *current = books_ht->buckets[i]->head;
            while (current != NULL) {
                key_value_t *book = (key_value_t *)current->data;
                snprintf(arr_books[index].name,
                         sizeof(arr_books[index].name), "%s",
                         (char *)book->key);
                book_info_t *book_details =
                (book_info_t *)ht_get_details(books_ht, book->key);
                arr_books[index].purchases = book_details->purchases;
                arr_books[index].rating = book_details->rating;
                index++;
                current = current->next;
            }
        }
        sort_arr_books(arr_books, books_ht->size);
        for (unsigned int i = 0; i < books_ht->size; i++) {
            printf("%d. Name:%s Rating:%.3f Purchases:%d\n",
                   i + 1, arr_books[i].name,
                   arr_books[i].rating,
                   arr_books[i].purchases);
        }
        free(arr_books);  // free auxiliars
    }
    printf("Users ranking:\n");
    if (users_ht->size > 0) {
        // now sorting for users
        // firstly, we count how many users are not banned
        unsigned int count_users = 0;
        for (unsigned int i = 0; i < users_ht->hmax; i++) {
            ll_node_t *current = users_ht->buckets[i]->head;
            while (current != NULL) {
                key_value_t *user = (key_value_t *)current->data;
                user_info_t *user_details =
                (user_info_t *)ht_get_details(users_ht, user->key);
                if (!user_details->banned) {
                    count_users++;
                }
                current = current->next;
            }
        }
        int index = 0;
        user_ranking_t *arr_users =
        malloc(count_users * sizeof(user_ranking_t));
        for (unsigned int i = 0; i < users_ht->hmax; i++) {
            ll_node_t *current = users_ht->buckets[i]->head;
            while (current != NULL) {
                key_value_t *user = (key_value_t *)current->data;
                user_info_t *user_details =
                (user_info_t *)ht_get_details(users_ht, user->key);
                if (!user_details->banned) {
                    snprintf(arr_users[index].name,
                             sizeof(arr_users[index].name), "%s",
                             (char *)user->key);
                    arr_users[index].points = user_details->points;
                    index++;
                }
                current = current->next;
            }
        }
        sort_arr_users(arr_users, count_users);
        for (unsigned int i = 0; i < count_users; i++) {
            printf("%d. Name:%s Points:%d\n",
                   i + 1, arr_users[i].name, arr_users[i].points);
        }
        free(arr_users);  // free auxiliars
    }
}

void resize_hashtable(hashtable_t **ht, int hmax, char dictionary_type[B_MAX]) {
    hmax = hmax * 2;
    hashtable_t *new_ht = ht_create(hmax, hash_function_string,
                                    compare_function_strings,
                                    dictionary_type);
    for (unsigned int i = 0; i < (*ht)->hmax; i++) {
        ll_node_t *current = (*ht)->buckets[i]->head;
        ll_node_t *prev = current;
        while (current != NULL) {
            key_value_t *data = (key_value_t *)current->data;
            char *key = (char *)data->key;
            unsigned int key_size = strlen(key) + 1;
            if (strcmp(dictionary_type, BOOKS) == 0) {
                hashtable_t *def_ht = (hashtable_t *)data->value;
                ht_put(new_ht, data->key, key_size, def_ht, sizeof(hashtable_t),
                       current->details, BOOKS);
                free(data->key);
                free(def_ht);
                free(data);
            } else if (strcmp(dictionary_type, USERS) == 0) {
                char *value = NULL;
                unsigned int value_size = 0;
                if (data->value != NULL) {
                    value = (char *)data->value;
                    value_size = strlen(value) + 1;
                    ht_put(new_ht, data->key, key_size, data->value, value_size,
                       current->details, USERS);
                    free(data->value);
                } else {
                    ht_put(new_ht, data->key, key_size, NULL, 0,
                       current->details, USERS);
                }
                free(data->key);
                free(data);
            } else {
                char *value = (char *)data->value;
                unsigned int value_size = strlen(value) + 1;
                ht_put(new_ht, data->key, key_size, data->value, value_size,
                       NULL, DEFINITIONS);
                free(data->key);
                free(data->value);
                free(data);
            }
            current = current->next;
            if (prev->details)
                free(prev->details);
            free(prev);
            prev = current;
        }
        free((*ht)->buckets[i]);
    }
    free((*ht)->buckets);
    free(*ht);
    *ht = new_ht;
}
