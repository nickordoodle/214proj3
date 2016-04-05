#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include "indexer.h"
#include "binary-search-tree.h"

Record *BST_head;
int isProgramInit;

/* OVERALL ALGORITHM:
	Keep Hash Table to keep list of "Records" which keep file names and times occurred
	Keep Tokenizer binary search tree of all tokens

	For user input (directory or file):
		If(file)
			Read/tokenize file
			Add tokens to token linked list
			Hash each token to hashmap
		Else if (directory)
			For All subdirectories AND files
				Read/tokenize all files
				Add tokens to token linked list
				Hash each token to hashmap

	After iterating through all files and directories,
	BUILD-INVERTED INDEX 
		For each token in alphabetical order (Binary Search Tree)
			Hash the token and add its Record(s) Linked list data to the output
			file in descending order by number of occurrences

	Keep in mind the JSON format of the output

*/

/* Recursively searches for a directory unless 
   the name of the user input is a file, then
   call fileHandler function to deal with it 


   	TO IMPLEMENT: Multiple directory search support
   				  Search child directories for user input search */ 
void directoryHandler(char *name){

   	DIR *dir;
   	struct dirent *entry;
   	char *entryName  = malloc(sizeof(name));
   	strcpy(entryName, name);

   	if ((dir = opendir (entryName)) != NULL) {

		/* print all the files and directories within directory */
   		while ((entry = readdir (dir)) != NULL) {

	    	/* Ignore its own directory and parent directory */
   			if (strcmp(entry->d_name, ".") == 0
   				|| strcmp(entry->d_name, "..") == 0){
   				continue;
   		}

			//Case for a file 
   		if (entry->d_type == DT_REG){

   			char *temp = malloc(sizeof(char) * strlen(entryName));
   			strcpy(temp, entryName);
   			fileHandler(strcat(strcat(temp, "/"), entry->d_name));
   			free(temp);

   		} else if(entry->d_type == DT_DIR){

		 	//Enter recursive directory call if name does
		   	//not match
		   	char *temp = malloc(sizeof(char) * strlen(entryName));
   			strcpy(temp, entryName);
			directoryHandler(strcat(strcat(temp, "/"), entry->d_name));
   			free(temp);

   		}

   	}

   	closedir (dir);

   } else {

		/* could not open directory */
   	perror ("");
   }
}



/* This function will be called when we have
   found a file that we are dealing with */
void fileHandler(char *name){

	// read in file
		// tokenize words
		// put words into index by filename

	FILE *fp;
	long fileSize;
	char *buffer;

	fp = fopen ( name , "r" );
	if( !fp ) {

		perror(name);
		return;
	}

	/* Get size of file */
	fseek( fp , 0L , SEEK_END);
	fileSize = ftell( fp );
	rewind( fp );

	/* allocate memory for entire content */
	buffer = calloc( 1, fileSize+1 );
	if( !buffer ) fclose(fp),fputs("memory alloc fails",stderr),exit(1);

	/* copy the file into the buffer */
	if( 1!=fread( buffer , fileSize, 1 , fp) )
	fclose(fp),free(buffer),fputs("entire read fails",stderr),exit(1);

	/* do your work here, buffer is a string contains the whole text */

	TokenizerT *tokenizer = TKCreate(buffer);

	/* Iterates loop until end of array */
	while (hasNextToken(tokenizer)){
		
		// Get token string, the type has already been printed 
		char *newToken = TKGetNextToken(tokenizer);

		/* Add to binary search tree */
		if(strlen(newToken) > 0){

			if(!isProgramInit){

				BST_head = createNewRecord(name, newToken, 1, NULL, NULL, NULL, NULL);
				isProgramInit = 1;
			}

			else{

				Record *newRecord = insert(BST_head, newToken, name);
		
				if(!newRecord)
					printf("The token: %s already exists. \n", newToken );
				else
					printf("Successfully inserted the token: %s from file: %s \n",
				 	newToken, name);
			}	

			
			
		}

			
		free(newToken);
			
	}
	
	TKDestroy(tokenizer);

	fclose(fp);
	free(buffer);

}


void initGlobals(){

	BST_head = NULL;
	isProgramInit = 0;


}



int main(int argc, char const *argv[]) {

	FILE *fp;
    size_t length = strlen(argv[2]);
	char *dirStream = malloc(length + 1 + 1 ); 

	if(argc < 3){
		printf("Bad input: Not enough arguments \n"); 
		return 0;
	} 

	initGlobals();

	/* Call our file manager functions on the input */


    char c = '/';
    dirStream[0] = c;
    strcpy(dirStream + 1, argv[2]);
    dirStream[length + 1] = '\0';

	directoryHandler(argv[2]);

	fp = fopen(argv[1], "r");

	/* File exists already, ask for input again */
	if (fp) {
		printf("The file \"%s\" you tried creating already exists \n", argv[1]);
		return 0;
	} else {

		/* Build the inverted index JSON formatted text file
		   using the given file name */
		if(!BST_head){
			printf("Could not retrieve any data from the given directory or index: %s \n", argv[2]);
		}

		fp = fopen(argv[1], "w+");
		writeToFile(BST_head, fp, getRightMostRecord(BST_head));

	}

	fclose(fp);

	return 0;

} 
