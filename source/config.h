#include <string.h>
#include <stdio.h>

#include <dirent.h>

#define CONFIG_FILE_PATH    "sdmc:/3ds/NTR-Screenshot-Mover/config"
#define CONFIG_FILE_DIR     "sdmc:/3ds/NTR-Screenshot-Mover"    

#define NTR_DIR             "sdmc:/"
#define LUMA_DIR            "sdmc:/luma/screenshots"
#define MRG_DIR             "sdmc:/screenshots-merged"

#define DEFAULT_TARGET_DIR  "sdmc:/Screenshots/"

#define SOURCE_DIR_TAG      "SOURCE DIRECTORY:"
#define TARGET_DIR_TAG      "TARGET DIRECTORY:"

static const char * const DEFAULT_SOURCE_DIR_LIST[] = {
    NTR_DIR,
    LUMA_DIR
    //MRG_DIR
};

void resetConfig();
void configInit();
