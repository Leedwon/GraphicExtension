# GraphicProject

The goal of this project was to create new extension for graphic files.

# .OX

Is the created extension
It contains of:
- header which has ox signature, file size, offset to pixels array
- picture header which has width, height, palette of colours (dedicated palette, grey scale, imposed palette, black white dithering, dedicated dithering), coding type (rle or byte run more info on that below).
- color table (optional) contains palette when needed i.e for grey scale there is no palette.
- pixels table each pixel is stored on 8bits.

# Coding type

To store data in .OX we use compression it's either Byterun or Rle depending which one would take smaller ammount of space.

Example of how those algorithm works on simple char sequence:

AAAABBBBCCCCCCABCDCBCCACDAAABDCBBBBACACACCCCCAAAA - pre compressed

Byterun:

-3A -3B -5C 10ABCDCBCCACD -2A 2BDC -3B 4ACACA -4C -3A

RLE:

4A 4B 6C 011ABCDCBCCACD0 3A 03BDC0 05ACACA0 5C 4A

App provides converter from .bmp to .OX and conversly. 

SDL2 library was used to create app.
