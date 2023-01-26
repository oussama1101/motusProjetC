
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include "header.c"

typedef enum { JOUEUR, ORDINATEUR } Versus ;
typedef enum { ANGLAIS, FRANCAIS } Language ;
typedef enum { FACILE, MOYENNE, DIFFICILE } Difficulte ;

typedef struct UserPreferences{
    Versus vs;
    Language lang;
    Difficulte diff;
} UserPreferences;

typedef struct gameInfo{
    char* playerName;
    char* date;
    char* correctWord;
    int timePlayed;
} GameInfo;

char toLower(char c);
char *digitToStr(int n);
int lineCount(char* filename);
int validWord(char *word, int len, UserPreferences *up);
void randomWord(char *fileName, char *word);
void fileChooser(char *fileName, int len);
char* verifyUserWord(UserPreferences* up);
char* getCurrentTime();
void getPath(GameInfo *gameInfo, char *path);
void saveInfo(GameInfo *gi, UserPreferences *up);
int gameInfo(UserPreferences *up, GameInfo *gi);
void saveWord(GameInfo* gi, char* gWord);
void displayGrid(int diff, char *gWord, int color[], int attempts);
void core(UserPreferences *up, GameInfo *gi, char *word, char *gWord, int diff, int attempts);
void loadGame(char *dirName);
void startGame(UserPreferences *up);