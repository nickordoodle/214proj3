#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hashTable.h"


Record *createRecord(char *fileName, int occurrences){

	Record *record = malloc(sizeof(Record));
	record->fileName = fileName;
	record->occurrences = occurrences;
	record->next = NULL;
	record->prev = NULL;

	return record;
}


void destroyRecord(Record *record){

	record->fileName = NULL;
	record->occurrences = -1;
	record->next = NULL;
	record->prev = NULL;
	free(record);

}

HashTable *createHashTable(int size){


	/* Allocate the requested size of table, may vary depending on data size */
	int arraySizeAllocation = size * sizeof(Record);
	HashTable *ht = malloc(sizeof(HashTable));

	ht->size = size;
	ht->isInitialized = 1;

	Record **arrayPtr = malloc(arraySizeAllocation * sizeof(Record));
	ht->hashArray = arrayPtr;

	return ht;
}

/* Frees the memory allocated from creating the hash table */
void destroyHashTable(HashTable *table){

	int position = 0;
	Record **hashArray = table->hashArray;

	while(position != table->size){

		if(hashArray[position]->next != NULL){
			/* TO IMPLEMENT: FREE EACH NODE IN LINKED LIST */
		} else if(hashArray[position] != NULL){

			hashArray[position] = NULL;
			free(hashArray[position]);
			position++;
		}

	}

}

/* djb2 hash function algorithm to minimize collisions */
int hashFunction(char *token){

	long hash = 5381;
    int c;

    while ((c = *token++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;

}

/* Used for readability and easily swap data from
   the current record and the next record */
void swapRecords(Record *prev, Record *curr){

	char *tempFileName = prev->fileName;
	int tempOccurrences = prev->occurrences;
	prev->fileName = curr->fileName;
	prev->occurrences = curr->occurrences;
	curr->fileName = tempFileName;
	curr->occurrences = tempOccurrences;

}
/*
	First, use hash function on the token.  If new, insert new Record.
	Else, search through the Records linked list for a match and if match, increment occurence.
	Else, insert new record at the end of the list.

*/
int addToHashTable(HashTable *table, char *token, char *fileName){

	/* Should return a 'key' value to be inserted into the table */
	int position = hashFunction(token);

	Record **arrayPtr = table->hashArray;
	Record *firstRecord = arrayPtr[position];

	Record *newRecord = malloc(sizeof(Record));
	newRecord = createRecord(fileName, 1);

	/* Check for collision by seeing if a Record exists in that key value
	   position or not */
	if( firstRecord != NULL){

		Record *curr = firstRecord;
		Record *next = curr->next;
		Record *prev = curr->prev;

		int sameFileFound = 0;

		/*Check for match first, then insert based on ascending
		  order of occurrences */
		do{
			/* Copy data over one node */
			if(sameFileFound && prev->occurrences > curr->occurrences){

				/* Swap data */
				swapRecords(prev, curr);

			}
			

			/* Same file found, increment occurrences and readjust list if necessary */
			if(!strcmp(fileName, curr->fileName)){

				sameFileFound = 1;
				curr->occurrences++;


				/* Need to shift the current Record over in the linked list */

				/* TO IMPLEMENT: NEED TO MOVE RECORDS OVER IN LINKED LIST IF IT APPLIES
				EX. Our list: baa:3->4, boo:3, bee:4
				       After: boo:3, baa:4, bee:4 */
			}

			prev = curr;
			curr = next;
			next = curr->next;

		} while(curr != NULL);


		/* Same file not found, add to front of linked list */
		newRecord->next = curr;
		curr->prev = newRecord;
		arrayPtr[position] = newRecord;

	} else{

		/* New token found so this is the first Record in this position */
		arrayPtr[position] = newRecord;

	}



	return 0;
}