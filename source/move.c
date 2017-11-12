#include "move.h"

// get file modification time in a formatted string
void getFileTimeStr(char * filePath, char * timeStr) {
    u64 mtime;
    sdmc_getmtime(filePath, &mtime);
    time_t ft = mtime;
    struct tm *ftm = gmtime(&ft);
    strftime(timeStr, 16, "%Y%m%d-%H%M%S", ftm);
    return;
}

const char *SS_FORMAT = ".bmp";
const char *SOURCE_DIR = "sdmc:/";
const char *TARGET_DIR = "sdmc:/Screenshots/";
const char *TARGET_PREFIX = "Screenshot";

bool mvSSFile(char * fileIndex, char * timeStr, 
    const char * filePrefix, char * resultStr) {
    char filePath[0x100];
    sprintf(filePath, "%s%s_%s%s", 
        SOURCE_DIR, filePrefix, fileIndex, SS_FORMAT);
    // eg "sdmc:/top_right_0000.bmp"
    
    if (access(filePath, F_OK) == -1) {
        sprintf(resultStr, "%s does not exist\n", filePath);
        return false;
    }

    char targetPath[0x100];
    sprintf(targetPath, 
        "%s"        "%s_"          "%s_"    "%s_"       "%s"        "%s", 
        TARGET_DIR, TARGET_PREFIX, timeStr, filePrefix, fileIndex,  SS_FORMAT);
    // eg "sdmc:/Screenshots/Screenshot_20161127-143154_top_right_0000.bmp"

    if (rename(filePath, targetPath) == 0) {
        sprintf(resultStr, "Moved %s to\n %s\n", filePath, targetPath);
        return true;
    }
    else {
        sprintf(resultStr, "Failed to move %s\n", filePath);
        return false;
    }
}

// move screenshot files
void startMvSS() {
    const char *TOP_PREFIX = "top";
    const char *TOP_RIGHT_PREFIX = "top_right";
    const char *BOT_PREFIX = "bot";

    struct stat st = {0};
    if (stat(TARGET_DIR, &st) == -1) {
        mkdir(TARGET_DIR, 0700);
    }

    DIR           *sourceDir;
    struct dirent *sourceDirEnt;
    sourceDir = opendir(SOURCE_DIR);

    if (sourceDir) {
        while ((sourceDirEnt = readdir(sourceDir)) != NULL) {
            char cFileName[19]; 
            strncpy(cFileName, sourceDirEnt->d_name, 18);
            cFileName[18] = '\0';
            char *cFileFormat = strrchr(cFileName, '.');

            if(cFileFormat && strcmp(cFileFormat, SS_FORMAT) == 0) {
                char cFilePath[0x100];
                sprintf(cFilePath, "%s%s", SOURCE_DIR, cFileName);
                // eg "sdmc:/top_right_0000.bmp"

                if (access(cFilePath, F_OK) == -1)
                    continue;

                char cFilePrefix[10], cFileIndex[5];
                int cIndexPos = 0;
                for (int i = 0; i < strlen(cFileName); i++){
                    if (cFileName[i] >= 48 && cFileName[i] <= 57){
                        cIndexPos = i;
                        break;
                    }
                }
                if (cIndexPos) {
                    strncpy(cFilePrefix, cFileName, cIndexPos-1);
                    cFilePrefix[cIndexPos-1] = '\0';
                    memcpy(cFileIndex, &cFileName[cIndexPos], 4);
                    cFileIndex[4] = '\0';
                } else
                    continue;
                
                if (strcmp(cFilePrefix, TOP_PREFIX) != 0 &&
                    strcmp(cFilePrefix, TOP_RIGHT_PREFIX) != 0 &&
                    strcmp(cFilePrefix, BOT_PREFIX) != 0)
                    continue;

                char cSSTimeStr[16];
                getFileTimeStr(cFilePath, cSSTimeStr);

                char resultStr[0x100];
                mvSSFile(cFileIndex, cSSTimeStr, TOP_PREFIX, resultStr);
                printf("%s\n", resultStr);
                mvSSFile(cFileIndex, cSSTimeStr, TOP_RIGHT_PREFIX, resultStr);
                printf("%s\n", resultStr);
                mvSSFile(cFileIndex, cSSTimeStr, BOT_PREFIX, resultStr);
                printf("%s\n", resultStr);
            }
        }

        closedir(sourceDir);
    }
}
