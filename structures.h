// Copyright 2022 Rares Matei Dumitrescu mateidum828@gmail.com

#ifndef _HOME_MATEIDUMITRESCU_DOCUMENTS_TEMA2_SD_STRUCTURES_H_
#define _HOME_MATEIDUMITRESCU_DOCUMENTS_TEMA2_SD_STRUCTURES_H_

#define B_MAX 40
#define U_MAX 20

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
    int sum_of_ratings;
    int purchases;
    int borrowed;
} book_info_t;

typedef struct user_info_t {
    int points;
    int banned;
    int has_borrowed;
    int borrow_period;
} user_info_t;

typedef struct book_ranking_t {
    double rating;
    int purchases;
    char name[B_MAX];
} book_ranking_t;

typedef struct user_ranking_t {
    char name[U_MAX];
    int points;
} user_ranking_t;

#endif  // _HOME_MATEIDUMITRESCU_DOCUMENTS_TEMA2_SD_STRUCTURES_H_
