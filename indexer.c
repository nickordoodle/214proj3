#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include "indexer.h"
#include "binary-search-tree.h"
#include "tokenizer.h"

Record *BST_head;
int isProgramInit;

/* OVERALL ALGORITHM:
	Keep Hash Table to keep list of "Records" which keep file names and times occurred
	Keep Tokenizer binary search tree of all tokens
testing
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

		/* Read the files and directories within directory */
   		while ((entry = readdir (dir)) != NULL) {

	    	/* Ignore its own directory and parent directory */
   			if (strcmp(entry->d_name, ".") == 0
   				|| strcmp(entry->d_name, "..") == 0){
   				continue;
   		}

		/* Case for files */
   		if (entry->d_type == DT_REG){

   			char *temp = malloc(sizeof(char) * strlen(entryName));
   			strcpy(temp, entryName);
   			fileHandler(strcat(strcat(temp, "/"), entry->d_name));
   			free(temp);

   		} 
   		/* Case for directories, recurse on on that directory */
   		else if(entry->d_type == DT_DIR){

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

	FILE *fp;
	long fileSize;
	char *buffer;

	/* Try opening file in read mode and check
	   if the file is NULL or is empty */
	fp = fopen ( name , "r" );
	if( !fp ) {

		perror(name);
		return;
	}

	/* Get size of file */
	fseek( fp , 0L , SEEK_END);
	fileSize = ftell( fp );
	rewind( fp );

	/* Allocate memory for entire buffer */
	buffer = calloc( 1, fileSize+1 );
	if( !buffer ) fclose(fp),fputs("memory alloc fails",stderr),exit(1);

	/* Copy the file into the buffer */
	if( 1!=fread( buffer , fileSize, 1 , fp) )
	fclose(fp),free(buffer),fputs("entire read fails",stderr),exit(1);

	/* Start tokenizing */
	TokenizerT *tokenizer = TKCreate(buffer);

	/* Iterates until no more tokens exist */
	while (hasNextToken(tokenizer)){
		
		/* Get the next token from input */
		char *newToken = TKGetNextToken(tokenizer);
		
		/* Will return null if token is invalid*/
                if(newToken == NULL)
                        continue;

		/* Ensure that the token is not empty string */
		if(strlen(newToken) > 0){
			
			/*Adds the new/updates Token in BST*/
			SLInsert(newToken, name);

			/* Init globals if the program has not run through yet */
			if(!isProgramInit){
				isProgramInit = 1;
			}
			
		}

			
		free(newToken);
			
	}
	
	/* Memory and file handling */
	TKDestroy(tokenizer);

	fclose(fp);
	free(buffer);
}

/* Gives our global variables values to start the program */
void initGlobals(){

	BST_head = NULL;
	isProgramInit = 0;
}

int main(int argc, char const *argv[]) {

	FILE *fp;
    size_t length = strlen(argv[2]);
	char *dirStream = malloc(length + 1 + 1 ); 

	/* Check if proper number of arguments are entered */
	if(argc < 3){
		printf("Bad input: Not enough arguments \n"); 
		return 0;
	} 

	initGlobals();



    char c = '/';
    dirStream[0] = c;
    strcpy(dirStream + 1, argv[2]);
    dirStream[length + 1] = '\0';

	/* Call our file manager functions on the input */
	directoryHandler(argv[2]);

	fp = fopen(argv[1], "r");

	/* The output inverted index file exists already */
	if (fp) {
		printf("The file \"%s\" you tried creating already exists \n", argv[1]);
		return 0;
	} else {

		/* Build the inverted index JSON formatted text file
		   using the given file name */
		if(isProgramInit == 1){
			printf("Could not retrieve any data from the given directory or index: %s \n", argv[2]);
			return 0;
		}

		/* Uses our generated data structures and uses the binary search tree
		   structure to iterate through all tokens, files, and counts to properly
		   build the inverted index or JSON file */
		fp = fopen(argv[1], "w+");
		writeToFile(fp);

	}

	fclose(fp);

	return 0;

} 
