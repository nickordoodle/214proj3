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


};


typedef struct hashTable_ hashTable;
struct hashTable {
	int size;
	Record **table;	
};


Record *createRecord(char *fileName, int occurrences);
void destroyRecord(Record *record);
hashTable *createHashTable(int size);
void destroyHashTable(hashTable *table);
int addToHashTable(hashTable table, char *token, char *fileName);
int createHashTable();
int destroyHashTable();

