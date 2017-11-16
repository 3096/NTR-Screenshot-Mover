# ![# NTR Screenshot Mover](https://github.com/3096/NTR-Screenshot-Mover/raw/master/meta/icon.png) NTR Screenshot Mover

A simple 3DS homebrew app to move NTR Screenshots out of SD root directory.

## NOTICE: This project has been put on hold indefinitely.

Practical testing has shown a signifigant slow down to ALL sdmc file operations caused by this program when a large amount of screenshots are moved. It likely is a result of FAT32 file system and/or the way 3DS handles it. (I'm not too familiar down to the technical stuffs.) 

Also, the circumstances surrounding NTR CFW has changed: it's now open source! I have created [a forked version](https://github.com/3096/NTR) that saves screenshots directly to a directory and naming it with timestamps. This is one step towards the better solution I always wanted anyway.

## Why?

NTR uses a naming convention of "top/bot_<INDEX>.bmp", which means that everytime NTR boots, it needs to scan the entire directory of screenshots in order to figure out the index. This process, plus 3DS's slow file system, can take up to **minutes** when there are a lot of screenshot. Plus in general, having that many files in the SD root directory is not a good idea.

## Dude your code sucks!

I am still a beginner at programming. Please create an [issue](https://github.com/3096/NTR-Screenshot-Mover/issues/new) if you see something bad and want to help me learn and improve!

---
## Current Implemented Features:

- Move NTR screenshot files to `/Screenshots`
- Detect file's last modified time for naming

## Known issue:
- The moving process is still very slow if the target directory is crowded.
    - Looks like 3DS file system just doesn't work well that way. Will need to create more directories.

## To do list:

- Figure out how to build .cia
- Optionally, launch BootNTRSelector when done
- Custom paths (also luma screenshot support)
- Combine top and bottom screen
- Convert to png format
- Better UI and scrollable
    - Display result (how many files were moved, etc.)

---
## Building:

Make sure you have:

- devkitPro with devkitARM
- libctru

`make`

---
## Credits:

- Hardworking people who created the libraries used here
- Helpful people on [Nintendo Homebrew Discord](https://discord.gg/C29hYvh) #Dev channel
