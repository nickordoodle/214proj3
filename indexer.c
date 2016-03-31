#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
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


	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir ("c:\\src\\")) != NULL) {
  		/* print all the files and directories within directory */
	  while ((ent = readdir (dir)) != NULL) {
	    printf ("%s\n", ent->d_name);
	  }
  	closedir (dir);
	} else {
  	/* could not open directory */
  	perror ("");
  	//return EXIT_FAILURE;
	}
	return 0;
} 
