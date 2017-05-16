# NTR-Screenshot-Mover
A simple 3DS homebrew app to move NTR Screenshots out of SD root directory.

## Why?

NTR uses a naming convention of "top/bot_<INDEX>.bmp", which means that everytime NTR boots, it needs to scan the entire directory of screenshots in order to figure out the index. This process, plus 3DS's slow file system, can take up to **minutes** when there are a lot of screenshot. Plus in general, having that many files in the SD root directory is not a good idea.

## To do list:

- Actually move something (WIP)
- Detect time of when the file is created for naming (WIP)
- Optionally, launch BootNTRSelector when done

## Possible features, no guarantee:

- Combine top and bottom screen
- Convert to png format (I think I saw a png lib, not sure if it can do this tho)
- Gallery style preview

## Building:

Make sure you have:

- devkitPro with devkitARM

`make`
