// Copyright 2022 Rares Matei Dumitrescu mateidum828@gmail.com

#ifndef UTILS_H_
#define UTILS_H_

#define BUF 125
#define B_MAX 40

// function to shift to left the letters of a string
void shift_letters(char book_name[B_MAX]);

// function to get the name of the book
char *get_book_name(char line[BUF], char book_name[B_MAX]);

#endif  // UTILS_H_