#include <string.h>
#include <dirent.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <3ds.h>

void getFileCreationTime(char *filePath)
{
    struct stat attrib;
    stat(filePath, &attrib);
    char date[10];
    strftime(date, 10, "%d-%m-%y", gmtime(&(attrib.st_mtime)));
    printf("The file %s was last modified at %s\n", filePath, date);
    date[0] = 0;
}

void mvFiles() {
	const char TOP_SS_NAME_PREFIX[5] = "top_";
	const char BOT_SS_NAME_PREFIX[5] = "bot_";
	const char SS_FORMAT[5] = ".bmp";

	DIR           *d;
	struct dirent *dir;
	d = opendir("/");

	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			char cFilePrefix[5];
			strncpy(cFilePrefix, dir->d_name, 4);
			cFilePrefix[4] = '\0';
			char cFileFormat[5];
			memcpy(cFileFormat, &dir->d_name[8], 4);
			cFileFormat[4] = '\0';

			if (strcmp(cFileFormat, SS_FORMAT) == 0) {
				
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

		// Your code goes here

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
