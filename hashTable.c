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

hashTable *createHashTable(int size){

	return 0;
}


void destroyHashTable(hashTable *table){



}


/*
	First, use hash function on the token.  If new, insert new Record.
	Else, search through the Records linked list for a match and if match, increment occurence.
	Else, insert new record at the end of the list.

*/
int addToHashTable(hashTable table, char *token, char *fileName){




	return 0;
}