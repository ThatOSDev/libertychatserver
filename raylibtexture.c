
#include "raylibtexture.h"
#include "raylibinterface.h"
#include "settings.h"
#include "stringmanager.h"

#define VERTICAL_TOP_TO_BOTTOM        0
#define HORIZONTAL_LEFT_TO_RIGHT      90
#define MAIN_WINDOW_BORDER_THICKNES   1
#define MAIN_WINDOW_TITLE_TEXT_XPOS   10
#define MAIN_WINDOW_TITLE_TEXT_YPOS   10
#define MAIN_WINDOW_TITLE_TEXT_OFFSET 3
#define CONTAINER_BORDER_THICKNES     2
#define INFO_BAR_HEIGHT               25

Texture2D MinIcon;
Texture2D MaxIcon;
Texture2D MaxedIcon;
Texture2D ExitIcon;

Texture2D tex;

Font titleFont;
Font guiFont;
Font textFont;

RGBA background      = {0};
RGBA outline         = {0};
RGBA dragbar         = {0};
RGBA toolsBackground = {0};
RGBA toolsForground  = {0};
RGBA toolsOutline    = {0};
RGBA titleHighlight  = {0};
RGBA titleForground  = {0};

Texture2D CreateMinimizeIcon()
{
    RenderTexture2D tempTexture = LoadRenderTexture(30, 30);
    BeginTextureMode(tempTexture);
        ClearBackground((Color){0, 0, 0, 0});
        DrawRectangle(1, 10, 30, 10, RED);
        DrawRectangleLines(0, 0, 30, 30, BLACK);
    EndTextureMode();
    Image tempImage = LoadImageFromTexture(tempTexture.texture);
    ImageFlipVertical(&tempImage);
    Texture2D tempTex = LoadTextureFromImage(tempImage);
    UnloadImage(tempImage);
    UnloadRenderTexture(tempTexture);
    return tempTex;
}

Texture2D CreateMaxIcon()
{
    RenderTexture2D tempTexture = LoadRenderTexture(30, 30);
    BeginTextureMode(tempTexture);
        ClearBackground((Color){0, 0, 0, 0});
        DrawRectangleLines(1, 1, 28, 28, RED);
        DrawRectangle(1, 20, 27, 8, RED);
        DrawRectangleLines(0, 0, 30, 30, BLACK);
    EndTextureMode();
    Image tempImage = LoadImageFromTexture(tempTexture.texture);
    ImageFlipVertical(&tempImage);
    Texture2D tempTex = LoadTextureFromImage(tempImage);
    UnloadImage(tempImage);
    UnloadRenderTexture(tempTexture);
    return tempTex;
}

Texture2D CreateMaximizedIcon()
{
    RenderTexture2D tempTexture = LoadRenderTexture(30, 30);
    BeginTextureMode(tempTexture);
        ClearBackground(WHITE);
        DrawRectangleLines(1, 1, 28, 28, RED);
        DrawRectangle(2, 2, 27, 10, RED);
        DrawRectangleLines(0, 0, 30, 30, BLACK);
    EndTextureMode();
    Image tempImage = LoadImageFromTexture(tempTexture.texture);
    ImageFlipVertical(&tempImage);
    Texture2D tempTex = LoadTextureFromImage(tempImage);
    UnloadImage(tempImage);
    UnloadRenderTexture(tempTexture);
    return tempTex;
}

Texture2D CreateExitIcon()
{
    RenderTexture2D tempTexture = LoadRenderTexture(30, 30);
    BeginTextureMode(tempTexture);
        ClearBackground((Color){0, 0, 0, 0});
        DrawRectangle(0, 0, 30, 30, RED);
        DrawLine(5, 4, 26, 25, (Color){toolsForground.red, toolsForground.green, toolsForground.blue, toolsForground.alpha});
        DrawLine(4, 4, 26, 26, (Color){toolsForground.red, toolsForground.green, toolsForground.blue, toolsForground.alpha});
        DrawLine(4, 5, 25, 26, (Color){toolsForground.red, toolsForground.green, toolsForground.blue, toolsForground.alpha});
        DrawLine(25, 4, 4, 25, (Color){toolsForground.red, toolsForground.green, toolsForground.blue, toolsForground.alpha});
        DrawLine(26, 4, 4, 26, (Color){toolsForground.red, toolsForground.green, toolsForground.blue, toolsForground.alpha});
        DrawLine(26, 5, 5, 26, (Color){toolsForground.red, toolsForground.green, toolsForground.blue, toolsForground.alpha});
        DrawRectangleLines(0, 0, 30, 30, (Color){toolsOutline.red, toolsOutline.green, toolsOutline.blue, toolsOutline.alpha});
    EndTextureMode();
    Image tempImage = LoadImageFromTexture(tempTexture.texture);
    ImageFlipVertical(&tempImage);
    Texture2D tempTex = LoadTextureFromImage(tempImage);
    UnloadImage(tempImage);
    UnloadRenderTexture(tempTexture);
    return tempTex;
}

void drawMinimizeIcon()
{
    int width  = that_getScreenWidth();
    DrawTexture(MinIcon, width - 126, 5, WHITE);
}

void drawMaxIcon()
{
    int width  = that_getScreenWidth();
    DrawTexture(MaxIcon, width - 80, 5, WHITE);
}

void drawMaximizedIcon()
{
    int width  = that_getScreenWidth();
    DrawTexture(MaxedIcon, width - 80, 5, WHITE);
}

void drawExitIcon()
{
    int width  = that_getScreenWidth();
    DrawTexture(ExitIcon, width - 35, 5, WHITE);
}

void that_initResources()
{
    that_initDefaultTheme();
    titleFont       = LoadFontEx("C:\\Windows\\Fonts\\consolaz.ttf", TITLE_FONT_SIZE, 0, 250);
    guiFont         = LoadFontEx("C:\\Windows\\Fonts\\arial.ttf", GUI_FONT_SIZE, 0, 250);
    textFont        = LoadFontEx("C:\\Windows\\Fonts\\arial.ttf", TEXT_FONT_SIZE, 0, 250);

    background      = that_getMainWindowBackgroundColor();
    outline         = that_getMainWindowOutlineColor();
    dragbar         = that_getMainWindowDragbarColor();
    toolsBackground = that_getMainWindowToolsBackgroundColor();
    toolsForground  = that_getMainWindowToolsForgroundColor();
    toolsOutline    = that_getMainWindowToolsOutlineColor();
    titleHighlight  = that_getMainWindowTitleHighlightColor();
    titleForground  = that_getMainWindowTitleForgroundColor();

    ExitIcon        = CreateExitIcon();
    MaxIcon         = CreateMaxIcon();
    MaxedIcon       = CreateMaximizedIcon();
    MinIcon         = CreateMinimizeIcon();
}

/*
    This sets up the main window (Texture).
    It draws everything that is not updated during the program execution
    with the exception of dynamically resizing the window.
    This texture is used instead of clearing the screen every frame.
*/
Texture2D that_createRaylibMainTexture()
{
    int width  = that_getScreenWidth();
    int height = that_getScreenHeight();

    Image tempImage = GenImageColor(width, height,
                (Color){background.red, background.green, background.blue, background.alpha});

    ImageDrawRectangle(&tempImage, MAIN_WINDOW_BORDER_THICKNES, MAIN_WINDOW_BORDER_THICKNES,
                width - (MAIN_WINDOW_BORDER_THICKNES * 2), MAIN_WINDOW_DRAGBAR_HEIGHT,
                (Color){dragbar.red, dragbar.green, dragbar.blue, dragbar.alpha});

    ImageDrawTextEx(&tempImage, titleFont, TITLE_TEXT,
                 (Vector2){MAIN_WINDOW_TITLE_TEXT_XPOS, MAIN_WINDOW_TITLE_TEXT_YPOS},
                     TITLE_FONT_SIZE, TITLE_TEXT_FONT_SPACING,
       (Color){titleHighlight.red, titleHighlight.green,
                   titleHighlight.blue, titleHighlight.alpha});

    ImageDrawTextEx(&tempImage, titleFont, TITLE_TEXT,
                 (Vector2){MAIN_WINDOW_TITLE_TEXT_XPOS + MAIN_WINDOW_TITLE_TEXT_OFFSET,
                           MAIN_WINDOW_TITLE_TEXT_YPOS + MAIN_WINDOW_TITLE_TEXT_OFFSET},
                           TITLE_FONT_SIZE, TITLE_TEXT_FONT_SPACING,
                           (Color){titleForground.red, titleForground.green,
                           titleForground.blue, titleForground.alpha});

    ImageDrawRectangle(&tempImage, width - 126, 15, 30, 10,
    (Color){toolsBackground.red, toolsBackground.green, toolsBackground.blue, toolsBackground.alpha});

    ImageDrawRectangle(&tempImage, width - 79, 25, 27, 8,
    (Color){toolsBackground.red, toolsBackground.green, toolsBackground.blue, toolsBackground.alpha});

    ImageDrawRectangle(&tempImage, width - 35, 5, 30, 30,
    (Color){toolsBackground.red, toolsBackground.green, toolsBackground.blue, toolsBackground.alpha});

    ImageDrawRectangleLines(&tempImage, (Rectangle) {width - 79, 6, 28, 28}, 1,
    (Color){toolsBackground.red, toolsBackground.green, toolsBackground.blue, toolsBackground.alpha});

    ImageDrawRectangleLines(&tempImage, (Rectangle) {width - 126, 5, 30, 30}, 1,
    (Color){toolsOutline.red, toolsOutline.green, toolsOutline.blue, toolsOutline.alpha});

    ImageDrawRectangleLines(&tempImage, (Rectangle) {width - 80, 5, 30, 30}, 1,
    (Color){toolsOutline.red, toolsOutline.green, toolsOutline.blue, toolsOutline.alpha});

    ImageDrawRectangleLines(&tempImage, (Rectangle) {width - 35, 5, 30, 30}, 1,
    (Color){toolsOutline.red, toolsOutline.green, toolsOutline.blue, toolsOutline.alpha});

    ImageDrawLine(&tempImage, width - 30, 9, width - 10, 29,
    (Color){toolsForground.red, toolsForground.green, toolsForground.blue, toolsForground.alpha});

    ImageDrawLine(&tempImage, width - 31, 9, width - 10, 30,
    (Color){toolsForground.red, toolsForground.green, toolsForground.blue, toolsForground.alpha});

    ImageDrawLine(&tempImage, width - 31, 10, width - 11, 30,
    (Color){toolsForground.red, toolsForground.green, toolsForground.blue, toolsForground.alpha});

    ImageDrawLine(&tempImage, width - 11, 9, width - 31, 29,
    (Color){toolsForground.red, toolsForground.green, toolsForground.blue, toolsForground.alpha});

    ImageDrawLine(&tempImage, width - 10, 9, width - 31, 30,
    (Color){toolsForground.red, toolsForground.green, toolsForground.blue, toolsForground.alpha});

    ImageDrawLine(&tempImage, width - 10, 10, width - 30, 30,
    (Color){toolsForground.red, toolsForground.green, toolsForground.blue, toolsForground.alpha});

    // Menu Bar
    ImageDrawRectangle(&tempImage, MAIN_WINDOW_BORDER_THICKNES, 40,
                width - (MAIN_WINDOW_BORDER_THICKNES * 2), 20, BLUE);

    ImageDrawTextEx(&tempImage, guiFont, "SETTINGS", (Vector2){20, 43}, GUI_FONT_SIZE, 2.0, BLACK);

    // Online Users
    ImageDrawRectangle(&tempImage, MAIN_WINDOW_BORDER_THICKNES + 2, 62, 202,
                        height - (MAIN_WINDOW_BORDER_THICKNES + 89), DARKGRAY);

    ImageDrawRectangle(&tempImage, 2 + (MAIN_WINDOW_BORDER_THICKNES + 2), 80, 198,
                        height - (MAIN_WINDOW_BORDER_THICKNES + 109), BLACK);

    ImageDrawRectangle(&tempImage, (MAIN_WINDOW_BORDER_THICKNES + 12), 72, 180, 20, GRAY);

    ImageDrawTextEx(&tempImage, guiFont, "ONLINE USERS", (Vector2){19, 74}, GUI_FONT_SIZE, 6.0, (Color){1, 1, 1, 255});
    ImageDrawTextEx(&tempImage, guiFont, "ONLINE USERS", (Vector2){20, 75}, GUI_FONT_SIZE, 6.0, (Color){200, 101, 0, 255});

    // Bottom Info Bar
    ImageDrawRectangle(&tempImage, MAIN_WINDOW_BORDER_THICKNES,
                height - (INFO_BAR_HEIGHT + MAIN_WINDOW_BORDER_THICKNES),
                width - (MAIN_WINDOW_BORDER_THICKNES * 2),
                (INFO_BAR_HEIGHT + 1) - MAIN_WINDOW_BORDER_THICKNES,
                BLUE);

    int wh = INFO_BAR_HEIGHT;
    for(unsigned int t = 0; t < 5; t++)
    {
        ImageDrawLine(&tempImage, (width - MAIN_WINDOW_BORDER_THICKNES) - wh,
                                  (height - MAIN_WINDOW_BORDER_THICKNES),
                                  (width - MAIN_WINDOW_BORDER_THICKNES),
                                  (height - MAIN_WINDOW_BORDER_THICKNES) - wh, WHITE);
        wh -= 5;
    }

    ImageDrawRectangleLines(&tempImage,
                (Rectangle) {0, 0, width, height},
                MAIN_WINDOW_BORDER_THICKNES,
                (Color){outline.red, outline.green, outline.blue, outline.alpha});

    UnloadTexture(tex);
    tex = LoadTextureFromImage(tempImage);
    UnloadImage(tempImage);
    return tex;
}

/*
    This creates the individual 'windows' that are over-laid on the main texture.
    These are CONTAINERS, which hold info to each their own.
    CONTAINERS can be dragged and dropped to various areas of the screen.

    DIRECTION
    ---------
    0  = Vertical
    90 = Horizontal
*/
// TODO : Fix this function. Too many parameters !
Texture2D that_createRaylibContainerTexture(int w, int h, int direction, Color c1, Color c2)
{
    Image tempImage = GenImageGradientLinear(w, h, direction, c1, c2);
    UnloadTexture(tex);
    tex = LoadTextureFromImage(tempImage);
    UnloadImage(tempImage);
    return tex;
}

void that_drawLiveText()
{

    int totalLines          = that_getTotalStrings();
    int totalDisplayedLines = (that_getScreenHeight() - ((INFO_BAR_HEIGHT * 2) + MAIN_WINDOW_DRAGBAR_HEIGHT)) / TEXT_FONT_HEIGHT;

    int leftOvers = 0;
    leftOvers = totalLines - totalDisplayedLines;
    if(leftOvers < 0)
    {
        leftOvers = 0;
    }

    // Temporary Text display.
    // TODO : Will need to optimize this, by drawing to texture.
    if(totalLines > 0)
    {
        int J = 1;
        for(int t = totalLines; t > leftOvers; t--)
        {
            DrawTextEx(textFont, that_getString(t - 1),
                       (Vector2) {220, that_getScreenHeight() - ((J * TEXT_FONT_HEIGHT) + INFO_BAR_HEIGHT)},
                       TEXT_FONT_SIZE, TEXT_FONT_SPACING, WHITE);
            J++;
        }
    }
}

void that_clearResources()
{
    UnloadTexture(MinIcon);
    UnloadTexture(MaxIcon);
    UnloadTexture(ExitIcon);
    UnloadTexture(tex);

    UnloadFont(titleFont);
    UnloadFont(guiFont);
    UnloadFont(textFont);
}
