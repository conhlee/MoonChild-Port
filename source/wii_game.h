#ifndef _GAME_H
#define _GAME_H

#include <cstdint>
class MoviePlayer;

void gameTick(uint8_t *pixels, int width, int height, int pitch);
void keyUp(int key);
void keyDown(int key);
void initMoonChild(unsigned char *pixelBuffer, int width, int height, MoviePlayer *moviePlayer);
void resetProgress();
void enableCheat();

#endif