/*
 * Projet : Bataille Navale
 * Description : Une bataille navale en C dans le cadre MA-20 et ICT-114 du CPNV
 * Auteur : Eliott Jaquier
 * Version : 1.0.1 (Affichage du menu d'aide)
 * Date : 04.03.2020
*/

#include <stdio.h>
#include "windows.h"
#include "time.h"
#include "math.h"

/*Les génériques de fonctions*/
void displayMainMenu(), setup(),displayHelp();

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
    printf("(1) - Jouer - Non disponible \n");
    printf("(2) - Aide \n");
    printf("(3) - Scores - Non disponible\n");
    printf("(4) - Quitter \n");
    printf(" \n");

    printf("Veuillez choisir une option : \n");
    scanf("%d",&choice);

    switch (choice){
        case 1:
        case 3:
            printf("Cette opération n'est pas disponible pour le moment.\n");
            displayMainMenu();
            break;
        case 4:
            printf("Bye Bye !\n");
            break;
        case 2:
            displayHelp();
            break;
        default:
            printf("Ceci n'est pas une option valide !\n");
            displayMainMenu();
            break;
    }
}

/**
 * Description : Affichage d'un menu d'aide
 */
void displayHelp(){
    printf("----Aide---- \n");
    printf("  \n");
    printf("Bienvenue sur la bataille navale ! \n");
    printf("Le but est de toucher tout les bateaux en le moins de coups possibles. \n");
    printf("Indiquez une case pour envoyer un missile dessus. Vous recevrez le résulata de votre action : \n");
    printf("1. Plouf (un rond s'affiche) - Vous n'avez touché aucun bateau. \n");
    printf("2. Touché (une croix) - Vous avez touché un bout d'un bateau. \n");
    printf("3. Coulé (une croix) - Vous avez coulé un bateau entier. \n");
    printf("  \n");

    system("pause");
    displayMainMenu();
}