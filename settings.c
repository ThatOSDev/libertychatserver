
#include "settings.h"

struct GLOBAL_COLORS
{
    RGBA main_window_background;
    RGBA main_window_dragbar;
    RGBA main_window_outline;
    RGBA main_window_title_highlight;
    RGBA main_window_title_forground;
    RGBA main_window_tools_background;
    RGBA main_window_tools_forground;
    RGBA main_window_tools_outline;
    RGBA main_window_menu_background;
    RGBA main_window_menu_forground;
    RGBA main_window_menu_outline;
    RGBA container_window_background;
    RGBA container_window_forground;
    RGBA container_window_outline;
    RGBA container_window_dragbar_background_start;
    RGBA container_window_dragbar_background_end;
    RGBA container_window_dragbar_forground;
    RGBA container_window_dragbar_tools_background;
    RGBA container_window_dragbar_tools_forground;
    RGBA container_window_dragbar_tools_outline;
} GLOBAL_COLORS;

unsigned char colorThemeArray[160] = {

    // Theme 1 (Default)
    16, 16, 26, 255, 100, 120, 120, 255, 255, 165, 0, 255,      // main_window
    32, 32, 32, 255, 240, 240, 240, 255,                        // main_window_title
    255, 161, 0, 255, 255, 255, 255, 255, 1, 1, 1, 255,         // main_window_tools
    116, 116, 126, 255, 216, 216, 226, 255, 240, 240, 240, 255, // main_window_menu
    32, 32, 32, 255, 132, 132, 132, 255, 250, 240, 226, 255,    // container_window
    168, 168, 126, 255, 16, 16, 126, 255, 255, 255, 255, 255,   // container_window_dragbar
    216, 16, 16, 255, 255, 255, 255, 255, 240, 240, 240, 255,   // container_window_dragbar_tools

    // Theme 2
    116, 16, 26, 255, 16, 16, 26, 255, 16, 16, 26, 255,         // main_window
    32, 32, 32, 255, 240, 240, 240, 255,                        // main_window_title
    16, 16, 26, 255, 16, 16, 26, 255, 16, 16, 26, 255,          // main_window_tools
    16, 16, 26, 255, 16, 16, 26, 255, 16, 16, 26, 255,          // main_window_menu
    16, 16, 26, 255, 16, 16, 26, 255, 16, 16, 26, 255,          // container_window
    16, 16, 26, 255, 16, 16, 26, 255, 16, 16, 26, 255,          // container_window_dragbar
    16, 16, 26, 255, 16, 16, 26, 255, 16, 16, 26, 255           // container_window_dragbar_tools
                                      };

struct GLOBAL_COLORS globalColors;

void that_changeTheme(int themeNumber)
{
    if(themeNumber < 2)
    {
        themeNumber = 0;
    } else if(themeNumber > 1)
    {
        themeNumber *= 80;
        themeNumber -= 80;
    }

    globalColors.main_window_background.red                       = colorThemeArray[themeNumber + 0];
    globalColors.main_window_background.green                     = colorThemeArray[themeNumber + 1];
    globalColors.main_window_background.blue                      = colorThemeArray[themeNumber + 2];
    globalColors.main_window_background.alpha                     = colorThemeArray[themeNumber + 3];
    globalColors.main_window_dragbar.red                          = colorThemeArray[themeNumber + 4];
    globalColors.main_window_dragbar.green                        = colorThemeArray[themeNumber + 5];
    globalColors.main_window_dragbar.blue                         = colorThemeArray[themeNumber + 6];
    globalColors.main_window_dragbar.alpha                        = colorThemeArray[themeNumber + 7];
    globalColors.main_window_outline.red                          = colorThemeArray[themeNumber + 8];
    globalColors.main_window_outline.green                        = colorThemeArray[themeNumber + 9];
    globalColors.main_window_outline.blue                         = colorThemeArray[themeNumber + 10];
    globalColors.main_window_outline.alpha                        = colorThemeArray[themeNumber + 11];
    globalColors.main_window_title_highlight.red                  = colorThemeArray[themeNumber + 12];
    globalColors.main_window_title_highlight.green                = colorThemeArray[themeNumber + 13];
    globalColors.main_window_title_highlight.blue                 = colorThemeArray[themeNumber + 14];
    globalColors.main_window_title_highlight.alpha                = colorThemeArray[themeNumber + 15];
    globalColors.main_window_title_forground.red                  = colorThemeArray[themeNumber + 16];
    globalColors.main_window_title_forground.green                = colorThemeArray[themeNumber + 17];
    globalColors.main_window_title_forground.blue                 = colorThemeArray[themeNumber + 18];
    globalColors.main_window_title_forground.alpha                = colorThemeArray[themeNumber + 19];
    globalColors.main_window_tools_background.red                 = colorThemeArray[themeNumber + 20];
    globalColors.main_window_tools_background.green               = colorThemeArray[themeNumber + 21];
    globalColors.main_window_tools_background.blue                = colorThemeArray[themeNumber + 22];
    globalColors.main_window_tools_background.alpha               = colorThemeArray[themeNumber + 23];
    globalColors.main_window_tools_forground.red                  = colorThemeArray[themeNumber + 24];
    globalColors.main_window_tools_forground.green                = colorThemeArray[themeNumber + 25];
    globalColors.main_window_tools_forground.blue                 = colorThemeArray[themeNumber + 26];
    globalColors.main_window_tools_forground.alpha                = colorThemeArray[themeNumber + 27];
    globalColors.main_window_tools_outline.red                    = colorThemeArray[themeNumber + 28];
    globalColors.main_window_tools_outline.green                  = colorThemeArray[themeNumber + 29];
    globalColors.main_window_tools_outline.blue                   = colorThemeArray[themeNumber + 30];
    globalColors.main_window_tools_outline.alpha                  = colorThemeArray[themeNumber + 31];
    globalColors.main_window_menu_background.red                  = colorThemeArray[themeNumber + 32];
    globalColors.main_window_menu_background.green                = colorThemeArray[themeNumber + 33];
    globalColors.main_window_menu_background.blue                 = colorThemeArray[themeNumber + 34];
    globalColors.main_window_menu_background.alpha                = colorThemeArray[themeNumber + 35];
    globalColors.main_window_menu_forground.red                   = colorThemeArray[themeNumber + 36];
    globalColors.main_window_menu_forground.green                 = colorThemeArray[themeNumber + 37];
    globalColors.main_window_menu_forground.blue                  = colorThemeArray[themeNumber + 38];
    globalColors.main_window_menu_forground.alpha                 = colorThemeArray[themeNumber + 39];
    globalColors.main_window_menu_outline.red                     = colorThemeArray[themeNumber + 40];
    globalColors.main_window_menu_outline.green                   = colorThemeArray[themeNumber + 41];
    globalColors.main_window_menu_outline.blue                    = colorThemeArray[themeNumber + 42];
    globalColors.main_window_menu_outline.alpha                   = colorThemeArray[themeNumber + 43];
    globalColors.container_window_background.red                  = colorThemeArray[themeNumber + 44];
    globalColors.container_window_background.green                = colorThemeArray[themeNumber + 45];
    globalColors.container_window_background.blue                 = colorThemeArray[themeNumber + 46];
    globalColors.container_window_background.alpha                = colorThemeArray[themeNumber + 47];
    globalColors.container_window_forground.red                   = colorThemeArray[themeNumber + 48];
    globalColors.container_window_forground.green                 = colorThemeArray[themeNumber + 49];
    globalColors.container_window_forground.blue                  = colorThemeArray[themeNumber + 50];
    globalColors.container_window_forground.alpha                 = colorThemeArray[themeNumber + 51];
    globalColors.container_window_outline.red                     = colorThemeArray[themeNumber + 52];
    globalColors.container_window_outline.green                   = colorThemeArray[themeNumber + 53];
    globalColors.container_window_outline.blue                    = colorThemeArray[themeNumber + 54];
    globalColors.container_window_outline.alpha                   = colorThemeArray[themeNumber + 55];
    globalColors.container_window_dragbar_background_start.red    = colorThemeArray[themeNumber + 56];
    globalColors.container_window_dragbar_background_start.green  = colorThemeArray[themeNumber + 57];
    globalColors.container_window_dragbar_background_start.blue   = colorThemeArray[themeNumber + 58];
    globalColors.container_window_dragbar_background_start.alpha  = colorThemeArray[themeNumber + 59];
    globalColors.container_window_dragbar_background_end.red      = colorThemeArray[themeNumber + 60];
    globalColors.container_window_dragbar_background_end.green    = colorThemeArray[themeNumber + 61];
    globalColors.container_window_dragbar_background_end.blue     = colorThemeArray[themeNumber + 62];
    globalColors.container_window_dragbar_background_end.alpha    = colorThemeArray[themeNumber + 63];
    globalColors.container_window_dragbar_forground.red           = colorThemeArray[themeNumber + 64];
    globalColors.container_window_dragbar_forground.green         = colorThemeArray[themeNumber + 65];
    globalColors.container_window_dragbar_forground.blue          = colorThemeArray[themeNumber + 66];
    globalColors.container_window_dragbar_forground.alpha         = colorThemeArray[themeNumber + 67];
    globalColors.container_window_dragbar_tools_background.red    = colorThemeArray[themeNumber + 68];
    globalColors.container_window_dragbar_tools_background.green  = colorThemeArray[themeNumber + 69];
    globalColors.container_window_dragbar_tools_background.blue   = colorThemeArray[themeNumber + 70];
    globalColors.container_window_dragbar_tools_background.alpha  = colorThemeArray[themeNumber + 71];
    globalColors.container_window_dragbar_tools_forground.red     = colorThemeArray[themeNumber + 72];
    globalColors.container_window_dragbar_tools_forground.green   = colorThemeArray[themeNumber + 73];
    globalColors.container_window_dragbar_tools_forground.blue    = colorThemeArray[themeNumber + 74];
    globalColors.container_window_dragbar_tools_forground.alpha   = colorThemeArray[themeNumber + 75];
    globalColors.container_window_dragbar_tools_outline.red       = colorThemeArray[themeNumber + 76];
    globalColors.container_window_dragbar_tools_outline.green     = colorThemeArray[themeNumber + 77];
    globalColors.container_window_dragbar_tools_outline.blue      = colorThemeArray[themeNumber + 78];
    globalColors.container_window_dragbar_tools_outline.alpha     = colorThemeArray[themeNumber + 79];
}

void that_initDefaultTheme()
{
    that_changeTheme(1);
}

RGBA that_getMainWindowBackgroundColor()
{
    return globalColors.main_window_background;
}

RGBA that_getMainWindowDragbarColor()
{
    return globalColors.main_window_dragbar;
}

RGBA that_getMainWindowOutlineColor()
{
    return globalColors.main_window_outline;
}

RGBA that_getMainWindowTitleHighlightColor()
{
    return globalColors.main_window_title_highlight;
}

RGBA that_getMainWindowTitleForgroundColor()
{
    return globalColors.main_window_title_forground;
}

RGBA that_getMainWindowToolsBackgroundColor()
{
    return globalColors.main_window_tools_background;
}

RGBA that_getMainWindowToolsForgroundColor()
{
    return globalColors.main_window_tools_forground;
}

RGBA that_getMainWindowToolsOutlineColor()
{
    return globalColors.main_window_tools_outline;
}

RGBA that_getMainWindowMenuBackgroundColor()
{
    return globalColors.main_window_menu_background;
}

RGBA that_getMainWindowMenuForgroundColor()
{
    return globalColors.main_window_menu_forground;
}

RGBA that_getMainWindowMenuOutlineColor()
{
    return globalColors.main_window_menu_outline;
}

RGBA that_getContainerWindowBackgroundColor()
{
    return globalColors.container_window_background;
}

RGBA that_getContainerWindowForgroundColor()
{
    return globalColors.container_window_forground;
}

RGBA that_getContainerWindowOutlineColor()
{
    return globalColors.container_window_outline;
}

RGBA that_getContainerWindowDragbarBackgroundStartColor()
{
    return globalColors.container_window_dragbar_background_start;
}

RGBA that_getContainerWindowDragbarBackgroundEndColor()
{
    return globalColors.container_window_dragbar_background_end;
}

RGBA that_getContainerWindowDragbarForgroundColor()
{
    return globalColors.container_window_dragbar_forground;
}

RGBA that_getContainerWindowDragbarToolsBackgroundColor()
{
    return globalColors.container_window_dragbar_tools_background;
}

RGBA that_getContainerWindowDragbarToolsForgroundColor()
{
    return globalColors.container_window_dragbar_tools_forground;
}

RGBA that_getContainerWindowDragbarToolsOutlineColor()
{
    return globalColors.container_window_dragbar_tools_outline;
}




