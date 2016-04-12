#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "index.h"
#include "sorted-list.h"
#include "tokenizer.h"


/* Handles directory searches */
void directoryHandler(const char *name){

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
	  			strcat(temp, "/");
	   			strcat(temp, entry->d_name);
	   			fileHandler(temp);
	   			free(temp);

	   		} 
	   		/* Case for directories, recurse on on that directory */
	   		else if(entry->d_type == DT_DIR){

			   	char *temp = malloc(sizeof(char) * strlen(entryName));
	   			strcpy(temp, entryName);
	   			strcat(temp, "/");
	   			strcat(temp, entry->d_name);
	   			const char *directory = temp;
				directoryHandler(directory);
	   			free(temp);

   			}

   		}

   	closedir (dir);

   } else {

		/* could not open directory */
   		perror ("");
   		exit(0);
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
   		exit(0);

	}

	/* Get size of file */
	fseek( fp , 0L , SEEK_END);
	fileSize = ftell( fp );
	rewind( fp );

	if(!fileSize){
		printf("Empty file found \n");
		exit(0);
	}

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
			
		}

		free(newToken);
	}
	
	/* Memory and file handling */
	TKDestroy(tokenizer);

	fclose(fp);
	free(buffer);	
}


int main(int argc, char const *argv[]) {

	/* Check if proper number of arguments are entered */
	if(argc < 3){
		printf("Bad input: Not enough arguments \n"); 
		return 0;
	} 

	FILE *fp;
	char *fileName = (char *) malloc(strlen(argv[2]));
	strcpy(fileName, argv[2]);

    if(*(fileName + strlen(fileName) - 1) == '/')
    	fileName[strlen(fileName) - 1] = '\0';

	struct stat statbuf;
	stat(fileName, &statbuf);

	/* Check if initially directory or file */
	if(S_ISDIR(statbuf.st_mode)){
		directoryHandler(fileName);
	}
	/* Handles the case for a single file input */
	else{
		fileHandler(fileName);

	}

	/* Open the output */
	fp = fopen(argv[1], "r");

	/* The output inverted index file exists already */
	if (fp) {
		char str[2];
		printf("The output file you entered already exists, would you like to overwrite it? (y/n)");
		scanf("%s", str);

		if(str[0] == 'y' || str[0] == 'Y'){
			fp = fopen(argv[1], "w+");
			writeToFile(fp);
			printf("File overwritten.\n");
		} else if(str[0] == 'n' || str[0] == 'N'){
			printf("You chose not to overwrite the file, exiting now.\n");
			return 0;
		} else{
			printf("Invalid option, exiting now.\n");
			return 0;
		}

	} else {

		/* Uses our generated data structures and uses the binary search tree
		   structure to iterate through all tokens, files, and counts to properly
		   build the inverted index or JSON file */
		fp = fopen(argv[1], "w+");
		writeToFile(fp);

	}

	free(fileName);
	fclose(fp);

	return 0;

} 
