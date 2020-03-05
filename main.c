/*
 * Projet : Bataille Navale
 * Description : Une bataille navale en C dans le cadre MA-20 et ICT-114 du CPNV
 * Auteur : Eliott Jaquier
 * Version : 1.0.4 - Water Version (Affichage du menu d'aide avancé)
 * Date : 05.03.2020
*/

#include <stdio.h>
#include "windows.h"
#include "time.h"
#include "math.h"
#include "ctype.h"

/*Génériques de fonctions*/
void displayMainMenu(), setup(),displayHelp(),clear();
int askChoiceMin(int min,int max);

/*CONSTANTES DE JEU*/
const int isEditor = 1; //Certaine fonctions seront remplacée pour marcher dans l'editeur
/*int gameGril[10][10] =
{
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0}
};*/

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
    if(!isEditor){
        SetConsoleTitle("Bataille Navale"); //Peut provoquer des erreurs dans la version sur CLION en affichant le contenu dans la console (ceci est maintenant protégé)
    }else{
        printf("ATTENTION ! VERSION CLION ONLY ! NE PAS COMPILER EN DEHORS ! (Changer la constante isEditor)\n");
    }
    printf("\n");
}

/**
 * Description : Affichage du menu ainsi que le traîtement du choix
 */
void displayMainMenu(){
    printf("----Menu---- \n");
    printf("  \n");
    printf("Bienvenue sur le jeu 'Bataille Navale' !\n");
    printf("(1) - Jouer - Non disponible \n");
    printf("(2) - Aide \n");
    printf("(3) - Scores - Non disponible\n");
    printf("(4) - Quitter \n");
    printf(" \n");

    printf("Veuillez choisir une option : \n");

    switch (askChoiceMin(1,4)){
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
    printf("Plouf (un rond) - Vous n'avez touché aucun bateau. \n");
    printf("Touché (une croix) - Vous avez touché un bout d'un bateau. \n");
    printf("Coulé (une croix) - Vous avez coulé un bateau entier. \n");
    printf("  \n");

    system("pause");
    clear();
    displayMainMenu();
}

/**
 * Efface le contenu de la fenêtre
 */
void clear(){
    if(!isEditor){
        system("cls");
    }else{
        for(int i=0;i<=10;i++){
            printf("\n");
        }
    }
}

/**
*  Permet de mieux traîter les choix que la manière native scanf seulement
*/

int askChoiceMin(int min,int max){
    /*char choice[32] = "";
    do{
        scanf("%31s", &choice);
        printf("\n");
        if(choice[0] >= min && choice[0] <= max){
            return choice[0];
        }else{
            printf("Veuillez taper un nombre de %d à %d : \n",min,max);
        }
    }while (choice[0] < min || choice[0] > max);*/
    int choice = 0;
    scanf("%d", &choice)
    return choice;
}