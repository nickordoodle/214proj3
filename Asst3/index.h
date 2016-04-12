#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <fts.h>

int compareCharArrayToString(char *name, char array[]);
char *getNameOfFileOrDirectory(char *filePath);
void directoryHandler(const char *name);
void fileHandler(char *name);
