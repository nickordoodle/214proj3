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

typedef struct Record_ Record;
struct Record_ {

	char *fileName;
	int occurrences;
	Record *next;
	Record *prev;
};

/* combined token with node
Token creatToken(char * token){
	Token *newToken = malloc(sizeof(Token));
	newToken-> token= token;
	return Token;
}*/

/*current file will be the most recent so you only need to check there since each file is only opened once*/
void recordRecord(Node node, char *filename){
	if(strcmp(node->head->filename, filename){
		head->occurrences++;
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
/* Do null check on list, if not null then iterate
   through the list */
void SLDestroy(SortedListPtr list){

	destroyTree(list->head);
	
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
int insertToken(CompareFuncT cf, Node *node, Node *parent, char *token, char *filename){

	Node *nodeParent = parent;
	void *nodeData = node->data;
	int compareVal = cf(data, nodeData);

    int returnVal = 0;

    /* Empty tree, build here and successful insertion*/
    if(node == NULL){ /*don't think this is needed anymore*/
        node = createNode(node, token, filename);
        return 1;
    }

    /* Insert into left subtree */
    if(compareVal < 0){
    	/*nodeParent = node;*/
    	if(node -> left  == NULL){
                node -> left = createNode(node, token, filename);
                returnVal = 1;
        } else{
            returnVal = insertNode(cf, node->left, nodeParent, data);

        }
	
    } 
    /* Insert into right subtree */
    else if (compareVal > 0){   
    	/*nodeParent = node;   */
    	if(node -> right == NULL){
                node -> right = createNode(node, token, filename);
                returnVal = 1;
        } else{
           returnVal = insertNode(cf, node->right, nodeParent, data);
 
        }
    	
    } 
    /* Word has already previously occurred  */
    else {
    	recordRecord(Node,filename)
    	returnVal = 0;
    }
    

    /* CAUSING UNWANTED BEHAVIOR BECAUSE OF RECURSION CALLS */
    return returnVal;
}

Node *minValueNode(Node* node)
{
    Node* current = node;
 
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;
 
    return current;
}



/* Uses the compare functions to determine where
   to place the data 

   MEAT OF THE PROGRAM.  Need to determine how to
   sort the list while inserting new items.  We
   could just iterate through each time but that is
   inefficient.  Problem is that sorting algorithms
   are harder to do with linked lists. So either
   regular iteration or change implementation to use
   linked lists. */
int SLInsert(char* token, char* filename){

	int returnVal = 0;

	/* Empty tree, make new one */
	if(list->head == NULL){
		initializeSL();
		list->head = createNode(NULL, token, filename);
		return 1;
	} 

	returnVal = insertToken(list->compare, list->head, list->head, token, filename);
	

	return returnVal;
}



