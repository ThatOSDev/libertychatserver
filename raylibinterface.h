
#ifndef GAME_H
#define GAME_H

void that_updateRaylibMouse(void);
int  that_getMousePosX(void);
int  that_getMousePosY(void);
int  that_checkMousePos(int MinXPos, int MinYPos, int MaxXPos, int MaxYPos);
void that_setRaylibWindowSize(int width, int height);
void that_createRaylibWindow(void);
void that_changeRaylibClearColor(int red, int green, int blue, int alpha);
void that_updateRaylibScreenSize(void);
void that_updateRaylibState(void);
int  that_getRaylibGUIState(void);
void that_setRaylibGUIState(int state);
void that_updateRaylibLoop(void);
int  that_isRaylibClosed(void);
void that_closeRaylibWindow(void);
int  that_getScreenWidth(void);
int  that_getScreenHeight(void);

#endif // GAME_H
