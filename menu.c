#include <stdlib.h>
#include <stdio.h>
#include "game.c"
#include <dirent.h>

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
        printf("\033[32m");printf(" %s",liste[i]);
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
    printf("\033[37m");printf(" pour continuer : ");
}

void ChoixDifficulte(UserPreferences *up){
    int choice =0;
    char *menu[] = {
        "Facile ",
        "Moyenne ",
        "Difficle ",
        "Retour ",
        "Quitter ",
    };
        printf("\033[2J\033[1;1H");
        header();
        chargeroptions(menu,5," Choix de difficulte ");
        scanf("%d",&choice);
        switch ( choice ){
        case 1:
            up->diff = FACILE;
            startGame(up);
            break;
        case 2:
            up->diff = MOYENNE;
            startGame(up);
            break;
        case 3:
            up->diff = DIFFICILE;
            startGame(up);
            break;
        case 4:
            break;
        case 5:
            exit(0);
            break;
        default:
            printf("You typed a wrong number !");
        }
    
}

void ChoixDictionnaire(UserPreferences *up){
    int choice =0;
    char *menu[] = {
        "Francais ",
        "Anglais ",
        "Retour ",
        "Quitter ",
    };
    
        printf("\033[2J\033[1;1H");
        header();
        chargeroptions(menu, 4, " Choix de langue ");
        scanf("%d", &choice);
        switch ( choice ){
            case 1: //FRANCAIS
                up->lang = FRANCAIS;
                ChoixDifficulte(up);
                break;
            case 2: //ANGLAIS
                up->lang = ANGLAIS;
                ChoixDifficulte(up);
                break;
            case 3: //RETOUR VERS NOUVELLE PARTIE
                break;
            case 4:
                exit(0);
                break;
            default:
                printf("You typed a wrong number !");
        }
    
}

void nouvellePartie(){
    UserPreferences *up = (UserPreferences*)malloc(sizeof(UserPreferences));
    int choice =0;
    char *menu[] = {
        "Partie contre ordinateur ",
        "Partie contre Joueur ",
        "Retour ",
        "Quitter ",
    };
    while (choice != 3) {
    printf("\033[2J\033[1;1H");
    header();
    chargeroptions(menu,4," Nouvelle Partie ");
    scanf("%d",&choice);
    switch ( choice ){
    case 1: //JOUER CONTRE ORDI
        up->vs = ORDINATEUR;
        ChoixDictionnaire(up);
        break;
    case 2: //JOUER CONTRE JOUEUR
        up->vs = JOUEUR;
        ChoixDictionnaire(up);
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
void listOfGames(){

    int choice = 0,i=1;
    DIR *d;
    struct dirent *dir;
    d = opendir("saves/");

    printf("\033[2J\033[1;1H");
    char *menu[50];
    menu[0] = "Retour";
    header();
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {   
            if(dir->d_name[0] != '.'){
            menu[i] = dir->d_name;
            i++;
            }
        }
        closedir(d);
    }
    chargeroptions(menu,i," Liste des sauvegardes ");
    do {
        scanf("%d",&choice);
    } while(choice > i);
    if(choice == 1){
        return;
    }
    char path[100] = "saves/";
    strncat(path, menu[choice-1], (int)strlen(menu[choice-1])+1);
    loadGame(path);
}

void RegleDuJeu(){
    int var=0;
    printf("\033[2J\033[1;1H");
    header();
    printf("\033[36m");printf("  +");
    printf("\033[37m");printf("----------------------------------------------------------");
    printf("\033[36m");printf("+\n");
    printf("\033[37m");printf("  |   ");
    printf("\033[36m");printf("N");
    printf("\033[37m");printf("   |");
    printf("\033[35m");printf(" Regles du jeu");
    printf("\033[37m");printf("\n");
    printf("\033[36m");printf("  +");
    printf("\033[37m");printf("----------------------------------------------------------");
    printf("\033[36m");printf("+\n");
    printf("\033[37m");
    printf("\tLe jeu repose sur la recherche de mots d'un nombre \n\tfixé de lettres. Un candidat propose un mot et doit \n\tépeler celui-ci.Le mot doit contenir le bon nombre \n\tde lettres et être correctement orthographié, sinon \n\til est refusé. Le mot apparaît alors sur une grille.");
    printf("\n\tLégende :\n\tCouleur blanche : Mauvaise lettre\n\tCouleur \033[31mrouge\033[37m : Lettre en mauvaise plac\n\tCouleur \033[32mverte\033[37m : Bonne lettre");
    printf("\033[36m");printf("\n  +");
    printf("\033[37m");printf("----------------------------------------------------------");
    printf("\033[36m");printf("+\n");
    printf("\033[34m");printf("  [");
    printf("\033[33m");printf("!");
    printf("\033[34m");printf("]");
    printf("\033[37m");printf("Tapez");
    printf("\033[34m");printf(" 1 ");
    printf("\033[37m");printf("pour revenir au menu principale du jeu : ");
    scanf("%d",&var);
    if(var == 1){
        return;
    }


}
void menuPrincipale(){
    int choice = 0;
    while (choice != 4) {
        char *menu[] = {
            "Commencer une nouvelle partie ",
            "Charger une partie deja existante ",
            "Aide en ligne",
            "Quitter "
        };
        printf("\033[2J\033[1;1H");
        header();
        chargeroptions(menu,4," MENU ");
        scanf("%d",&choice);
        switch ( choice ){
            case 1:
                nouvellePartie();
                break;
            case 2:
                listOfGames();
                break;
            case 3:
            //system("open http://www.google.com"); 
            RegleDuJeu();    
                       break;
            case 4:
                break;
            default:
                printf("You typed a wrong number !");
        }
    }
}
