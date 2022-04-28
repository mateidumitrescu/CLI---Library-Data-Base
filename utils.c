// Copyright 2022 Rares Matei Dumitrescu mateidum828@gmail.com

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "structures.h"
#include "hashtable_utils.h"
#include "utils.h"

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

int compare_users( const void* a, const void* b)
{
     user_ranking_t user_a = *((user_ranking_t*) a);
     user_ranking_t user_b = *((user_ranking_t*) b);

     if (user_a.points < user_b.points) return 1;
     else if (user_a.points > user_b.points) return -1;
     else if (strcmp(user_a.name, user_b.name) > 0) return 1;
     else if (strcmp(user_a.name, user_b.name) < 0) return -1;
     return 0;
}

int compare_books( const void* a, const void* b)
{
     book_ranking_t book_a = * ( (book_ranking_t*) a );
     book_ranking_t book_b = * ( (book_ranking_t*) b );

     if (book_a.rating < book_b.rating) return 1;
     else if (book_a.rating > book_b.rating) return -1;
     else if (book_a.purchases < book_b.purchases) return 1;
     else if (book_a.purchases > book_b.purchases) return -1;
     else if (strcmp(book_a.name, book_b.name) > 0) return 1;
     else if (strcmp(book_a.name, book_b.name) < 0) return -1;
     return 0;
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
        qsort(arr_books, books_ht->size, sizeof(book_ranking_t), compare_books);
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
        int index = 0;
        user_ranking_t *arr_users =
        malloc(users_ht->size * sizeof(user_ranking_t));
        for (unsigned int i = 0; i < users_ht->hmax; i++) {
            ll_node_t *current = users_ht->buckets[i]->head;
            while (current != NULL) {
                key_value_t *user = (key_value_t *)current->data;
                user_info_t *user_details =
                (user_info_t *)ht_get_details(users_ht, user->key);
                if (!user_details->banned) {
                    count_users++;
                    snprintf(arr_users[index].name,
                             sizeof(arr_users[index].name), "%s",
                             (char *)user->key);
                    arr_users[index].points = user_details->points;
                    index++;
                }
                current = current->next;
            }
        }
        qsort(arr_users, count_users, sizeof(user_ranking_t), compare_users);
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
                                    compare_function_strings);
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
