#include <string.h>
#include <stdio.h>

#include <dirent.h>

#include <3ds.h>

void getFileTimeStr(char * filePath, char * timeStr);
bool mvSSFile(char * fileIndex, char * timeStr, const char * filePrefix, char * resultStr);
void startMvSS();
