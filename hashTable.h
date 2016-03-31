#include <stdlib.h>

/* This is the data structure we 'hash' to and acts as a linked 
   list if the token is found in multiple files.  For example,
   'and' is found in file Boo and Baa.  So the it hashes to
   Boo:1 --> Baa:1  and so on.

 */

typedef struct Record_ Record;
struct Record {

	char *fileName;
	int occurrences;
	Record *next;
	Record *prev;


};


typedef struct hashTable_ HashTable;
struct HashTable {
	int size;
	int isInitialized;
	Record *hashArray;	
};


Record *createRecord(char *fileName, int occurrences);
void destroyRecord(Record *record);
HashTable *createHashTable(int size);
void destroyHashTable(hashTable *table);
int hashFunction(char *token);
void swapRecords(Record *prev, Record *curr);
int addToHashTable(HashTable table, char *token, char *fileName);
int createHashTable();
int destroyHashTable();

