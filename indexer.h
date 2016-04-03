#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <fts.h>
#include "tokenizer.h"

int compareCharArrayToString(char *name, char array[]);
char *getNameOfFileOrDirectory(char *filePath);
void directoryHandler(char *name);
void fileHandler(char *name);
void initGlobals(char *token, char *fileName, int fileSize);