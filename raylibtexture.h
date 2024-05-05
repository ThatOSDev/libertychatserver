
#ifndef RAYLIB_TEXTURE_H
#define RAYLIB_TEXTURE_H

#include "headers.h"

void drawMinimizeIcon(void);
void drawMaxIcon(void);
void drawMaximizedIcon(void);
void drawExitIcon(void);

Texture2D that_createRaylibMainTexture();
Texture2D that_createRaylibGradientTexture(int w, int h, int direction, Color c1, Color c2);
void      that_initResources(void);
void      that_drawLiveText(void);
void      that_clearResources(void);

#endif // RAYLIB_TEXTURE_H
