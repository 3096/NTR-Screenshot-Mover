# NTR-Screenshot-Mover
A simple 3DS homebrew app to move NTR Screenshots out of SD root directory.

## Why?

NTR uses a naming convention of "top/bot_<INDEX>.bmp", which means that everytime NTR boots, it needs to scan the entire directory of screenshots in order to figure out the index. This process, plus 3DS's slow file system, can take up to **minutes** when there are a lot of screenshot. Plus in general, having that many files in the SD root directory is not a good idea.

## Dude your code sucks!

I am still a beginner at programming. Please create an [issue](https://github.com/3096/NTR-Screenshot-Mover/issues/new) if you see something bad and want to help me learn and improve!

## Current Implemented Features:

- Move NTR screenshot files to `/Screenshots`
- Detect file's last modified time for naming

## Known issue:
- The moving process is still very slow if the target directory is crowded.
    - Looks like 3DS file system just doesn't work well that way. Will need to create more directories.

## To do list:

- Figure out how to build .cia
- Optionally, launch BootNTRSelector when done
- Custom paths

## Possible features, no guarantee:

- Combine top and bottom screen
- Convert to png format
- Gallery style preview

## Building:

Make sure you have:

- devkitPro with devkitARM
- libctru

`make`
