#include <stdlib.h>
#include <stdio.h>
#include "game.c"

void chargeroptions(char* liste[],int n,char* titre){
    printf("\033[36m");printf("  +");
    printf("\033[37m");printf("----------------------------------------------------------");
    printf("\033[36m");printf("+\n");
    printf("\033[37m");printf("  |   ");
    printf("\033[36m");printf("N");
    printf("\033[37m");printf("   |");
    printf("\033[35m");printf("%s",titre);
    printf("\033[37m");printf("\n");
    printf("\033[36m");printf("  +");
    printf("\033[37m");printf("----------------------------------------------------------");
    printf("\033[36m");printf("+\n");
    printf("\033[37m");
    for(int i=0;i<n;i++){
        printf("  |  ");printf("\033[34m");
        printf("[");printf("\033[36m");printf("%d",i+1);printf("\033[34m");printf("]");
        printf("\033[37m");printf("  |");
        printf("\033[32m");printf("%s",liste[i]);
        printf("\033[37m");printf("\n");
    }
    printf("\033[36m");printf("  +");
    printf("\033[37m");printf("----------------------------------------------------------");
    printf("\033[36m");printf("+\n");
    printf("\033[34m");printf("  [");
    printf("\033[33m");printf("!");
    printf("\033[34m");printf("]");
    printf("\033[37m");printf(" Veuillez choisir un ");
    printf("\033[34m");printf("N");
    printf("\033[37m");printf(" pour continuer :");
}

void ChoixDifficulte(){

    int choice =0;
    char *menu[] = {
        " Facile ",
        " Moyenne ",
        " Difficle ",
        " Retour ",
        " Quitter ",
    };
    while (choice != 5) {
        printf("\033[2J\033[1;1H");
        header();
        chargeroptions(menu,5," Choix de difficulte ");
        scanf("%d",&choice);
        switch ( choice ){
        case 1:
            printf("You typed 1");
            break;
        case 2:
            core();
            break;
        case 3:
            printf("You typed 3");
            break;
        case 4:
            printf("You typed 4");
            break;
        case 5:
            exit(0);
            break;
        default:
            printf("You typed a wrong number !");
        }
    }
}

void ChoixDictionnaire(){
    int choice =0;
    char *menu[] = {
        " Francais ",
        " Anglais ",
        " Retour ",
        " Quitter ",
    };
    while (choice != 4) {
        printf("\033[2J\033[1;1H");
        header();
        chargeroptions(menu,4," Choix de langue ");
        scanf("%d",&choice);
        switch ( choice ){
            case 1:
                printf("You typed 1"); //FRANCAIS 
                ChoixDifficulte();
                break;
            case 2:
                printf("You typed 2"); //ANGLAIS
                ChoixDifficulte();
                break;
            case 3:
                printf("You typed 3"); //RETOUR DE 
                break;
            case 4:
                exit(0);
                break;
            default:
                printf("You typed a wrong number !");
        }
    }
}

void nouvellePartie(){

    int choice =0;
    char *menu[] = {
        " Partie contre ordinateur ",
        " Partie contre Joueur ",
        " Retour ",
        " Quitter ",
    };
    while (choice != 3) {
    printf("\033[2J\033[1;1H");
    header();
    chargeroptions(menu,4," Nouvelle Partie ");
    scanf("%d",&choice);
    switch ( choice ){
    case 1: //JOUER CONTRE ORDI
        ChoixDictionnaire();
        printf("You typed 1");
        break;
    case 2: //JOUER CONTRE JOUEUR
        printf("You typed 2");
        break;
    case 3: //RETOUR AU MENU PRINCIPALE
        break;
    case 4: //QUITTER
        exit(0);
        break;
    default:
        printf("You typed a wrong number !");
    }
    }
}

void commencerPartie(){
    int choice = 0;
    while (choice != 4) {
        char *menu[] = {" Commencer une nouvelle partie "," Charger une partie deja existante "," Aide en ligne"," Quitter "};
        printf("\033[2J\033[1;1H");
        header();
        chargeroptions(menu,4," MENU ");
        scanf("%d",&choice);
        switch ( choice ){
            case 1:
                nouvellePartie();
                break;
            case 2:
                printf("You typed 2");
                break;
            case 3:
                printf("You typed 3");
                break;
            case 4:
                printf("You typed 4");
                break;
            default:
                printf("You typed a wrong number !");
        }
    }
}
