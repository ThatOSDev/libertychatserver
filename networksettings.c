
#include "network.h"

#include <stdio.h>   // FILE      fputs()   fread()   fopen() printf()  fseek()  SEEK_END  SEEK_SET
#include <stdlib.h>  // malloc()  free()    atoi()
#include <string.h>  // strcat()  strcmp()  strlen()  strtok()

#define SETTINGS_FILE_NAME ("settings.ini")

char* statsArray[15] = {"Temp Title", "0", "1",
                        "OS NAME", "800", "600", "800", "450", "100",
                        "100", "255.255.255.255", "ffffff::ffffff:ffffff:ffffff:ffffff", "255.255.255.255",
                        "ffffff::ffffff:ffffff:ffffff:ffffff", "99999"};

char* settingsArray[16] = {"<PROGRAM_STATS>\n    <NAME>\n        TITLE: ", "\n    </NAME>\n    <VERSION>\n        MAJOR: ",
                   "\n        MINOR: ", "\n    </VERSION>\n    <OS>\n        SYSTEM: ", "\n    </OS>\n    <DIMENSIONS>\n        WIDTH: ",
                   "\n        HEIGHT: ", "\n    </DIMENSIONS>\n    <MINIMUM_SIZE>\n        MIN_WIDTH: ", "\n        MIN_HEIGHT: ",
                   "\n    </MINIMUM_SIZE>\n    <POSITION>\n        POSITION_X: ", "\n        POSITION_Y: ",
                   "\n    </POSITION>\n    <NETWORK>\n        INTERNAL_IP4: ", "\n        INTERNAL_IP6: ", "\n        EXTERNAL_IP4: ",
                   "\n        EXTERNAL_IP6: ", "\n        PORT: ", "\n    </NETWORK>\n</PROGRAM_STATS>"};

struct S_APP_SETTINGS* APP_SETTINGS = NULL;

void getSubString(int strBegin, int strEnd, char* dest, char* src)
{
    for(int t = strBegin; t < strEnd; t++)
    {
        dest[t] = src[t];
    }
}

struct S_APP_SETTINGS* that_checkSettings(char* title)
{
    that_listIPAddresses();
    //that_updateIPTable();
    APP_SETTINGS               = calloc(1, sizeof(struct S_APP_SETTINGS));

    FILE* fPtr = fopen(SETTINGS_FILE_NAME, "rb+");
    if(fPtr == NULL)
    {


        statsArray[0] = title;
        #if defined(_WIN64)
            statsArray[3] = "Windows x64";
        #elif defined(_WIN32)
            statsArray[3] = "Windows x86";
        #endif

        statsArray[2] = "2";
        statsArray[10] = "127.0.0.1";
        statsArray[11] = "::1";
        statsArray[14] = "8080";

      //  printf("Writting to File ...      ");
        fPtr = fopen(SETTINGS_FILE_NAME, "wb");
        char iniFile[760] = {'\0'};
        for(int t = 0; t < 15; t++)
        {
            strcat(iniFile, settingsArray[t]);
            strcat(iniFile, statsArray[t]);
        }
        strcat(iniFile, settingsArray[15]);
        fputs(iniFile, fPtr);
        fclose(fPtr);
      //  printf("DONE !\n\n");
        fPtr = fopen(SETTINGS_FILE_NAME, "rb+");
    }

    fseek(fPtr, 0, SEEK_END);
    long fsize = ftell(fPtr) + 1;
    fseek(fPtr, 0, SEEK_SET);

    char *m_String = malloc(fsize);
    fread(m_String, fsize, 1, fPtr);

    fclose(fPtr);
    m_String[fsize] = '\0';

    char *pt;
    pt = strtok(m_String, " ");
    do
    {
        if(strcmp(pt, "TITLE:") == 0)
        {
            pt = strtok(NULL, "<");
            long total = strlen(pt) + 1;
            APP_SETTINGS->TITLE        = calloc(total, sizeof(char));
            getSubString(0, total, APP_SETTINGS->TITLE, pt);
           // printf("        APPLICATION NAME : %s\n", APP_SETTINGS->TITLE);
        }

        if(strcmp(pt, "MAJOR:") == 0)
        {
            pt = strtok(NULL, " ");
            APP_SETTINGS->MAJOR = atoi(pt);
           // printf("     APPLICATION VERSION : %d", APP_SETTINGS->MAJOR);
        }

        if(strcmp(pt, "MINOR:") == 0)
        {
            pt = strtok(NULL, " ");
            APP_SETTINGS->MINER = atoi(pt);
          //  printf(".%d\n\n", APP_SETTINGS->MINER);
        }

        if(strcmp(pt, "SYSTEM:") == 0)
        {
            pt = strtok(NULL, "<");
            long total = strlen(pt) + 1;
            APP_SETTINGS->OS_NAME      = calloc(total, sizeof(char));
            getSubString(0, total, APP_SETTINGS->OS_NAME, pt);
          //  printf("        OPERATING SYSTEM : %s\n", APP_SETTINGS->OS_NAME);
        }

        if(strcmp(pt, "WIDTH:") == 0)
        {
            pt = strtok(NULL, " ");
            APP_SETTINGS->WINDOW_WIDTH = atoi(pt);
           // printf("        APPLICATION SIZE : %d", APP_SETTINGS->WINDOW_WIDTH);
        }

        if(strcmp(pt, "HEIGHT:") == 0)
        {
            pt = strtok(NULL, " ");
            APP_SETTINGS->WINDOW_HEIGHT = atoi(pt);
           // printf("x%d\n\n", APP_SETTINGS->WINDOW_HEIGHT);
        }

        if(strcmp(pt, "MIN_WIDTH:") == 0)
        {
            pt = strtok(NULL, " ");
            APP_SETTINGS->MIN_WINDOW_WIDTH = atoi(pt);
           // printf("APPLICATION MINIMUM SIZE : %d", APP_SETTINGS->MIN_WINDOW_WIDTH);
        }

        if(strcmp(pt, "MIN_HEIGHT:") == 0)
        {
            pt = strtok(NULL, " ");
            APP_SETTINGS->MIN_WINDOW_HEIGHT = atoi(pt);
           // printf("x%d\n\n", APP_SETTINGS->MIN_WINDOW_HEIGHT);
        }

        if(strcmp(pt, "POSITION_X:") == 0)
        {
            pt = strtok(NULL, " ");
            APP_SETTINGS->WINDOW_X_POSITION = atoi(pt);
           // printf("         WINDOW POSITION : %d", APP_SETTINGS->WINDOW_X_POSITION);
        }


        if(strcmp(pt, "POSITION_Y:") == 0)
        {
            pt = strtok(NULL, " ");
            APP_SETTINGS->WINDOW_Y_POSITION = atoi(pt);
           // printf("x%d\n\n", APP_SETTINGS->WINDOW_Y_POSITION);
        }

        if(strcmp(pt, "INTERNAL_IP4:") == 0)
        {
            pt = strtok(NULL, " ");
            long total = strlen(pt) + 1;
            APP_SETTINGS->INTERNAL_IP4 = calloc(total, sizeof(char));
            getSubString(0, total, APP_SETTINGS->INTERNAL_IP4, pt);
           // printf("            INTERNAL IP4 : %s\n", APP_SETTINGS->INTERNAL_IP4);
        }

        if(strcmp(pt, "INTERNAL_IP6:") == 0)
        {
            pt = strtok(NULL, " ");
            long total = strlen(pt) + 1;
            APP_SETTINGS->INTERNAL_IP6 = calloc(total, sizeof(char));
            getSubString(0, total, APP_SETTINGS->INTERNAL_IP6, pt);
          //  printf("            INTERNAL IP6 : %s\n", APP_SETTINGS->INTERNAL_IP6);
        }

        if(strcmp(pt, "EXTERNAL_IP4:") == 0)
        {
            pt = strtok(NULL, " ");
            long total = strlen(pt) + 1;
            APP_SETTINGS->EXTERNAL_IP4 = calloc(total, sizeof(char));
            getSubString(0, total, APP_SETTINGS->EXTERNAL_IP4, pt);
           // printf("            EXTERNAL IP4 : %s\n", APP_SETTINGS->EXTERNAL_IP4);
        }

        if(strcmp(pt, "EXTERNAL_IP6:") == 0)
        {
            pt = strtok(NULL, " ");
            long total = strlen(pt) + 1;
            APP_SETTINGS->EXTERNAL_IP6 = calloc(total, sizeof(char));
            getSubString(0, total, APP_SETTINGS->EXTERNAL_IP6, pt);
           // printf("            EXTERNAL IP6 : %s\n", APP_SETTINGS->EXTERNAL_IP6);
        }

        if(strcmp(pt, "PORT:") == 0)
        {
            pt = strtok(NULL, " ");
            APP_SETTINGS->PORT = atoi(pt);
           // printf("                    PORT : %d\n\n", APP_SETTINGS->PORT);
        }

        pt = strtok(NULL, " ");
    } while(pt != NULL);
    free(m_String);
    return APP_SETTINGS;
}

void that_settingsCleaup()
{
    free(APP_SETTINGS->TITLE);
    free(APP_SETTINGS->OS_NAME);
    free(APP_SETTINGS->INTERNAL_IP4);
    free(APP_SETTINGS->INTERNAL_IP6);
    free(APP_SETTINGS->EXTERNAL_IP4);
    free(APP_SETTINGS->EXTERNAL_IP6);
    free(APP_SETTINGS);
}



