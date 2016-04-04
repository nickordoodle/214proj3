#ifndef SORTED_LIST_H
#define SORTED_LIST_H
/*
 * sorted-list.h
 */

#include <stdlib.h>

/*======Prototypes for User-Defined Functions==========
-=-=-=-You do not need to do anything with these definitions-=-=-=-*/

/*
 * Your list is used to store data items of an unknown type, which you need to sort.
 * Since the type is opaque to you, you do not know how to directly compare the data.
 *
 * You can presume though that a user will supply your code with a comparator function
 * that knows how to compare the data being sorted, but your code must do the rest
 * of the bookkeeping in a generic manner.
 *
 * The comparator function will take pointers to two data items and will return -1 if the 1st 
 * is smaller, 0 if the two are equal, and 1 if the 2nd is smaller.
 *
 * The user will also supply a destruct function will take a pointer to a single data item
 *	and knows how to deallocate it. If the data item does not require deallocation, the user's
 *  destruct function will do nothing.
 *
 * Note that you are not expected to implement any comparator or destruct functions.
*  Your code will have appropriate comparator function and a destruct functions added to it.
 */

typedef int (*CompareFuncT)( void *, void * );
typedef void (*DestructFuncT)( void * );



/*-=-=-=-You must implement all the functions and definitions below-=-=-=-

=====0: SortedList=====================================
===0.1: List Definition, List Create/Destroy*/



/* Used to act as our data for the list with pointers to its adjacent 
   data Nodes */
typedef struct Node Node;
struct Node {
	char *token;
	Record head;
	Node *parent;
	Node *left;
	Node *right;

};

typedef struct Record_ Record;
struct Record_ {

	char *fileName;
	int occurrences;
	Record *next;
	Record *prev;
};

/*
 * Sorted list type that will hold all the data to be sorted. 
   This list holds a pointer to the head (front) of the list
   as well as the types of compare functions to use according
   to the data.
*
 *
 */
struct SortedList
{
	Node *head;
	CompareFuncT compare;
	DestructFuncT destroy;

};
typedef struct SortedList* SortedListPtr;


void recordRecord(Node node, char *filename);
/*
 * SLCreate creates a new, empty, 'SortedList'.
 *
 * SLCreate's parameters will be a comparator (cf) and destructor (df) function.
 *   Both the comparator and destructor fuhelpernctions will be defined by the user as per
 *     the prototypes above.
 *   Both functions must be stored in the SortedList struct.
 * 
 * SLCreate must return NULL if it does not succeed, and a non-NULL SortedListPtr
 *   on success.
 */

SortedListPtr SLCreate(CompareFuncT cf, DestructFuncT df);






/*===0.2: List Insert/Remove*/

/*
 * SLInsert inserts a given data item 'newObj' into a SortedList while maintaining the
 *   order and uniqueness of list items.
 * 
 * SLInsert should return 1 if 'newObj' is not equal to any other items in the list and
 *   was successfully inserted.
 * SLInsert should return 0 if 'newObj' is equal to an item already in the list or it was
 *   not successfully inserted
 *
 * Data item equality should be tested with the user's comparator function *
 */

int SLInsert(SortedListPtr list, void *newObj);


/*
 * SLRemove should remove 'newObj' from the SortedList in a manner that
 *   maintains list order.
 *
 * SLRemove must not modify the data item pointed to by 'newObj'.
 *
 * SLRemove should return 1 on success, and 0 on failure.
 */

int SLRemove(SortedListPtr list, void *newObj);




#endif
