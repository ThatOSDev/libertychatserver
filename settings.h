
#ifndef SETTINGS_H
#define SETTINGS_H

/*
    Main Window ( Dragbar Height )
    Themes ( Colors )
    Title Font   (Size, Spacing )
    Title Text

    More to be added ...
*/

#define MAIN_WINDOW_DRAGBAR_HEIGHT 40
#define TITLE_FONT_SIZE            28.0
#define GUI_FONT_SIZE              16.0
#define TEXT_FONT_SIZE             16.0
#define TEXT_FONT_HEIGHT           20.0
#define TEXT_FONT_SPACING          2.0
#define TITLE_TEXT_FONT_SPACING    2.0
#define TITLE_TEXT                 ("LIBERTY SERVER")
#define INITIAL_SCREEN_WIDTH       800
#define INITIAL_SCREEN_HEIGHT      400

typedef struct RGBA
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    unsigned char alpha;
} RGBA;

void that_changeTheme(int themeNumber);
void that_initDefaultTheme(void);

RGBA that_getMainWindowBackgroundColor(void);
RGBA that_getMainWindowDragbarColor(void);
RGBA that_getMainWindowOutlineColor(void);
RGBA that_getMainWindowTitleHighlightColor(void);
RGBA that_getMainWindowTitleForgroundColor(void);
RGBA that_getMainWindowToolsBackgroundColor(void);
RGBA that_getMainWindowToolsForgroundColor(void);
RGBA that_getMainWindowToolsOutlineColor(void);
RGBA that_getMainWindowMenuBackgroundColor(void);
RGBA that_getMainWindowMenuForgroundColor(void);
RGBA that_getMainWindowMenuOutlineColor(void);
RGBA that_getContainerWindowBackgroundColor(void);
RGBA that_getContainerWindowForgroundColor(void);
RGBA that_getContainerWindowOutlineColor(void);
RGBA that_getContainerWindowDragbarBackgroundStartColor(void);
RGBA that_getContainerWindowDragbarBackgroundEndColor(void);
RGBA that_getContainerWindowDragbarForgroundColor(void);
RGBA that_getContainerWindowDragbarToolsBackgroundColor(void);
RGBA that_getContainerWindowDragbarToolsForgroundColor(void);
RGBA that_getContainerWindowDragbarToolsOutlineColor(void);

#endif // SETTINGS_H
