// Copyright 2022 Rares Matei Dumitrescu mateidum828@gmail.com

#ifndef _HOME_MATEIDUMITRESCU_DOCUMENTS_TEMA2_SD_HASHTABLE_UTILS_H_
#define _HOME_MATEIDUMITRESCU_DOCUMENTS_TEMA2_SD_HASHTABLE_UTILS_H_

#include "structures.h"
#define S 40

// function to create a linked list
linked_list_t *ll_create(unsigned int data_size,
						 unsigned int properties_size);

// function to add a node in a list
void ll_add_nth_node(linked_list_t* list, unsigned int n,
					 void* new_data, void *properties);

// function to remove a node in a list and return deleted data
ll_node_t *ll_remove_nth_node(linked_list_t* list, unsigned int n);

// function to get the size of a list
unsigned int ll_get_size(linked_list_t* list);

// function to free a list
void ll_free(linked_list_t** pp_list);

// function to compare 2 strings
int compare_function_strings(void *a, void *b);

// function to hash a string
unsigned int hash_function_string(void *a);

// function to create a hashtable
hashtable_t *ht_create(unsigned int hmax,
					   unsigned int (*hash_function)(void*),
		               int (*compare_function)(void*, void*));

// function to check if a key was used before
int ht_has_key(hashtable_t *ht, void *key);

// function to return full key_value_t structure
void *ht_get_key_value(hashtable_t *ht, void *key);

// function to return the value from a given key
void *ht_get(hashtable_t *ht, void *key);

// function to add (key, value) in ht or replace value if the key was used
void ht_put(hashtable_t *ht, void *key, unsigned int key_size,
	        void *value, unsigned int value_size, void *details,
			char dictionary_type[S]);

// function to free data from a hashtable
void ht_free(hashtable_t *ht, char dictionary_type[S]);

// function to remove (key, value) from hashtable if they exist
void ht_remove_entry(hashtable_t *ht, void *key,
					 char dictionary_type[S]);

// function to return details of key in a hashtable
void *ht_get_details(hashtable_t *ht, void *key);

#endif  // _HOME_MATEIDUMITRESCU_DOCUMENTS_TEMA2_SD_HASHTABLE_UTILS_H_
