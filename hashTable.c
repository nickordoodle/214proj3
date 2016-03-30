#include <stdlib.h>
#include <stdio.h>


Record *createRecord(char *fileName, int occurrences){

	Record record = malloc(sizeof(Record));
	record->fileName = fileName;
	record->occurrences = occurrences;
	record->next = NULL;

}


void destroyRecord(Record *record){

	record->fileName = NULL;
	record->occurrences = -1;
	record->next = NULL;
	free(record);

}

HashTable *createHashTable(int size){


	/* Allocate the requested size of table, may vary depending on data size */
	int arraySizeAllocation = size * sizeof(Record);
	HashTable ht = malloc( arraySizeAllocation + (2 * sizeof(int)));

	ht->size = size;
	ht->isInitialized = 1;

	Record hashArray[size];
	Record *arrayPtr = hashArray;
	ht->hashArray = arrayPtr;

	return ht;
}


void destroyHashTable(HashTable *table){



}


int hashFunction(char *token){




	return 0;
}
/*
	First, use hash function on the token.  If new, insert new Record.
	Else, search through the Records linked list for a match and if match, increment occurence.
	Else, insert new record at the end of the list.

*/
int addToHashTable(HashTable table, char *token, char *fileName){

	/* Should return a 'key' value to be inserted into the table */
	int position = hashFunction(token);

	Record *arrayPtr = table->hashArray;


	/* Check for collision by seeing if a Record exists in that key value
	   position or not */
	if( (arrayPtr + position) != NULL){

		Record *curr = arrayPtr + position;
		Record *next = curr->next;

		/*Check for match first, then insert based on ascending
		  order of occurrences */
		while(next != NULL){

			/* Same file found, increment occurrences and readjust list if necessary */
			if(!strcmp(fileName, curr->fileName)){

				curr->occurrences++;

				/* TO IMPLEMENT: NEED TO MOVE RECORDS OVER IN LINKED LIST IF IT APPLIES
				EX. Our list: baa:3->4, boo:3, bee:4
				       After: boo:3, baa:4, bee:4 */
			}

			curr = next;
			next = curr->next;
		}

	} else{



	}



	return 0;
}