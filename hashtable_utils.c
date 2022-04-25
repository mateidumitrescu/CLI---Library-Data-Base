// Copyright 2022 Rares Matei Dumitrescu mateidum828@gmail.com

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "structures.h"
#define S 40
#define DEFINITIONS "definitions"
#define BOOKS "books"
#define USERS "users"

linked_list_t *ll_create(unsigned int data_size, unsigned int details_size)
{
    linked_list_t *ll = malloc(sizeof(*ll));

    ll->head = NULL;
    ll->data_size = data_size;
    ll->details_size = details_size;
    ll->size = 0;

    return ll;
}

void ll_add_nth_node(linked_list_t* list, unsigned int n,
                     void *new_data, void *details)
{
    ll_node_t *prev, *curr;
    ll_node_t* new_node;

    if (!list) {
        return;
    }

    if (n > list->size) {
        n = list->size;
    }

    curr = list->head;
    prev = NULL;
    while (n > 0) {
        prev = curr;
        curr = curr->next;
        --n;
    }

    new_node = malloc(sizeof(*new_node));
    new_node->data = malloc(list->data_size);
    memcpy(new_node->data, new_data, list->data_size);
    if (details) {  // check if there are any details to assign to node
        new_node->details = malloc(list->details_size);
        memcpy(new_node->details, details, list->details_size);
    } else {  // definitions dictionary doesn't need details
        new_node->details = NULL;
    }

    new_node->next = curr;
    if (prev == NULL) {
        list->head = new_node;
    } else {
        prev->next = new_node;
    }

    list->size++;
}

ll_node_t *ll_remove_nth_node(linked_list_t* list, unsigned int n)
{
    ll_node_t *prev, *curr;

    if (!list || !list->head) {
        return NULL;
    }

    if (n > list->size - 1) {
        n = list->size - 1;
    }

    curr = list->head;
    prev = NULL;
    while (n > 0) {
        prev = curr;
        curr = curr->next;
        --n;
    }

    if (prev == NULL) {
        list->head = curr->next;
    } else {
        prev->next = curr->next;
    }

    list->size--;

    return curr;
}

unsigned int ll_get_size(linked_list_t* list)
{
     if (!list) {
        return -1;
    }

    return list->size;
}

void ll_free(linked_list_t** pp_list)
{
    ll_node_t* currNode;

    if (!pp_list || !*pp_list) {
        return;
    }

    while (ll_get_size(*pp_list) > 0) {
        currNode = ll_remove_nth_node(*pp_list, 0);
        free(currNode->data);
        currNode->data = NULL;
        free(currNode);
        currNode = NULL;
    }

    free(*pp_list);
    *pp_list = NULL;
}

int compare_function_strings(void *a, void *b)
{
	char *str_a = (char *)a;
	char *str_b = (char *)b;

	return strcmp(str_a, str_b);
}

unsigned int hash_function_string(void *a)
{
	/*
	 * Credits: http://www.cse.yorku.ca/~oz/hash.html
	 */
	unsigned char *puchar_a = (unsigned char*) a;
	int64_t hash = 5381;
	int c;

	while ((c = *puchar_a++))
		hash = ((hash << 5u) + hash) + c; /* hash * 33 + c */

	return hash;
}

hashtable_t *ht_create(unsigned int hmax,
                       unsigned int (*hash_function)(void*),
		               int (*compare_function)(void*, void*),
                       char dictionary_type[S])
{
	hashtable_t *ht = malloc(sizeof(*ht));
    ht->hmax = hmax;
    ht->size = 0;
    ht->hash_function = hash_function;
    ht->compare_function = compare_function;

    ht->buckets = malloc(ht->hmax * sizeof(linked_list_t *));
    for (unsigned int i = 0; i < ht->hmax; i++) {
        if (strcmp(dictionary_type, BOOKS) == 0) {
            ht->buckets[i] = ll_create(sizeof(key_value_t),
                                       sizeof(book_info_t));
        } else if (strcmp(dictionary_type, DEFINITIONS) == 0) {
            ht->buckets[i] = ll_create(sizeof(key_value_t), 0);
        } else if (strcmp(dictionary_type, USERS) == 0) {
            ht->buckets[i] = ll_create(sizeof(key_value_t),
                                       sizeof(user_info_t));
        }
        ht->buckets[i]->head = NULL;
    }

    return ht;
}

int ht_has_key(hashtable_t *ht, void *key)
{
    if (ht == NULL || key == NULL)
        return 0;

    int id = ht->hash_function(key) % ht->hmax;
    ll_node_t *current = ht->buckets[id]->head;

    while (current != NULL) {
        key_value_t *data = (key_value_t *)current->data;
        if (ht->compare_function(key, data->key) == 0)
            return 1;
        current = current->next;
    }
	return 0;
}

void *ht_get_key_value(hashtable_t *ht, void *key) {
    if (ht == NULL || key == NULL)
        return NULL;

    if (ht_has_key(ht, key) == 0)
        return NULL;

    int id = ht->hash_function(key) % ht->hmax;
    ll_node_t *current = ht->buckets[id]->head;
    while (current != NULL) {
        key_value_t *data = (key_value_t *)current->data;
        if (ht->compare_function(key, data->key) == 0)
            return data;
        current = current->next;
    }

	return NULL;
}

void *ht_get(hashtable_t *ht, void *key) {
	if (ht == NULL || key == NULL)
        return NULL;

    if (ht_has_key(ht, key) == 0)
        return NULL;

    int id = ht->hash_function(key) % ht->hmax;
    ll_node_t *current = ht->buckets[id]->head;
    while (current != NULL) {
        key_value_t *data = (key_value_t *)current->data;
        if (ht->compare_function(key, data->key) == 0)
            return data->value;
        current = current->next;
    }

	return NULL;
}

void ht_put(hashtable_t *ht, void *key, unsigned int key_size,
	        void *value, unsigned int value_size, void *details,
            char dictionary_type[S])
{
	if (ht_has_key(ht, key)) {
        key_value_t *key_value = ht_get_key_value(ht, key);
        free(key_value->value);
        key_value->value = malloc(value_size);
        memcpy(key_value->value, value, value_size);
        return;
    }

    int id = ht->hash_function(key) % ht->hmax;
    key_value_t data;
    data.key = malloc(key_size);
    memcpy(data.key, key, key_size);
    data.value = malloc(value_size);
    memcpy(data.value, value, value_size);

    if (strcmp(dictionary_type, BOOKS) == 0) {
        book_info_t *book_details = (book_info_t *)details;
        ll_add_nth_node(ht->buckets[id], 0, &data, book_details);
    } else if (strcmp(dictionary_type, DEFINITIONS) == 0) {
        ll_add_nth_node(ht->buckets[id], 0, &data, NULL);
    } else if (strcmp(dictionary_type, USERS) == 0) {
        user_info_t *user_details = (user_info_t *)details;
        ll_add_nth_node(ht->buckets[id], 0, &data, user_details);
    }

    ht->size++;
}

void ht_free(hashtable_t *ht, char dictionary_type[S]) {
    for (unsigned int i = 0; i < ht->hmax; i++) {
        if (ht->buckets[i]->head != NULL) {
            ll_node_t *node = ht->buckets[i]->head, *prev;
            while (node != NULL) {
                prev = node;
                node = node->next;

                key_value_t *data = (key_value_t *)prev->data;
                if (strcmp(dictionary_type, USERS) == 0) {
                    free(data->key);
                    free(prev->details);
                    if (sizeof(data->value) > 0) {
                        free(data->value);
                    }
                    free(prev->data);
                    free(prev);
                } else if (strcmp(dictionary_type, BOOKS) == 0) {
                    free(prev->details);
                    free(data->key);
                    hashtable_t *definitions_ht = (hashtable_t *)data->value;
                    ht_free(definitions_ht, DEFINITIONS);
                    free(prev->data);
                    free(prev);
                } else if (strcmp(dictionary_type, DEFINITIONS) == 0) {
                    free(data->key);
                    free(data->value);
                    free(prev->data);
                    free(prev);
                }
            }
        }
        free(ht->buckets[i]);
    }
    free(ht->buckets);
    free(ht);
}

void ht_remove_entry(hashtable_t *ht, void *key, char dictionary_type[S])
{
    if (ht == NULL || key == NULL)
        return;

    if (ht_has_key(ht, key) == 0)
        return;

    int id = ht->hash_function(key) % ht->hmax;
    ll_node_t *current = ht->buckets[id]->head;
    key_value_t *data;
    int current_pos = 0;

    while (current != NULL) {
        data = (key_value_t *)current->data;
        if (ht->compare_function(key, data->key) == 0)
            break;
        current_pos++;
        current = current->next;
    }

    current = ll_remove_nth_node(ht->buckets[id], current_pos);
    data = (key_value_t *)current->data;
    if (strcmp(dictionary_type, BOOKS) == 0) {
        // we have to check what type of dictionary we work with
        hashtable_t *definitions_ht = (hashtable_t *)data->value;
        free(current->details);
        free(data->key);
        ht_free(definitions_ht, DEFINITIONS);
        free(current->data);
        free(current);
    } else if (strcmp(dictionary_type, DEFINITIONS) == 0) {
        free(data->key);
        free(data->value);
        free(data);
        free(current);
    }  // no need for users
    ht->size--;
}

void *ht_get_details(hashtable_t *ht, void *key) {
    if (ht == NULL || key == NULL) {
        return NULL;
    }

    if (ht_has_key(ht, key) == 0) {
        return NULL;
    }

    int id = ht->hash_function(key) % ht->hmax;
    ll_node_t *current = ht->buckets[id]->head;
    while (current != NULL) {
        key_value_t *data = (key_value_t *)current->data;
        if (ht->compare_function(key, data->key) == 0) {
            return current->details;
        }
        current = current->next;
    }

    return NULL;
}
