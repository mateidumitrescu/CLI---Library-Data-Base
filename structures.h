// Copyright 2022 Rares Matei Dumitrescu mateidum828@gmail.com

#ifndef STRUCTURES_H_
#define STRUCTURES_H_

typedef struct ll_node_t
{
    void *data;
    void *details;
    struct ll_node_t* next;
} ll_node_t;

typedef struct linked_list_t
{
    ll_node_t* head;
    unsigned int details_size;
    unsigned int data_size;
    unsigned int size;
} linked_list_t;

typedef struct key_value_t {
	void *key;
	void *value;
} key_value_t;

typedef struct hashtable_t {
	linked_list_t **buckets;
	unsigned int size;
	unsigned int hmax; 
	unsigned int (*hash_function)(void*);
	int (*compare_function)(void*, void*);
} hashtable_t;

typedef struct book_info_t {
    double rating;
    double purchases;
    int borrowed;
} book_info_t;

typedef struct user_info_t {
    int points;
    int banned;
    int borrow_period;
    int return_period;
} user_info_t;

#endif  // STRUCTURES_H_