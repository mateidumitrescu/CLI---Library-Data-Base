**Name: Dumitrescu Rares Matei**
**Group: 311CA**

## Library Data Base

### Description:

This project uses 3 different hashtables that work together:

    HASHTABLE of DEFINITIONS - this hashtable is a normal key - value hashtable
    which is used to store different words together with their meaning

    HASHTABLE of BOOKS - this hashtable stores different book names and each book
    stores in its value a HASHTABLE of DEFINITIONS that was mentioned above

    HASHTABLE of USERS - this hashtable stores user names together with the book they 
    borrowed

In order to create a program which works such as a normal library data base, the program
has new structures implemented which are stored in the node structure. The hashtables nodes
(except for the HASHTABLE of DEFINITONS) get a void *details field which will store a 
structure about the book / user properties.

For example, user_info_t structure stores a user points, the borrow period he asked for a book,
if he has already borrowed a book and if he was banned from the library. book_info_t structure
is used to store the number of purchases of a book, its rating and if it was borrowed.

What needs to be mentioned is that when a new user is registered in the system, its data->value
block will be NULL and it will change only when he borrows a book.

The commands used for this program can be easily seen in the main.c file and it is very simple
to use.

### Comments on project:

I think this program could be a lot better optimized in order to run faster. This project
was a good practice to have a good base in hashtables implementations and use of them.
