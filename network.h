
#ifndef THAT_LIB_H
#define THAT_LIB_H

#define BUTTON_DOWN   1
#define BUTTON_UP     2
#define LEFT_BUTTON   0
#define RIGHT_BUTTON  1
#define MIDDLE_BUTTON 2

// SETTINGS
struct S_APP_SETTINGS
{
    char* TITLE;
    int   MAJOR;
    int   MINER;
    char* OS_NAME;
    int   WINDOW_WIDTH;
    int   WINDOW_HEIGHT;
    int   MIN_WINDOW_WIDTH;
    int   MIN_WINDOW_HEIGHT;
    int   WINDOW_X_POSITION;
    int   WINDOW_Y_POSITION;
    char* INTERNAL_IP4;
    char* INTERNAL_IP6;
    char* EXTERNAL_IP4;
    char* EXTERNAL_IP6;
    int   PORT;
};

struct S_APP_SETTINGS* that_checkSettings(char* title);
void                   that_settingsCleaup(void);

// NETWORK
void                   that_updateIPTable(void);
void                   that_listIPAddresses(void);
void                   that_initNetwork(void);
void                   that_checkNetwork(void);
void                   that_networkCleanup(void);

#endif // THAT_LIB_H
