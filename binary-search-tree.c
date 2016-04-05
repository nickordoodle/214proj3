#include "binary-search-tree.h"



Record* findMin(Record *record)
{
        if(record == NULL)
        {
                /* There is no element in the tree */
                return NULL;
        }

        if(record->left) /* Go to the left sub tree to find the min element */
                return findMin(record->left);
        else 
                return record;

        return NULL;
}


Record* findMax(Record *record)
{
        if(record == NULL)
        {
                /* There is no element in the tree */
                return NULL;
        }
        if(record->right) /* Go to the left sub tree to find the min element */
                findMax(record->right);
        else 
                return record;

        return NULL;
}

void swapRecords(Record *prev, Record *curr){

	char *tempFileName = prev->fileName;
	int tempOccurrences = prev->occurrences;
	prev->fileName = curr->fileName;
	prev->occurrences = curr->occurrences;
	curr->fileName = tempFileName;
	curr->occurrences = tempOccurrences;

}

Record * createNewRecord(char *fileName, char *token, int occurrences, Record *next,
    Record *prev,
    Record *left,
    Record *right){

    Record *newRecord = malloc(sizeof(Record));
    newRecord ->token = malloc(sizeof(char) * strlen(token));
    newRecord ->fileName = malloc(sizeof(char) * strlen(fileName));
    strcpy(newRecord -> token, token);
    strcpy(newRecord -> fileName, fileName);
    newRecord -> occurrences = 1;
    newRecord -> left = left;
    newRecord -> right = right;
    newRecord -> prev = prev;
    newRecord -> next = next;
    return newRecord;

}

void shiftRecord(Record *recordToShift){

	Record *curr = recordToShift;
	Record *next = recordToShift->next;

	/* Case for only node in linked list or it is
	   already the last node */
	if(next == NULL){
		return;
	} else {

		do{

			if(curr->occurrences > next->occurrences)
				swapRecords(curr, next);

			curr = next;
			next = curr->next;

		} while(curr != NULL);

	}
}


Record * insert(Record *record, char *token, char *fileName) {

		Record *doesRecordExist = find(record, token);
		Record *curr = doesRecordExist;
		int compareVal;

		/* Check if record exists already */
		if(doesRecordExist != NULL){

			int foundSameFile = 0;

			do{
				
				/* check if same file entry exists */
				if(!strcmp(curr->fileName, fileName)){
					foundSameFile = 1;
					curr->occurrences++;
					shiftRecord(curr);
				}

				curr = curr->next;

			} while(curr != NULL && !foundSameFile);

			return doesRecordExist;

		}


        if(record == NULL)
        {
        		// Create new record as head
                Record *newRecord = createNewRecord(fileName, token, 1, NULL, NULL, 
                    NULL, NULL);
                
                return newRecord;	
        }

        compareVal = strcmp(token, record->token);

        if(!compareVal){

        	//Find filename
        	int foundSameFile = 0;

			do{
				Record *curr = doesRecordExist;
				/* check if same file entry exists */
				if(!strcmp(curr->fileName, fileName)){
					foundSameFile = 1;
					curr->occurrences++;
					shiftRecord(curr);
				}

				curr = curr->next;

			} while(curr != NULL && !foundSameFile);

			if(!foundSameFile){

				Record *newRecord = createNewRecord(fileName, token, 1, record, NULL, 
                    NULL, NULL);
                record->prev = newRecord;
                return newRecord;
			}


        } else if(compareVal > 0) {
                record->right = insert(record->right, token, fileName);
        } else if(compareVal < 0) {		
                record->left = insert(record->left, token, fileName);
        }

        /* Else there is nothing to do as the token is already in the tree. */
        return record;

}

Record *delete(Record *record, char *token)
{
        Record *temp;

        if(record==NULL)
        {
                printf("Element Not Found");
        }
        else if(token < record->token)
        {
                record->left = delete(record->left, token);
        }
        else if(token > record->token)
        {
                record->right = delete(record->right, token);
        }
        else
        {
                /* Now We can delete this record and replace with either minimum element 
                   in the right sub tree or maximum element in the left subtree */
                if(record->right && record->left)
                {
                        /* Here we will replace with minimum element in the right sub tree */
                        temp = findMin(record->right);
                        record -> token = temp->token; 
                        /* As we replaced it with some other record, we have to delete that record */
                        record -> right = delete(record->right,temp->token);
                }
                else
                {
                        /* If there is only one or zero children then we can directly 
                           remove it from the tree and connect its parent to its child */
                        temp = record;
                        if(record->left == NULL)
                                record = record->right;
                        else if(record->right == NULL)
                                record = record->left;
                        free(temp); /* temp is longer required */ 
                }
        }
        return record;

}

Record * find(Record *record, char *token)
{
		int compareVal;

        if(record == NULL)
        {
                /* Element is not found */
                return NULL;
        }

        compareVal = strcmp(token, record->token);

        if(compareVal > 0)
        {
                /* Search in the right sub tree. */
                return find(record->right, token);
        }
        else if(compareVal < 0)
        {
                /* Search in the left sub tree. */
                return find(record->left, token);
        }
        else
        {
                /* Element Found */
                return record;
        }
}

/*

{"list" :[
    {"word0" :[
        {"filepath0" : count0},
        {"filepath1" : count1}
    ]},
    {"word1" :[
        {"filepath2" : count2},
        {"filepath3" : count3},
        {“filepath4” : count4}
    ]}
]}
*/

void printFilesAndOccurrencesToFile(Record *record, FILE *fp){

    Record *curr = record;

    do{

        if(record->next == NULL)
            fprintf(fp, "\t {\"%s\" : %d } \n", record->fileName, record->occurrences );
        else
            fprintf(fp, "\t {\"%s\" : %d } \n", record->fileName, record->occurrences );


        curr = curr->next;

    } while(curr != NULL);


}

Record *getRightMostRecord(Record *record){

    while(record->right != NULL)
        record = record->right;

    return record;
}

/*
{  "." :[  
         {"test/testFile3.c" : 1 } 
]}, 
{    "I" :[  
         {"test/testFile3.c" : 1 } 
]}, 
{    "and" :[  
         {"test/testFile3.c" : 1 } 
]}, 
{    "every" :[  
         {"test/testFile3.c" : 1 } 
]}, 
{    "everyday" :[  
         {"test/testFile3.c" : 1 } 
]}, 
{    "night" :[  
         {"test/testFile3.c" : 1 } 
]}, 
{    "run" :[  
         {"test/testFile3.c" : 1 } 
]}, 
{    "sleep" :[  
         {"test/testFile3.c" : 1 } 
]} 

*/
void writeToFile(Record *record, FILE *fp, Record *righMostRecord)
{
        if(record==NULL)
        {
                return;
        }
        writeToFile(record->left, fp, righMostRecord);


        fprintf(fp, "\t {\"%s\" :[  \n \t", record->token);
        /* Print All filenames and occurrences here */
        printFilesAndOccurrencesToFile(record, fp);

        if (righMostRecord == record)
            fprintf(fp, "]} \n");
        else
            fprintf(fp, "]}, \n");

        writeToFile(record->right, fp, righMostRecord);
}

void PrintPreorder(Record *record)
{
        if(record==NULL)
        {
                return;
        }
        printf("%s ",record->token);
        PrintPreorder(record->left);
        PrintPreorder(record->right);
}

void PrintPostorder(Record *record)
{
        if(record==NULL)
        {
                return;
        }
        PrintPostorder(record->left);
        PrintPostorder(record->right);
        printf("%s",record->token);
}

/*
int main()
{
        Record *root = NULL;
        root = insert(root, 5);
        root = insert(root, -1);
        root = insert(root, 3);
        root = insert(root, -14);
        root = insert(root, 8);
        root = insert(root, 10);
        root = insert(root, 9);
        root = insert(root, 6);
        PrintInorder(root);
        printf("\n");
        root = delete(root,5);
        root = delete(root,-1);
        PrintInorder(root);
        printf("\n");
        Record * temp;
        temp = findMin(root);
        printf("Minimum element is %d\n",temp->token);
        temp = findMax(root);
        printf("Maximum element is %d\n",temp->token);
        temp = find(root,8);
        if(temp==NULL)
        {
                printf("Element 8 not found\n");
        }
        else
        {
                printf("Element 8 Found\n");
        }
        temp = find(root,2);
        if(temp==NULL)
        {
                printf("Element 2 not found\n");
        }
        else
        {
                printf("Element 6 Found\n");
        }
}
*/