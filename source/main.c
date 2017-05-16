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
	const char *TOP_PREFIX = "top_";
	const char *BOT_PREFIX = "bot_";
	const char *SS_FORMAT = ".bmp";

	const char *TARGET_DIR = "/Screenshots/";
	const char *TARGET_PREFIX = "Screenshot_";
	const char *TOP_TARGET_SUFFIX = "-top";
	const char *BOT_TARGET_SUFFIX = "-bot";

	// check if Screenshots dir exists
	struct stat st = {0};
	if (stat(TARGET_DIR, &st) == -1) {
	    mkdir(TARGET_DIR, 0700);
	}

	DIR           *rootDir;
	struct dirent *rootDirEnt;
	rootDir = opendir("/");

	if (rootDir)
	{
		while ((rootDirEnt = readdir(rootDir)) != NULL)
		{
			char *cFileFormat = strrchr(rootDirEnt->d_name, '.');
			if(cFileFormat && strcmp(cFileFormat, SS_FORMAT) == 0) {

				char cFilePrefix[5];
				strncpy(cFilePrefix, rootDirEnt->d_name, 4);
				cFilePrefix[4] = '\0';

				char cFilePath[14];
				strcpy(cFilePath, "/");
				strcat(cFilePath, rootDirEnt->d_name);

				char cFileTimeStr[16];
				getFileTimeStr(cFilePath, cFileTimeStr);

				char cTargetDir[49];
				strcpy(cTargetDir, TARGET_DIR);
				strcat(cTargetDir, TARGET_PREFIX);
				strcat(cTargetDir, cFileTimeStr);
				if (strcmp(cFilePrefix, TOP_PREFIX) == 0) {
					strcat(cTargetDir, TOP_TARGET_SUFFIX);
				} else if (strcmp(cFilePrefix, BOT_PREFIX) == 0) {
					strcat(cTargetDir, BOT_TARGET_SUFFIX);
				} else {
					break;
				}
				strcat(cTargetDir, SS_FORMAT);

				if(rename(cFilePath, cTargetDir) == 0)
					printf("Moved %s to\n %s\n", cFilePath, cTargetDir);
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
