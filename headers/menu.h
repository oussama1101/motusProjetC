#include <stdlib.h>
#include <stdio.h>
#include "headers/game.h"
#include <dirent.h>

void chargeroptions(char* liste[],int n,char* titre);
void ChoixDifficulte(UserPreferences *up);
void ChoixDictionnaire(UserPreferences *up);
void nouvellePartie();
void RegleDuJeu();
void listOfGames();
void menuPrincipale();