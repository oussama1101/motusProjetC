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

int lineCount(char* filename) {
 FILE *file;
    int lines = 0;
    char ch;
    file = fopen(filename, "r");
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            lines++;
        }
    }
    fclose(file);
    return lines+1;
}

int validWord(char *word, int len) {
    int valid = 0;
    if(!((word[0] >= 65 && word[0] <= 90) || (word[0] >= 97 && word[0] <= 122)))
        return 0;
    char fileName[30] = "dictionary/";
    strncat(fileName, "WordOf", (int)strlen("WordOf")+1);
    strncat(fileName, digitToStr(len), (int)strlen(digitToStr(len))+1);
    char c = '/';
    strncat(fileName, &c, (int)strlen(&c));
    c = toLower(word[0]);
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
    int i = 1, n = lineCount(fileName), r;
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

void fileChooser(char *fileName, int len) {
    strncat(fileName, "dictionary/", (int)strlen("dictionary/")+1);
    strncat(fileName, "WordOf", (int)strlen("WordOf")+1);
    strncat(fileName, digitToStr(len), (int)strlen(digitToStr(len))+1);
    char c = '/';
    strncat(fileName, &c, (int)strlen(&c));
    srand(time(0));  
    c = rand()%26+97;
    strncat(fileName, &c, (int)strlen(&c));
    strncat(fileName, "WordOf", (int)strlen("WordOf")+1);
    strncat(fileName, digitToStr(len), (int)strlen(digitToStr(len))+1);
    strncat(fileName, ".txt", (int)strlen(".txt")+1);
    //printf("\n%s\n", fileName);
}

char* verifyUserWord(UserPreferences* up){
    char* fileName = malloc(30 * sizeof(char));
    char* word =  malloc(30 * sizeof(char));
    switch (up->lang){
        case ANGLAIS:
            switch(up->diff){
                case FACILE:
                    do {
                        printf("\033[34m");printf("  [");
                        printf("\033[33m");printf("Joueur 1");
                        printf("\033[34m");printf("]");
                        printf("\033[37m");printf(" Veuillez entrer le ");
                        printf("\033[34m");printf("Mot");
                        printf("\033[37m");printf(" a deviner : ");
                        scanf("%s",word);
                            printf("\x1b[1F"); // monter le curseur en haut 
                            printf("\x1b[2K"); // supprimer la ligne de l'affichage
                    } while(!validWord(word,4));
                    return word;
                    break;
                case MOYENNE:
                    do {
                        printf("\033[34m");printf("  [");
                        printf("\033[33m");printf("Joueur 1");
                        printf("\033[34m");printf("]");
                        printf("\033[37m");printf(" Veuillez entrer le ");
                        printf("\033[34m");printf("Mot");
                        printf("\033[37m");printf(" a deviner : ");
                        scanf("%s",word);
                            printf("\x1b[1F"); // monter le curseur en haut 
                            printf("\x1b[2K"); // supprimer la ligne de l'affichage
                    } while(!validWord(word,5));
                    return word;
                    break;
                case DIFFICILE:
                    do {
                        printf("\033[34m");printf("  [");
                        printf("\033[33m");printf("Joueur 1");
                        printf("\033[34m");printf("]");
                        printf("\033[37m");printf(" Veuillez entrer le ");
                        printf("\033[34m");printf("Mot");
                        printf("\033[37m");printf(" a deviner : ");
                        scanf("%s",word);
                            printf("\x1b[1F"); // monter le curseur en haut 
                            printf("\x1b[2K"); // supprimer la ligne de l'affichage
                    } while(!validWord(word,4));
                    return word;
                    break;
            }
            break;
    }
}


char* getCurrentTime(){
    time_t rawtime;
    struct tm * timeInfo;
    time(&rawtime);
    timeInfo = localtime(&rawtime);
    char * currentTime = asctime(timeInfo);
    int i=0;
    while(currentTime[i] != '\0'){
        if (currentTime[i] == ' ')
            currentTime[i]='_';
        if(currentTime[i] == '\n')
            currentTime[i]='\0';
        i++;
    }
    return currentTime;
}

void getPath(GameInfo *gameInfo, char *path) {
    strncat(path, gameInfo->playerName , (int)strlen(gameInfo->playerName)+1);
    strncat(path, "_", (int)strlen("_")+1);
    strncat(path, gameInfo->date , (int)strlen(gameInfo->date)+1);
    strncat(path, ".txt", (int)strlen(".txt")+1);
}

void saveInfo(GameInfo *gi, UserPreferences *up){
    char path[50] = "saves/";
    getPath(gi, path);
    FILE *filePtr;
    filePtr = fopen(path, "w");
    if (filePtr != NULL) {
        fprintf(filePtr, "%d\t%d\t%d\n", up->vs, (int)up->lang, (int)up->diff);
        fprintf(filePtr, "%s\t%s\t%s\n", gi->playerName, gi->date, gi->correctWord);
    }
    fclose(filePtr); // On ferme le fichier qui a été ouvert
}

int gameInfo(UserPreferences *up, GameInfo *gi) {
    int diff = 0;
    printf("\033[2J\033[1;1H"); //clear the terminal
    header();
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
            diff = 4;
            printf("\033[33m");printf(" FACILE \n");
            printf("\033[37m");printf("  Le mot se compose de \033[33m 4 LETTRES \n");
        break;
        case MOYENNE:
            diff = 5;
            printf("\033[33m");printf(" MOYENNE \n");
            printf("\033[37m");printf("  Le mot se compose de \033[33m 5 LETTRES \n");
        break;
        case DIFFICILE:
            diff = 6;
            printf("\033[33m");printf(" DIFFICILE \n");
            printf("\033[37m");printf("  Le mot se compose de \033[33m 6 LETTRES \n");  
        break;
    }    
    printf("\033[33m");printf("  +");
    printf("\033[36m");printf("----------------------------------------------------------");
    printf("\033[33m");printf("+\n");
    printf("\033[39m");
    return diff;
}

void loadGame(char *dirName){
    UserPreferences *up = (UserPreferences*)malloc(sizeof(UserPreferences));
    GameInfo *gi = (GameInfo*)malloc(sizeof(GameInfo));
    gi->playerName = (char*)malloc(60 * sizeof(char));
    gi->date = (char*)malloc(60 * sizeof(char));
    gi->correctWord = (char*)malloc(60 * sizeof(char));
    int vs = 0, lang = 0, diff = 0, attempts = 0;
    FILE *filePtr;
    filePtr = fopen(dirName, "r");
    if (filePtr == NULL)
        exit(-1);
    fscanf(filePtr, "%d\t%d\t%d\n", &vs, &lang, &diff);
    fscanf(filePtr, "%s\t%s\t%s\n", gi->playerName, gi->date, gi->correctWord);
    if(vs == 0)   up->vs = JOUEUR;
    else    up->vs = ORDINATEUR; 
    if(lang == 0)   up->lang = ANGLAIS;
    else    up->lang = FRANCAIS;
    if(diff == 0)   up->diff = FACILE;
    else if(diff == 1)    up->diff = MOYENNE;
    else    up->diff = DIFFICILE;
    diff = gameInfo(up, gi);
    char* gWord;
    while(!feof(filePtr)){
        gWord = malloc(60 * sizeof(char));
        fscanf(filePtr, "%s\n", gWord);
        attempts++;
        int color[diff];
        for(int i = 0; i < diff; i++) {
            color[i] = 0;
        }
        for(int i = 0; i < up->diff; i++) {
            for(int j = 0; j < diff; j++) {
                if(gWord[i] == gi->correctWord[j]){
                    color[i] = 1;
                    if(i==j)
                        color[i] = 2;
                }
            }
        }
        for (int i = 0; i < diff; i++) {
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
    }
    fclose(filePtr);

    struct timeval start_time,end_time;
    gettimeofday(&start_time, NULL);
    char *word = malloc(60*sizeof(char));
    word = gi->correctWord;
    //printf("%s\n",gi->date);
    //printf("\n%s\n", word);
    int exit = 0;
    //printf("%s\n",gi->playerName);
    //printf("%s\n",gi->correctWord);
    do {
        int color[diff];
        for(int i = 0; i < diff; i++) {
            color[i] = 0;
        }
        scanf("%s", gWord);
        if(!strcmp(gWord, "exit")) {
            printf("the right anwser is \033[32m%s\033[39m\n", word);
            break;
        }
        if(!validWord(gWord, diff)) {
            printf("\x1b[1F");
            printf("\x1b[2K");
        } else {
            attempts++;
            
            for(int i = 0; i < diff; i++) {
                for(int j = 0; j < diff; j++) {
                    if(gWord[i] == word[j]){
                        color[i] = 1;
                        if(i==j)
                            color[i] = 2;
                    }
                }
            }
            printf("\x1b[1F");
            printf("\x1b[2K");
            for (int i = 0; i < diff; i++) {
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
            for (int i = 0; i < diff; i++) {
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

void saveWord(GameInfo* gi, char* gWord){
    FILE *filePtr;
    char path[50] = "saves/";
    getPath(gi, path);
    filePtr = fopen(path, "a");
    if (filePtr != NULL) {
        fprintf(filePtr, "%s\n", gWord);   
    }
    fclose(filePtr); // On ferme le fichier qui a été ouvert
}

void core(UserPreferences *up) {
    int diff = 0;
    GameInfo *gi = (GameInfo*)malloc(sizeof(GameInfo));
    gi->playerName = (char*)malloc(60 * sizeof(char));
    printf("\033[2J\033[1;1H"); //clear the terminal
    header();
    printf("\033[34m");printf("  [");
    printf("\033[33m");printf("!");
    printf("\033[34m");printf("]");
    printf("\033[37m");printf(" Veuillez entrer votre ");
    printf("\033[34m");printf("Nom");
    printf("\033[37m");printf(" pour continuer : ");
    scanf("%s", gi->playerName);
    sleep(1);
    printf("\x1b[1F"); // monter le curseur en haut 
    printf("\x1b[2K"); // supprimer la ligne de l'affichage
    diff = gameInfo(up, gi);
    struct timeval start_time,end_time;
    gettimeofday(&start_time, NULL);
    char *word = malloc(60*sizeof(char)), *gWord = malloc(60 * sizeof(char));
    if(up->vs == ORDINATEUR) {
        char *fileName = malloc(30 * sizeof(char));
        fileChooser(fileName, diff);
        if(up->lang == ANGLAIS){
            randomWord(fileName, word);
        }else{
            randomWord("fr.txt", word);
        } 
    } else {
        word = verifyUserWord(up);
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
    gi->correctWord = word;
    gi->date = getCurrentTime();
    //printf("%s\n",gi->date);
    //printf("\n%s\n", word);
    int attempts = 0, exit = 0;
    //printf("%s\n",gi->playerName);
    printf("%s\n",gi->correctWord);
    do {
        int color[diff];
        for(int i = 0; i < diff; i++) {
            color[i] = 0;
        }
        scanf("%s", gWord);
        if(!strcmp(gWord, "exit")) {
            printf("the right anwser is \033[32m%s\033[39m\n", word);
            break;
        }
        if(!validWord(gWord, diff)) {
            printf("\x1b[1F");
            printf("\x1b[2K");
        } else {
            attempts++;
            if(attempts == 1)
                saveInfo(gi, up);
            saveWord(gi, gWord);
            for(int i = 0; i < diff; i++) {
                for(int j = 0; j < diff; j++) {
                    if(gWord[i] == word[j]){
                        color[i] = 1;
                        if(i==j)
                            color[i] = 2;
                    }
                }
            }
            printf("\x1b[1F");
            printf("\x1b[2K");
            for(int i = 0; i < diff; i++){
                    if(i==0){
                        printf("\033[33m");printf(" +");
                        printf("\033[36m");printf("---");
                        printf("\033[33m");printf("+");
                    }else if(i == (diff-1)){
                        printf("\033[36m");printf("---");
                        printf("\033[33m");printf("+\n");
                    }else {
                        printf("\033[36m");printf("---");
                        printf("\033[33m");printf("+");
                    }
            
            }
            for (int i = 0; i < diff; i++) {
                if(color[i] == 2) {
                    printf("\033[36m | ");
                    printf("\033[32m%c", gWord[i]);
                } else if (color[i] == 1) {
                    printf("\033[36m | ");
                    printf("\033[31m%c", gWord[i]);
                } else {
                    printf("\033[36m | ");
                    printf("\033[39m%c", gWord[i]);
                }
                //printf("%i", color[i]);
            }
                        for(int i = 0; i < diff; i++){
                    if(i==0){
                        printf("\033[33m");printf("\n +");
                        printf("\033[36m");printf("---");
                        printf("\033[33m");printf("+");
                    }else if(i == (diff-1)){
                        printf("\033[36m");printf("---");
                        printf("\033[33m");printf("+");
                    }else {
                        printf("\033[36m");printf("---");
                        printf("\033[33m");printf("+");
                    }
            
            }

            printf("\n\033[39m");
            exit = 1;
            for (int i = 0; i < diff; i++) {
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
    char path[50] = "saves/";
    getPath(gi, path);
    remove(path);
    getchar();
    getchar();
}