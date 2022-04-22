// Copyright 2022 Rares Matei Dumitrescu mateidum828@gmail.com

#ifndef DEFINITIONS_UTILS_H_
#define DEFINITIONS_UTILS_H_

#define HMAX 10
#define B_MAX 40
#define KV_MAX 20
#define C_MAX 10
#define BUF 125

// function to add a key and a definition in a book
void add_definition(hashtable_t *books_ht, char book_name[B_MAX],
                    char key_name[KV_MAX], char value_name[KV_MAX]);

// function to get a definition of a given key from a given book
void get_definition(hashtable_t *books_ht, char book_name[B_MAX],
                    char key_name[KV_MAX]);

// function to remove a definition from a book
void remove_definition(hashtable_t *books_ht, char book_name[B_MAX], char key_name[KV_MAX]);

#endif  // DEFINITIONS_UTILS_H_