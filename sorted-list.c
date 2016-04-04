#include <stdlib.h>
#include <stdio.h>
#include "sorted-list.h"

SortedListPtr *list;

/* Allocate memory, set data fields to appropriate values*/
void initializeSL(){

	list = (SortedListPtr) malloc(sizeof(struct SortedList));

	if(SLPtr == NULL) {
		return NULL;
	}

	list->head = NULL;
	list->compare = cf;
	list->destroy = df;
}

/*current file will be the most recent so you only need to check there since each file is only opened once*/
void recordRecord(Node node, char *filename){
	if(strcmp(node->head->filename, filename){
		node->head->occurrences++;
	}else{
		Record *newRecord = malloc(sizeof(Record));
		newRecord-> filename= filename;	
		occurences = 1;
		newRecord-> prev = NULL;
		newRecord-> next = node-> head;
		node-> head-> prev = NewRecord;
		node-> head = newToken;
	}
}



Node *createNode(Node *parent, char *token, char *filename){
	
	Record *record = malloc(sizeof(Record));
	Node *newNode = malloc(sizeof(Node));
	
	record->filename = filename;
	record->occurance = 1;
	record->next = NULL;
	record->prev = NULL;
	
	newNode->token = token;
    	newNode->head = record;
	newNode->parent = parent;		
	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;
}
/*What is the purpose of parent here?*/
int insertToken(CompareFuncT cf, char *token, char *filename){
	
	Node node = list->head;
	void *nodeData = node->token;
	int compareVal = cf(token, nodeData);
	

    	int returnVal = 0;


    /* Insert into left subtree */
    if(compareVal < 0){
    	if(node -> left  == NULL){
                node -> left = createNode(node, token, filename);
                returnVal = 1;
        } else{
            returnVal = insertNode(cf, node->left, nodeParent, data);

        }
	
    } 
    /* Insert into right subtree */
    else if (compareVal > 0){   
    	if(node -> right == NULL){
                node -> right = createNode(node, token, filename);
                returnVal = 1;
        } else{
           returnVal = insertNode(cf, node->right, nodeParent, data);
 
        }
    	
    } 
    /* Word has already previously occurred and records need to be updated */
    else {
    	recordRecord(Node,filename)
    	returnVal = 0;
    }
   
    return returnVal;
}



/*   Checks for null BST and then send it to inserttoken to update the token information*/
   
int SLInsert(char* token, char* filename){

	int returnVal = 0;

	/* Empty tree, make new one */
	if(list->head == NULL){
		initializeSL();
		list->head = createNode(NULL, token, filename);
		return 1;
	} 

	returnVal = insertToken(list->compare, list->head, token, filename);
	

	return returnVal;
}

/*this will be turned into how we get the information out of the BST not done yet*/
void printTree(Node *node){/*created for testing purposes only*/
        if(node->left != NULL)
                printTree(node->left);
        if(node -> right != NULL)
                 printTree(node->right);
        return;
}

void destroyTree(Node *node){

	if (node == NULL) return;
 
    /* first delete both subtrees */
    destroyTree(node->left);
    destroyTree(node->right);
   
    /* then delete the node */
    free(node);
}

