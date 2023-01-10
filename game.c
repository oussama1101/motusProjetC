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

char toLower(char c) {
    if(c >= 'a' && c <= 'z')
        return c;
    return c + 32;
}

char *digitToStr(int n) {
    char *numbers[] = {"One", "Two", "Three", "Four", "Five", "Six", "Seven"};
    return numbers[n-1];
}

int validWord(char *word, int len) {
    int valid = 0;
    if(!((word[0] >= 65 && word[0] <= 90) || (word[0] >= 97 && word[0] <= 122)))
        return 0;
    char c = toLower(word[0]);
    char fileName[30] = "dictionary/wordOfFive/";
    strncat(fileName, &c, (int)strlen(&c));
    strncat(fileName, "WordOf", (int)strlen("WordOf")+1);
    strncat(fileName, digitToStr(len), (int)strlen(digitToStr(len))+1);
    strncat(fileName, ".txt", (int)strlen(".txt")+1);
    //printf("\n%s\n", fileName);
    FILE *f = fopen(fileName, "r");
    char *dicWord = malloc(5*sizeof(char));
    while (!feof(f)) {
        fscanf(f, "%s", dicWord);
        if(strcmp(dicWord, word) == 0) {
            valid = 1;
            break;
        }
    }
    fclose(f);
    return valid;
}

void randomWord(char *fileName, char *word) {
    FILE *f = fopen(fileName, "r");
    int i = 1, n = 5, r;
    srand(time(0));  
    r = (rand()%n+1);
    while (!feof(f)) {
        fscanf(f, "%s", word);
        if(i == r)
            break;
        i++;
    }
    fclose(f);
}


void core(UserPreferences *up) {
    GameInfo *gi = (GameInfo*)malloc(sizeof(GameInfo));
    gi->playerName = (char*)malloc(60 * sizeof(char));
    printf("\033[2J\033[1;1H");
    header();
    printf("\033[34m");printf("  [");
    printf("\033[33m");printf("!");
    printf("\033[34m");printf("]");
    printf("\033[37m");printf(" Veuillez entrer votre ");
    printf("\033[34m");printf("Nom");
    printf("\033[37m");printf(" pour continuer : ");
    scanf("%s", gi->playerName);
    sleep(1);
    printf("\x1b[1F");
    printf("\x1b[2K");
    printf("\033[37m");printf("  Nom du joueur : ");
    printf("\033[33m");printf(" %s \n",gi->playerName);
    printf("\033[37m");printf("  Le mot est en :");
    switch(up->lang){
        case ANGLAIS:
                printf("\033[33m");printf(" ANGLAIS \n");
        break;
        case FRANCAIS:
            printf("\033[33m");printf(" FRANCAIS \n");
        break;
    }
    printf("\033[37m");printf("  La difficulte du jeu est :");
    switch(up->diff){
        case FACILE:
            printf("\033[33m");printf(" FACILE \n");
            printf("\033[37m");printf("  Le mot se compose de \033[33m 4 LETTRES \n");                
        break;
        case MOYENNE:
            printf("\033[33m");printf(" MOYENNE \n");
            printf("\033[37m");printf("  Le mot se compose de \033[33m 5 LETTRES \n");  
        break;
        case DIFFICILE:
            printf("\033[33m");printf(" DIFFICILE \n");
            printf("\033[37m");printf("  Le mot se compose de \033[33m 6 LETTRES \n");  
        break;
    }    
    
    printf("\033[33m");printf("  +");
    printf("\033[36m");printf("----------------------------------------------------------");
    printf("\033[33m");printf("+\n");
    
    struct timeval start_time,end_time;
    gettimeofday(&start_time, NULL);
    char *word = malloc(5*sizeof(char)), *gWord = malloc(60 * sizeof(char));
    if (up->vs == ORDINATEUR)
        randomWord("eng.txt", word);
    else {
        printf("\033[34m");printf("  [");
        printf("\033[33m");printf("Joueur 1");
        printf("\033[34m");printf("]");
        printf("\033[37m");printf(" Veuillez entrer le ");
        printf("\033[34m");printf("Mot");
        printf("\033[37m");printf(" a deviner : ");
        scanf("%s", word);
        sleep(1);
        printf("\x1b[1F");
        printf("\x1b[2K");
        printf("\033[34m");printf("  [");
        printf("\033[33m");printf("Joueur 1");
        printf("\033[34m");printf("]");
        printf("\033[37m");printf(" a entre le mot a deviner ! \n");
        printf("\033[33m");printf("  +");
        printf("\033[36m");printf("----------------------------------------------------------");
        printf("\033[33m");printf("+\n");
        printf("\033[34m");printf("  [");
        printf("\033[33m");printf("Joueur 2");
        printf("\033[34m");printf("]");
        printf("\033[37m");printf(" a vous de jouer maintenant !\n");
    }
    //printf("\n%s\n", word);
    int attempts = 0, exit = 0;
    do {
        int color[5] = {0, 0, 0, 0, 0};
        scanf("%s", gWord);
        if(!strcmp(gWord, "exit")) {
            printf("the right anwser is \033[32m%s\033[39m\n", word);
            break;
        }
        if(!validWord(gWord, 5)) {
            printf("\x1b[1F");
            printf("\x1b[2K");
        } else {
            attempts++;
            for(int i = 0; i < 5; i++) {
                for(int j = 0; j < 5; j++) {
                    if(gWord[i] == word[j]){
                        color[i] = 1;
                        if(i==j)
                            color[i] = 2;
                    }
                }
            }
            printf("\x1b[1F");
            printf("\x1b[2K");
            for (int i = 0; i < 5; i++) {
                if(color[i] == 2) {
                    printf("\033[32m%c", gWord[i]);
                } else if (color[i] == 1) {
                    printf("\033[31m%c", gWord[i]);
                } else {
                    printf("\033[39m%c", gWord[i]);
                }
                //printf("%i", color[i]);
            }
            printf("\n\033[39m");
            exit = 1;
            for (int i = 0; i < 5; i++) {
                if(color[i] != 2) {
                    exit = 0;
                    break;
                }
            }
        }
    } while (!exit);
    gettimeofday(&end_time, NULL);
    printf("Your number of attempts is %i\n", attempts);
    printf("seconds : %ld\n", end_time.tv_sec - start_time.tv_sec);
    getchar();
    getchar();
}