# NTR-Screenshot-Mover
A simple 3DS homebrew app to move NTR Screenshots out of SD root directory.

## Why?

NTR uses a naming convention of "top/bot_<INDEX>.bmp", which means that everytime NTR boots, it needs to scan the entire directory of screenshots in order to figure out the index. This process, plus 3DS's slow file system, can take up to **minutes** when there are a lot of screenshot. Plus in general, having that many files in the SD root directory is not a good idea.

## Dude your code sucks!

I have never actually learned C, and my knowledge about how memories or pointers work is very limited. Please create an [issue](https://github.com/3096/NTR-Screenshot-Mover/issues/new) if you see something wrong and want to help me improve!

## Current Implemented Features:

- Move NTR screenshot files to `/Screenshots`
- Detect file's last modified time for naming

## To do list:

- Figure out how to build .cia
- Optionally, launch BootNTRSelector when done
- Custom paths

## Possible features, no guarantee:

- Combine top and bottom screen
- Convert to png format (I think I saw a png lib, not sure if it can do this tho)
- Gallery style preview

## Building:

Make sure you have:

- devkitPro with devkitARM
- libctru

`make`
