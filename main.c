/*
 * Projet : Bataille Navale
 * Description : Une bataille navale en C dans le cadre MA-20 et ICT-114 du CPNV
 * Auteur : Eliott Jaquier
 * Version : 1.0.7 - Water Version (Création de la grille de jeu)
 * Date : 06.03.2020
*/

#include <stdio.h>
#include "windows.h"
#include <windowsx.h>
#include <mmsystem.h>

#include "time.h"
#include "math.h"
#include "ctype.h"

/*Génériques de fonctions*/
void displayMainMenu(), setup(),setupGame(),displayHelp(),clear(),showGameGrild(),displayGame();
int askChoiceMin(int min,int max),askChoiceChar();

/*CONSTANTES DE JEU*/
const int isEditor = 1; //Certaine fonctions seront remplacée pour marcher dans l'editeur
const int nbBoats = 5;
const int linesMax = 10;
const int colsMax = 10;

const char gameConversion[10]={'a','b','c','d','e','f','h','i','j','k'};
const char gameConversionMaj[10]={'A','B','C','D','E','F','H','I','J','K'};
const char gameGrildCoule[] = {"O"};
const char gameGrildTouche[] = {"X"};
const char gameGrildVertical[] = {"|"};
const char gameGrildHorizontal[]= {"_"};
const char gameGrildHorizontalMiddle[]= {"─"};
const char gameGrildCoinHautGauche[] = {"■"};
const char gameGrildCoinHautDroite[] = {"■"};
const char gameGrildCoinBasGauche[] = {"└"};
const char gameGrildCoinBasDroite[]  = {"┘"};

int gameGrildCoups = 0;
int gameGrild[10][10] =
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
};
int gameGrildBoatsLenght[5] = {3,4,2,3,5};
int gameGrildBoats[10][10] =
{
        {0,1,1,1,0,0,0,0,0,0},
        {0,0,0,0,2,0,3,3,0,0},
        {0,0,0,0,2,0,0,0,0,0},
        {0,0,0,0,2,0,0,0,0,0},
        {0,0,0,0,2,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,5},
        {0,0,0,0,0,0,0,0,0,5},
        {0,0,0,0,0,0,0,0,0,5},
        {0,0,0,0,0,0,0,0,0,5},
        {0,0,4,4,4,0,0,0,0,5}
};

/**
 * Description : Le lancement et la fermeture du programme sont ici (seulement éxecution de fonctions)
 * @return
 */
int main() {
    setup();
    displayMainMenu();
    system("pause");
    return 0;
}

/**
 * Description : Cette fonction est executée lors du démarage du programme pour assurer son bon fonctionnement
 */
void setup(){
    SetConsoleOutputCP(CP_UTF8); //Les accents sont maintenant supportés
    if(!isEditor){
        SetConsoleTitle("Bataille Navale"); //Peut provoquer des erreurs dans la version sur CLION en affichant le contenu dans la console (ceci est maintenant protégé)
        system("color 13");//69,67,14,73
    }else{
        printf("ATTENTION ! VERSION CLION ONLY ! NE PAS COMPILER EN DEHORS ! (Changer la constante isEditor)\n");
    }
    printf("\n");
    clear();
}

void setupGame(){
    gameGrildCoups = 0;
    for(int lines=0;lines<linesMax;lines++){
        for(int cols=0;cols<colsMax;cols++){
            gameGrild[lines][cols] = 0;
        }
    }
    displayGame();
}
/**
 * Description : Affichage du menu ainsi que le traîtement du choix
 */
void displayMainMenu(){
    clear();
    printf("----Menu---- \n");
    printf("  \n");
    printf("Bienvenue sur le jeu 'Bataille Navale' !\n");
    printf("(1) - Jouer - Non terminé \n");
    printf("(2) - Aide \n");
    printf("(3) - Scores - Non disponible\n");
    printf("(4) - Quitter \n");
    printf(" \n");

    printf("Veuillez choisir une option : \n");

    switch (askChoiceMin(1,4)){
        case 1:
            setupGame();
            break;
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
    clear();
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
void displayGame(){
    int lineAttack = -1;
    int colAttack = -1;
    clear();
    showGameGrild();
    printf("Entrez la ligne à attaquer :");
    lineAttack = askChoiceMin(1,10);
    printf("\nEntrez la colone à attaquer :");
    colAttack = askChoiceChar();
    printf("\n");
}
/**
 * Affiche la grille de la bataille navale
 */
void showGameGrild(){
    clear();

    /*Première ligne*/
    printf("   ");
    for(int i = 0;i < (colsMax);i++){
        printf("  %c ",gameConversionMaj[i]); //Affichage de traîts
    }

    printf("\n");

    printf("   ");
    printf("%s",gameGrildCoinHautGauche);//Affichage cu Coin gauche
    for(int i = 0;i < (colsMax*3)+(colsMax-1);i++){
        printf("%s",gameGrildHorizontal); //Affichage de traîts
    }

    printf("%s",gameGrildCoinHautDroite); //Affichage du Coin Droite
    printf("\n");

    /*Autres lignes*/
    for(int line = 0;line < linesMax*2; line++){ //Se répéte à chaque ligne (A double pour une ligne/2 d'affichage)
        if((line%2)!=0){ //Affichage de lignes décoratives une ligne sur deux
            printf("   ");
            if(line+1 == linesMax*2){ //Affichage spécial pour la dernière ligne

                printf("%s",gameGrildCoinBasGauche);//Affichage du coin gauche
                for(int colsALineNow = 0;colsALineNow < (colsMax*3)+(colsMax-1);colsALineNow++){
                    printf("%s",gameGrildHorizontalMiddle);//Affichage d'une barre au milleu pour correspondre aux caractères des coins
                }
                printf("%s",gameGrildCoinBasDroite);//Affichage du coin droite

            }else{

                for(int colsALineNow = 0;colsALineNow < colsMax;colsALineNow++){//Se répéte le nombre de colones qu'il y a dans les données
                    printf("%s",gameGrildVertical);//Affichage d'un séparateur de colones
                    for(int i = 0;i < 3;i++){
                        printf("%s",gameGrildHorizontal);//Affichage de caractères horizontaux afin de créer une ligne
                    }
                }
                printf("%s",gameGrildVertical);//Affichage d'un séparateur de colones

            }

        }else{
            printf("%2d ",(line/2)+1);
            for (int col = 0; col < colsMax; col++) {//Se répéte le nombre de colones qu'il y a dans les données
                int celluleActuelle = gameGrild[line / 2][col];
                switch (celluleActuelle){ //Détermine de quelle façcon la cellule va être affichée
                    case 1:
                        printf("%s %s ",gameGrildVertical,gameGrildCoule);
                        break;
                    case 2:
                        printf("%s %s ",gameGrildVertical,gameGrildTouche);
                        break;
                    default:
                        printf("%s   ",gameGrildVertical);
                        break;
                }
            }
            printf("%s",gameGrildVertical);

        }

        printf("\n");//La ligne a été entièrement affichée à ce stade. Il suffit juste d'un retour à la ligne.
    }
}

/**
 * Efface le contenu de la fenêtre
 */
void clear(){
    if(isEditor == 0){
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
    int choice = min-1;//Si le scanf échoue, cette variable gardera cet état

    scanf("%d", &choice);

    int voider;
    while((voider=getchar()) != EOF && voider != '\n');

    if(!(choice >= min && choice <= max)){
        printf("\nVeuillez taper un nombre de %d à %d : ",min,max);
        askChoiceMin();
    }
    printf("\n");
    return choice;
}
/**
 * Idel que askChoiceMin mais avec les caractères converti en décimal à l'aide d'une grille
 * @return
 */
int askChoiceChar(){
    int isCharFounded = 0;
    char choice = 0;
    int charConverted = 0;

    scanf("%c", &choice);

    int voider;
    while((voider=getchar()) != EOF && voider != '\n');

    for(int i= 0;i<colsMax;i++){
        if(gameConversion[i] == choice || gameConversionMaj[i] == choice){
            isCharFounded = 1;
            charConverted = i+1;
        }
    }
    printf("\n");
    if(!isCharFounded){
        printf("CECI N'EST PAS UNE OPTION DISPONIBLE ! \n");
        charConverted = askChoiceChar();
    }
    return charConverted;
}