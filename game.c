#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <string.h>
#include <sys/time.h>
#include "header.c"

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


void core() {

    printf("\033[2J\033[1;1H");
    header();

    struct timeval start_time,end_time;
    gettimeofday(&start_time, NULL);

    char *word = malloc(5*sizeof(char)), *gWord = malloc(60 * sizeof(char));
    randomWord("eng.txt", word);
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