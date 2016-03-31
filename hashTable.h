#include <stdlib.h>

/* This is the data structure we 'hash' to and acts as a linked 
   list if the token is found in multiple files.  For example,
   'and' is found in file Boo and Baa.  So the it hashes to
   Boo:1 --> Baa:1  and so on.

 */

typedef struct Record_ Record;
struct Record_ {

	char *fileName;
	int occurrences;
	Record *next;
	Record *prev;


};


typedef struct HashTable_ HashTable;
struct HashTable_ {
	int size;
	int isInitialized;
	Record **hashArray;	
};


Record *createRecord(char *fileName, int occurrences);
void destroyRecord(Record *record);
int hashFunction(char *token);
void swapRecords(Record *prev, Record *curr);
int addToHashTable(HashTable *table, char *token, char *fileName);
HashTable *createHashTable(int size);
void destroyHashTable(HashTable *table);
