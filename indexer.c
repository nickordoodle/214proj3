#include <stdlib.h>
#include <stdio.h>
#include "indexer.h"

/*
	Keep Hash Table to keep list of "Records" which keep file names and times occurred
	Keep Tokenizer linked listed of descending order of each token

	For each directory:
		For each file in that directory:
			If new token insert token into linked list and hash new occurrence
			else if not new token, hash occurrence and add the number to new file


	Go through tokenizer linked list, hash each token and print out each token, then their records
	in ascending order by number of times in each file

*/

int main(int argc, char const *argv[]) {

	//IMPLEMENT
	return 0;
} 
