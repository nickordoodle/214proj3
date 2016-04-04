#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Record_ Record;
struct Record_ {

	char *fileName;
	char *token;
	int occurrences;
	Record *next;
	Record *prev;
	Record *left;
    Record *right;
};

Record* findMin(Record *record);
Record* findMax(Record *record);
void swapRecords(Record *prev, Record *curr);
void shiftRecord(Record *recordToShift);
Record * delete(Record *record, char *token);
Record * find(Record *record, char *token);
Record * insert(Record *record, char *token, char *fileName);
Record * createNewRecord(char *fileName, char *token, int occurrences, Record *next,
	Record *prev,
	Record *left,
    Record *right);
Record *getRightMostRecord(Record *record);
void writeToFile(Record *record, FILE *fp, Record *righMostRecord);
void PrintInorder(Record *record);
void PrintPreorder(Record *record);
void PrintPostorder(Record *record);