#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include "indexer.h"
#include "hashTable.h"

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
   	entryName = name;

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

   			fileHandler(strcat(strcat(entryName, "/"), entry->d_name));

   		} else if(entry->d_type == DT_DIR){

		 	//Enter recursive directory call if name does
		   	//not match 
			directoryHandler(strcat(strcat(entryName, "/"), entry->d_name));
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
	if( !fp ) perror(name),exit(1);

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

				initGlobals(newToken, name, fileSize);

			} else {

				/* TO IMPLEMENT: HASH/ADD TOKEN/ "RECORD" TO HASHMAP THEN
				ADD TOKEN TO BINARY SEARCH TREE HERE */

			}
			
		}

			
		free(newToken);
			
	}
	
	TKDestroy(tokenizer);

	fclose(fp);
	free(buffer);

}


void initGlobals(char *token, char *fileName, int fileSize){

	ht = createHashTable(fileSize);
	BST_head = token;


	isProgramInit = 1;


}



int main(int argc, char const *argv[]) {

	/* IMPLEMENT: Should handle directories and files separately
	    ex. For each new directory, add data to inverted index for all files
	        in that directory

	   Utilize <fts.h> library and <dirent.h> library for directory/file searching and manipulation
	   Use opendir to check if file or directory
	   REMEMBER:  The User gives us the directory or file to search

	   If cannot find file or directory, just output cannot find directory
	   Be mindful of permission(s) if user does not have access to open directory/file
	   User input can be ABSOLUTE OR RELATIVE PATH(S), need to account for both

	   If dir_type == DT_REG || DT_DIR, file or directory
	*/

	//Build HashMap
	//Build sorted list of descending order of tokens
	//Create file for inverted index

	static char *BST_head;
	static hashTable *ht;
	static int isProgramInit = 0;

	if(argc < 3){
		/* PRINT CUSTOM ERROR MESSAGE */
		return 0;
	}


	/* Call our file manager functions on the input */
	directoryHandler(argv[1]);

} 
