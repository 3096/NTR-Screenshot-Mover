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

bool mvSSFile(char * fileDir, char * targetDir, char * resultStr) {
    if(rename(fileDir, targetDir) == 0) {
        sprintf(resultStr, "Moved %s to\n %s\n", fileDir, targetDir);
        return true;
    }
    else {
        sprintf(resultStr, "Failed to move %s\n", fileDir);
        return false;
    }
}

// move screenshot files
void startMvSS() {
    const char *TOP_PREFIX = "top";
    const char *TOP_RIGHT_PREFIX = "top_right";
    const char *BOT_PREFIX = "bot";
    const char *SS_FORMAT = ".bmp";

    const char *SOURCE_DIR = "sdmc:/";
    const char *TARGET_DIR = "sdmc:/Screenshots/";
    const char *TARGET_PREFIX = "Screenshot";

    // check if Screenshots dir exists
    struct stat st = {0};
    if (stat(TARGET_DIR, &st) == -1) {
        mkdir(TARGET_DIR, 0700);
    }

    DIR           *sourceDir;
    struct dirent *sourceDirEnt;
    sourceDir = opendir(SOURCE_DIR);

    if (sourceDir)
    {
        while ((sourceDirEnt = readdir(sourceDir)) != NULL)
        {
            char cFileName[19]; 
            strncpy(cFileName, sourceDirEnt->d_name, 18);
            cFileName[18] = '\0';
            char *cFileFormat = strrchr(cFileName, '.');

            if(cFileFormat && strcmp(cFileFormat, SS_FORMAT) == 0) {

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

                char cFilePath[25];
                sprintf(cFilePath, "%s%s", SOURCE_DIR, cFileName);
                // eg "sdmc:/top_right_0000.bmp"

                char cFileTimeStr[16];
                getFileTimeStr(cFilePath, cFileTimeStr);

                char cTargetDir[66];
                sprintf(cTargetDir, 
                    "%s"        "%s_"           "%s_"           "%s_"        "%s"        "%s", 
                    TARGET_DIR, TARGET_PREFIX,  cFileTimeStr,   cFilePrefix, cFileIndex, SS_FORMAT);
                // eg "sdmc:/Screenshots/Screenshot_20161127-143154_top_right_0000.bmp"

                char resultStr[0x100];
                mvSSFile(cFilePath, cTargetDir, resultStr);
                printf("%s\n", resultStr);
            }
        }

        closedir(sourceDir);
    }
}
