#include <string.h>
#include <stdio.h>

#define NTR_DIR     "sdmc:/"
#define LUMA_DIR    "sdmc:/luma/screenshots"
#define MRG_DIR     "sdmc:/screenshots-merged"

#define DEFAULT_TARGET_DIR = "sdmc:/Screenshots/";

static const char * const DEFAULT_SOURCE_DIR_LIST[] = {
    NTR_DIR,
    LUMA_DIR
    //MRG_DIR
};

void resetConfig();
