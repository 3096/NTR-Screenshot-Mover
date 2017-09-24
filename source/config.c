#include "config.h"

void resetConfig() {
    FILE *configFile = fopen(CONFIG_FILE_PATH, "w+");

    fprintf(configFile, "%s\n", SOURCE_DIR_TAG);
    for(int i = 0; 
        i < sizeof(DEFAULT_SOURCE_DIR_LIST)/sizeof(DEFAULT_SOURCE_DIR_LIST[0]);
        i++)
            fprintf(configFile, "%s\n", DEFAULT_SOURCE_DIR_LIST[i]);

    fprintf(configFile, "%s\n", TARGET_DIR_TAG);
    fprintf(configFile, "%s\n", DEFAULT_TARGET_DIR);

    fclose(configFile);
}

void configInit() {
    struct stat st = {0};

    if (stat(CONFIG_FILE_DIR, &st) == -1)
        mkdir(CONFIG_FILE_DIR, 0700);

    //if (stat(TARGET DIRECTORY, &st) == -1)
    //    mkdir(TARGET DIRECTORY, 0700);
}
