// Copyright 2022 Rares Matei Dumitrescu mateidum828@gmail.com

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "structures.h"
#include "hashtable_utils.h"

#define S 40
#define DEFINITIONS 0  // Macros for dictionary types
#define BOOKS 1  // Macros for dictionary types
#define USERS 2  // Macros for dictionary types

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
		               int (*compare_function)(void*, void*))
{
	hashtable_t *ht = malloc(sizeof(*ht));
    ht->hmax = hmax;
    ht->size = 0;
    ht->hash_function = hash_function;
    ht->compare_function = compare_function;

    ht->buckets = malloc(ht->hmax * sizeof(linked_list_t *));
    for (unsigned int i = 0; i < ht->hmax; i++) {
        ht->buckets[i] = ll_create(sizeof(key_value_t),
                                   sizeof(book_info_t));
        ht->buckets[i]->head = NULL;
    }

    return ht;
}

int ht_has_key(hashtable_t *ht, void *key)
{
    if (ht->size == 0)
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
    // no need to check if ht_has_key or if key is null,
    // already did it in call function
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
	        void *value, unsigned int value_size, void *details)
{
    key_value_t *key_value = ht_get_key_value(ht, key);
    if(key_value) {
        free(key_value->value);
        if (value == NULL) {
            key_value->value = NULL;
            return;
        }
        key_value->value = malloc(value_size);
        memcpy(key_value->value, value, value_size);
        return;
    }

    int id = ht->hash_function(key) % ht->hmax;
    key_value_t data;
    data.key = malloc(key_size);
    memcpy(data.key, key, key_size);
    data.value = NULL;
    if (value != NULL) {
        data.value = malloc(value_size);
        memcpy(data.value, value, value_size);
    }

    ll_add_nth_node(ht->buckets[id], 0, &data, details);
    

    ht->size++;
}

void ht_free(hashtable_t *ht, int dictionary_type) {
    for (unsigned int i = 0; i < ht->hmax; i++) {

            ll_node_t *node = ht->buckets[i]->head, *prev;
            while (node != NULL) {
                prev = node;
                node = node->next;

                key_value_t *data = (key_value_t *)prev->data;
                if (dictionary_type == BOOKS) {
                    free(prev->details);
                    free(data->key);
                    hashtable_t *definitions_ht = (hashtable_t *)data->value;
                    ht_free(definitions_ht, DEFINITIONS);
                    free(prev->data);
                    free(prev);
                } else {
                    free(data->key);
                    free(data->value);
                    free(prev->data);
                    free(prev->details);
                    free(prev);
                }
            }
        free(ht->buckets[i]);
    }
    free(ht->buckets);
    free(ht);
}

void  ht_remove_entry(hashtable_t *ht, void *key, int dictionary_type)
{
    // no need to check if ht_has_key or if key is null,
    // already did it in call function
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
    if (dictionary_type == BOOKS) {
        hashtable_t *definitions_ht = (hashtable_t *)data->value;
        free(current->details);
        free(data->key);
        ht_free(definitions_ht, DEFINITIONS);
        free(current->data);
        free(current);
    } else if (dictionary_type == DEFINITIONS) {
        free(data->key);
        free(data->value);
        free(data);
        free(current);
    }  // no need for users
    ht->size--;
}

void *ht_get_details(hashtable_t *ht, void *key) {
    // no need to check if ht_has_key or if key is null,
    // already did it in call function
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
