/*
 * Projet : Bataille Navale
 * Description : Une bataille navale en C dans le cadre MA-20 et ICT-114 du CPNV
 * Auteur : Eliott Jaquier
 * Version : 1.0.0 (First release)
 * Date : 04.03.2020
*/

#include <stdio.h>
#include "windows.h"
#include "time.h"
#include "math.h"

/*Les génériques de fonctions*/
void displayMainMenu(), setup();

/**
 * Description : Le lancement et la fermeture du programme sont ici (seulement éxecution de fonctions)
 * @return
 */
int main() {
    setup();
    displayMainMenu();
    return 0;
}

/**
 * Description : Cette fonction est executée lors du démarage du programme pour assurer son bon fonctionnement
 */
void setup(){
    SetConsoleOutputCP(CP_UTF8); //Les accents sont maintenant supportés
    SetConsoleTitle("Bataille Navale"); //Peut provoquer des erreurs dans la version sur CLION en affichant le contenu dans la console
    printf("\n");
}

/**
 * Description : Affichage du menu ainsi que le traîtement du choix
 */
void displayMainMenu(){
    int choice = 0;

    printf("----Menu---- \n");
    printf("  \n");
    printf("Bienvenue sur le jeu 'Bataille Navale' !\n");
    printf("(1) - Jouer \n");
    printf("(2) - Aide \n");
    printf("(3) - Scores \n");
    printf("(4) - Quitter \n");
    printf(" \n");

    /*printf("Veuillez choisir une option : \n");
    scanf("%d",&choice);*/
}