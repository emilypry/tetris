# tetris
A mock Tetris game for Arduino Pro Micro and an OLED SSD1331! Really works.

There is only one bug that I know of: if you try to rotate one of the toys too close to the sides of the container,
the toy will actually break out of the container and continue to fall, erasing everything in its path. There was not 
enough memory on the Arduino for me to tack on a fix for this; fixing it would require making the entire program
more efficient (a project for another day...).
