/*

Open Addressed Hash Tables 

- chained hash tables: elements are in buckets extending from each position
- in this table, all elements are in the table itself, good for applications of fixed size
- cause you cant extend at each position, you need to figure out how to handle collisions 

Collision Resolution:
- probe the table
- insert: probe positions, until finding an unoccupied one
- removal/lookup: probe positions until element found or until you find an unoccupied one
- if you get to the unoccupied one, then you dont have the element in the table
- you need to minimize probes, the number of probes depends on: load factor of the hash table and the degree too which elements are 
distributed
- load factor is always less than or equal to 1
- alpha =n/m = number of elements/number of positions
- assuming uniform hashing then positions you probe are 1/(1-alpha)

 hash function for probing positions in an OA Table:

 - h(k,i) = x : k = key, i = number of times table has been probed
 - h must use one or more auxillary hash function but also as i increases from 0 to m-1 (number of positions in table), all positions must have been visited before any position is visited twice

Linear Probing:

h(k,i) = ( h'(k)+i )mod m:

- h' = auxillary hash function
- not very good at uniform hashing
- primary clustering occurs: large chains of unoccupied psoitions develop as table becomes more and more full

Double Hashing:
- adding the hash coding of two auxillary hash functions
- h(k,i) =( h1(k) = ih2(k))mod m
- h1 and h2 are auxillary hash functions
- m must be power of 2 and h2 always return odd value OR m prime and h2 always returns a positive integer less than m

*/
# ifndef OHTBL_H
# define OHTBL_H

# include <stdlib.h>

// define a structure for open addressed hash tables.

/*****************************************************************************
* *
* Define a structure for open-addressed hash tables. *
* *
*****************************************************************************/
typedef struct OHTbl_ {
int positions;
void *vacated;
int (*h1)(const void *key);
int (*h2)(const void *key);
int (*match)(const void *key1, const void *key2);
void (*destroy)(void *data);
int size;
void **table;
} OHTbl;
/*****************************************************************************
* *
* --------------------------- Public Interface --------------------------- *
* *
*****************************************************************************/
int ohtbl_init(OHTbl *htbl, int positions, int (*h1)(const void *key), int
 (*h2)(const void *key), int (*match)(const void *key1, const void *key2),
 void (*destroy)(void *data));
void ohtbl_destroy(OHTbl *htbl);
int ohtbl_insert(OHTbl *htbl, const void *data);
int ohtbl_remove(OHTbl *htbl, void **data);
int ohtbl_lookup(const OHTbl *htbl, void **data);
#define ohtbl_size(htbl) ((htbl)->size)

#endif