#include <string.h>
#include <stdio.h>

#include <dirent.h>

#include <3ds.h>

// get file modification time in a formatted string
void getFileTimeStr(char * filePath, char * timeStr) {
    u64 mtime;
    sdmc_getmtime(filePath, &mtime);
    time_t ft = mtime;
    struct tm *ftm = gmtime(&ft);
    strftime(timeStr, 16, "%Y%m%d-%H%M%S", ftm);
    return;
}

// move screenshot files
void mvSSFiles() {
    const char *TOP_PREFIX = "top";
    const char *TOP_RIGHT_PREFIX = "top_right";
    const char *BOT_PREFIX = "bot";
    const char *SS_FORMAT = ".bmp";

    const char *TARGET_DIR = "sdmc:/Screenshots/";
    const char *TARGET_PREFIX = "Screenshot_";

    // check if Screenshots dir exists
    struct stat st = {0};
    if (stat(TARGET_DIR, &st) == -1) {
        mkdir(TARGET_DIR, 0700);
    }

    DIR           *rootDir;
    struct dirent *rootDirEnt;
    rootDir = opendir("sdmc:/");

    if (rootDir)
    {
        while ((rootDirEnt = readdir(rootDir)) != NULL)
        {
            char *cFileFormat = strrchr(rootDirEnt->d_name, '.');

            if(cFileFormat && strcmp(cFileFormat, SS_FORMAT) == 0) {

                char cFilePrefix[10], cFileIndex[5];
                int cIndexPos = 0;
                for (int i = 0; i < strlen(rootDirEnt->d_name); i++){
                    if (rootDirEnt->d_name[i] >= 48 && rootDirEnt->d_name[i] <= 57){
                        cIndexPos = i;
                        break;
                    }
                }
                if (cIndexPos) {
                    strncpy(cFilePrefix, rootDirEnt->d_name, cIndexPos-1);
                    cFilePrefix[cIndexPos-1] = '\0';
                    memcpy(cFileIndex, &rootDirEnt->d_name[cIndexPos], 4);
                    cFileIndex[4] = '\0';
                } else
                    continue;
                
                if (strcmp(cFilePrefix, TOP_PREFIX) != 0 &&
                    strcmp(cFilePrefix, TOP_RIGHT_PREFIX) != 0 &&
                    strcmp(cFilePrefix, BOT_PREFIX) != 0)
                    continue;

                char cFilePath[25];
                strcpy(cFilePath, "sdmc:/");
                strcat(cFilePath, rootDirEnt->d_name);
                // eg "sdmc:/top_right_0000.bmp"

                char cFileTimeStr[16];
                getFileTimeStr(cFilePath, cFileTimeStr);

                char cTargetDir[66];
                strcpy(cTargetDir, TARGET_DIR);
                strcat(cTargetDir, TARGET_PREFIX);
                strcat(cTargetDir, cFileTimeStr);
                strcat(cTargetDir, "_");
                strcat(cTargetDir, cFilePrefix);
                strcat(cTargetDir, "_");
                strcat(cTargetDir, cFileIndex);
                strcat(cTargetDir, SS_FORMAT);
                // eg "sdmc:/Screenshots/Screenshot_20161127-143154_top_right_0000.bmp"

                int endNum = 1, maxAttempt = 10;
                while(rename(cFilePath, cTargetDir) != 0 && endNum < maxAttempt){
                    cTargetDir[strlen(cTargetDir)-strlen(SS_FORMAT)] = '\0';
                    strcat(cTargetDir, "_X");
                    cTargetDir[strlen(cTargetDir)-1] = 48 + endNum;
                    strcat(cTargetDir, SS_FORMAT);
                    
                    endNum++;
                }

                if(endNum < maxAttempt)
                    printf("Moved %s to\n %s\n", cFilePath, cTargetDir);
                else
                        printf("Failed to move %s\n", cFilePath);
            }
        }

        closedir(rootDir);
    }
}

int main(int argc, char **argv) {

    gfxInitDefault();
    consoleInit(GFX_TOP, NULL);

    printf("Press A to move NTR Screenshots\n");
    printf("Press START to quit\n\n");

    // Main loop
    while (aptMainLoop()) {

        gspWaitForVBlank();
        hidScanInput();

        u32 kDown = hidKeysDown();
        if (kDown & KEY_START)
            break; // break in order to return to hbmenu

        if (kDown & KEY_A)
            mvSSFiles();

        // Flush and swap framebuffers
        gfxFlushBuffers();
        gfxSwapBuffers();
    }

    gfxExit();
    return 0;
}
