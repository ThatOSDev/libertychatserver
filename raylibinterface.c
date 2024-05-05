
#include "win32-extra.h"
#include "settings.h"
#include "headers.h"
#include "raylibtexture.h"
#include "stringmanager.h"

enum
{
    MAIN_NONE = 0,
    MAIN_MINIMIZE,
    MAIN_MAXIMIZE,
    MAIN_EXIT,
    MAIN_RESIZE,
    MAIN_MOVE
} RAYLIB_GUI;

int raylibScreenWidth       = 0;
int raylibScreenHeight      = 0;
int raylibMinScreenWidth    = 0;
int raylibMinScreenHeight   = 0;

int raylibMonitorWidth      = 0;
int raylibMonitorHeight     = 0;
int raylibWindowPosX        = 0;
int raylibWindowPosY        = 0;
int tempResultX             = 0;
int tempResultY             = 0;
int raylibMouseX            = 0;
int raylibMouseY            = 0;

int raylibClearRed          = 0;
int raylibClearGreen        = 0;
int raylibClearBlue         = 0;
int raylibClearAlpha        = 0;

int rayMouseButton1Pressed  = 0;
int rayMouseButton2Pressed  = 0;
int rayMouseButton3Pressed  = 0;
int rayMouseButton1Released = 0;
int rayMouseButton2Released = 0;
int rayMouseButton3Released = 0;
int rayGUIState             = MAIN_NONE;

int quitProgram             = 0;
int isMaxedToggle           = 0;
int maxTempToggleWidth      = 0;
int maxTempToggleHeight     = 0;
int resizedTrigger          = 0;

Texture2D mainTexture;

void that_updateRaylibMouse()
{
    raylibMouseX = GetMouseX();
    raylibMouseY = GetMouseY();
    rayMouseButton1Pressed = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
    rayMouseButton2Pressed = IsMouseButtonDown(MOUSE_BUTTON_RIGHT);
    rayMouseButton3Pressed = IsMouseButtonDown(MOUSE_BUTTON_MIDDLE);

    rayMouseButton1Released = IsMouseButtonReleased(MOUSE_BUTTON_LEFT);
    rayMouseButton2Released = IsMouseButtonReleased(MOUSE_BUTTON_RIGHT);
    rayMouseButton3Released = IsMouseButtonReleased(MOUSE_BUTTON_MIDDLE);
}

int that_getMousePosX()
{
    return raylibMouseX;
}

int that_getMousePosY()
{
    return raylibMouseY;
}

int that_checkMousePos(int MinXPos, int MinYPos, int MaxXPos, int MaxYPos)
{
    if((raylibMouseX >= MinXPos) && (raylibMouseX < MaxXPos)
       && (raylibMouseY >= MinYPos) && (raylibMouseY < MaxYPos))
    {
        return 1;
    } else {
        return 0;
    }
}

void that_quitProgram()
{
    quitProgram = 1;
}

void that_setRaylibWindowSize(int width, int height)
{
    raylibScreenWidth  = width;
    raylibScreenHeight = height;
    if(raylibScreenWidth < raylibMinScreenWidth)
    {
        raylibScreenWidth = raylibMinScreenWidth;
    }
    if(raylibScreenHeight < raylibMinScreenHeight)
    {
        raylibScreenHeight = raylibMinScreenHeight;
    }
}

void that_updateRaylibScreenSize()
{
    raylibScreenWidth  = GetScreenWidth();
    raylibScreenHeight = GetScreenHeight();
    if(raylibScreenWidth < raylibMinScreenWidth)
    {
        raylibScreenWidth = raylibMinScreenWidth;
    }
    if(raylibScreenHeight < raylibMinScreenHeight)
    {
        raylibScreenHeight = raylibMinScreenHeight;
    }
}

void that_createRaylibWindow()
{
    #ifdef NODEBUGME
        SetTraceLogLevel(LOG_ERROR);
    #endif // NODEBUGME

    if((raylibScreenWidth == 0) || (raylibScreenHeight == 0))
    {
        that_setRaylibWindowSize(INITIAL_SCREEN_WIDTH, INITIAL_SCREEN_HEIGHT);
    }

    InitWindow(raylibScreenWidth, raylibScreenHeight, TITLE_TEXT);

    raylibMinScreenWidth  = raylibScreenWidth;
    raylibMinScreenHeight = raylibScreenHeight;

    SetWindowState(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_UNDECORATED);

    that_updateRaylibScreenSize();

    raylibWindowPosX = GetWindowPosition().x;
    raylibWindowPosY = GetWindowPosition().y;

    raylibMonitorWidth  = GetMonitorWidth(GetCurrentMonitor());
    raylibMonitorHeight = GetMonitorHeight(GetCurrentMonitor());

    that_initResources();

    mainTexture = that_createRaylibMainTexture();
}

void that_changeRaylibClearColor(int red, int green, int blue, int alpha)
{
    raylibClearRed   = red;
    raylibClearGreen = green;
    raylibClearBlue  = blue;
    raylibClearAlpha = alpha;
}

int that_getScreenWidth()
{
    return raylibScreenWidth;
}

int that_getScreenHeight()
{
    return raylibScreenHeight;
}

int that_getRaylibGUIState()
{
    return rayGUIState;
}

void that_setRaylibGUIState(int state)
{
    rayGUIState = state;
}

void that_updateRaylibState()
{
    if(rayGUIState != MAIN_RESIZE && rayGUIState != MAIN_MOVE)
    {
        rayGUIState = MAIN_NONE;
    }

    if(IsWindowResized())
    {
        UnloadTexture(mainTexture);
        that_updateRaylibScreenSize();
        mainTexture = that_createRaylibMainTexture();
    }

    if((resizedTrigger > 0) && (rayGUIState == MAIN_RESIZE))
    {
        UnloadTexture(mainTexture);
        that_updateRaylibScreenSize();
        mainTexture = that_createRaylibMainTexture();
        resizedTrigger--;
    }

    if(rayGUIState == MAIN_RESIZE)
    {
        that_updateRaylibScreenSize();
        Vector2 delta = GetMouseDelta();
        if((delta.x != 0) && (delta.y != 0))
        {
            UnloadTexture(mainTexture);
            mainTexture = that_createRaylibMainTexture();
            resizedTrigger = 1;
        }
    }

    that_updateRaylibMouse();

    if(that_checkMousePos(raylibScreenWidth - 126, 6, raylibScreenWidth - 96, 35) == 1)
    {
        rayGUIState = MAIN_MINIMIZE;
        if(rayMouseButton1Released == 1)
        {
           MinimizeWindow();
        }
    } else if(that_checkMousePos(raylibScreenWidth - 80, 6, raylibScreenWidth - 50, 35) == 1)
    {
        rayGUIState = MAIN_MAXIMIZE;
        if(rayMouseButton1Released == 1)
        {
            isMaxedToggle = !isMaxedToggle;
            if(isMaxedToggle == 1)
            {
                maxTempToggleWidth  = raylibScreenWidth;
                maxTempToggleHeight = raylibScreenHeight;
                MaximizeWindow();
                UnloadTexture(mainTexture);
                that_updateRaylibScreenSize();
                mainTexture = that_createRaylibMainTexture();
            } else if(isMaxedToggle == 0)
            {
                raylibScreenWidth   = maxTempToggleWidth;
                raylibScreenHeight  = maxTempToggleHeight;
                RestoreWindow();
                UnloadTexture(mainTexture);
                mainTexture = that_createRaylibMainTexture();
            }
        }
    } else if(that_checkMousePos(raylibScreenWidth - 34, 6, raylibScreenWidth - 5, 35) == 1)
    {
        rayGUIState = MAIN_EXIT;
        if(rayMouseButton1Released == 1)
        {
           quitProgram = 1;
        }
    } else if(that_checkMousePos(raylibScreenWidth - 25, raylibScreenHeight - 25,
                                  raylibScreenWidth - 1, raylibScreenHeight - 1) == 1)
    {
        SetMouseCursor(MOUSE_CURSOR_RESIZE_ALL);
        if((rayMouseButton1Pressed == 1) && (rayGUIState != MAIN_RESIZE))
        {
            tempResultX = raylibScreenWidth - raylibMouseX;
            tempResultY = raylibScreenHeight - raylibMouseY;
            rayGUIState = MAIN_RESIZE;
        }
    } else if(that_checkMousePos(1, 1, raylibScreenWidth - 130, 40) == 1)
    {
        if((rayMouseButton1Pressed == 1) && (rayGUIState != MAIN_MOVE))
        {
            tempResultX = raylibMouseX;
            tempResultY = raylibMouseY;
            rayGUIState = MAIN_MOVE;
        }
    } else {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }

    if((rayMouseButton1Released == 1) && ((rayGUIState == MAIN_RESIZE) || (rayGUIState == MAIN_MOVE)))
    {
        raylibWindowPosX = GetWindowPosition().x;
        raylibWindowPosY = GetWindowPosition().y;
        rayGUIState = MAIN_NONE;
        resizedTrigger = 2;
    }
}

void that_updateRaylibLoop()
{
    BeginDrawing();
        DrawTexture(mainTexture, 0, 0, WHITE);
        if((isMaxedToggle == 1) && (rayGUIState != MAIN_MAXIMIZE))
        {
            drawMaximizedIcon();
        }

        if(rayGUIState == MAIN_MINIMIZE)
        {
            drawMinimizeIcon();
        } else if(rayGUIState == MAIN_MAXIMIZE)
        {
            drawMaxIcon();
        } else if(rayGUIState == MAIN_EXIT)
        {
            drawExitIcon();
        } else if(rayGUIState == MAIN_RESIZE)
        {
            Vector2 delta = GetMouseDelta();
            if((delta.x != 0) && (delta.y != 0))
            {
                int tempResizeWidth  = raylibMouseX + tempResultX;
                int tempResizeHeight = raylibMouseY + tempResultY;
                resizedTrigger = 2;
                if(tempResizeWidth < raylibMinScreenWidth)
                {
                    tempResizeWidth = raylibMinScreenWidth;
                    resizedTrigger = 0;
                }
                if(tempResizeHeight < raylibMinScreenHeight)
                {
                    tempResizeHeight = raylibMinScreenHeight;
                    resizedTrigger = 0;
                }
                SetWindowSize(tempResizeWidth, tempResizeHeight);
            }
        } else if(rayGUIState == MAIN_MOVE)
        {
            struct vec2 v = that_getGlobalMousePos();
            SetWindowPosition(v.x - tempResultX, v.y - tempResultY);
        }

        that_drawLiveText();  // Might need to update this function.
    EndDrawing();
}

int that_isRaylibClosed()
{
    if(WindowShouldClose())
    {
        quitProgram = 1;
    }
    return quitProgram;
}

void that_closeRaylibWindow()
{
    that_clearResources();
    that_cleanupStrings();
    UnloadTexture(mainTexture);
    CloseWindow();
}

