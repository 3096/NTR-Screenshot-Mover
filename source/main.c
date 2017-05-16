#include <string.h>
#include <dirent.h>
#include <stdio.h>

#include <3ds.h>

// get file modification time in a formated string
char * getFileTime(char filePath[]) {
	u64 mtime;
	sdmc_getmtime(filePath, &mtime);
	// function not finished, needs format string
	return NULL;
}

// function name not final
void mvFiles() {
	const char *TOP_SS_NAME_PREFIX = "top_";
	const char *BOT_SS_NAME_PREFIX = "bot_";
	const char *SS_FORMAT = ".bmp";

	DIR           *d;
	struct dirent *dir;
	d = opendir("/");

	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			char *cFileFormat = strrchr(dir->d_name, '.');
			if(cFileFormat && strcmp(cFileFormat, SS_FORMAT) == 0) {

				char cFilePrefix[5];
				strncpy(cFilePrefix, dir->d_name, 4);
				cFilePrefix[4] = '\0';
				
				printf("%s\n", cFilePrefix);

				char cFilePath[strlen(dir->d_name) + 1];
				strcpy(cFilePath, "/");
				strcat(cFilePath, dir->d_name);

				// Code below is unfinied
				getFileTime(cFilePath);

				if (strcmp(cFilePrefix, TOP_SS_NAME_PREFIX) == 0) {

				} else if (strcmp(cFilePrefix, BOT_SS_NAME_PREFIX) == 0) {

				}
			}
		}

		closedir(d);
	}
}

int main(int argc, char **argv) {

	gfxInitDefault();
	consoleInit(GFX_TOP, NULL);

	printf("Press A to fail\n");
	printf("Press START to rage quit\n");

	// Main loop
	while (aptMainLoop()) {

		gspWaitForVBlank();
		hidScanInput();

		u32 kDown = hidKeysDown();
		if (kDown & KEY_START)
			break; // break in order to return to hbmenu

		if (kDown & KEY_A)
			mvFiles();

		// Flush and swap framebuffers
		gfxFlushBuffers();
		gfxSwapBuffers();
	}

	gfxExit();
	return 0;
}
