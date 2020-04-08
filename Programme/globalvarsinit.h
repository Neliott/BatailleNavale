/*
 * Projet : Bataille Navale
 * Description : Une bataille navale en C dans le cadre MA-20 et ICT-431 du CPNV
 * Auteur : Eliott Jaquier
 * Ce script sert à initialiser les variables (globales) et tout ce qui doit se placer avant le lancement du main.c
*/

/*Définitions pré-build (Utile pour les tableaux) (Commencent avec une majuscule pour les différentier de variables)*/
#define MaxScoresDispalyed 100 //Le nombre maximum de scores affichés
#define GrildLenght 10 //La longueur de la grille de jeu (carrée)


/*CONSTANTES DE JEU*/
const int isEditor = 0; //Certaine fonctions seront remplacée pour marcher dans l'editeur
int isAudio = 1; //Activer ou désactiver l'audio
int isEffect = 1; //Activer ou désactiver les effets visuels
int isRapideLaunch= 0; //Activer ou désactiver la lancement rapide du jeu
const int enablePrintLogsInConsole = 0; //Certaine fonctions seront remplacée pour marcher dans l'editeur
const int linesMax = GrildLenght; //Détermination de l'aire de jeu (X)
const int colsMax = GrildLenght; //Détermination de l'aire de jeu (Y)


/*CONSTANTES - PERSONALISATION D'INTERFACE*/
const char gameConversion[GrildLenght]={'a','b','c','d','e','f','g','h','i','j'};
const char gameConversionMaj[GrildLenght]={'A','B','C','D','E','F','G','H','I','J'};
const char gameGrildPlouf[] = {" ○ "};
const char gameGrildTouche[] = {" ! "};
const char gameGrildCoule[] = {" × "};
const char gameGrildVertical[] = {"|"};
const char gameGrildHorizontal[]= {"_"};
const char gameGrildHorizontalMiddle[]= {"─"};
const char gameGrildCoinHautGauche[] = {"■"};
const char gameGrildCoinHautDroite[] = {"■"};
const char gameGrildCoinBasGauche[] = {"└"};
const char gameGrildCoinBasDroite[]  = {"┘"};


/*VARIABLES - PLATEAU DU JOUEUR*/
int gameGrildCoups = 0; //Nombre de coups joués
int gameGrild[GrildLenght][GrildLenght]; //Grille affichée à l'écran


/*VARIABLES - BEATEAUX (Cachée du joueur)*/
const int gameGrildBoatsNb = 5; //Nombres de bateaux
int gameGrildBoatsHit[5] = {0,0,0,0,0}; //Nombre de zones touchées par le joueur pour chaque bateaux
int gameGrildBoatsLenght[5] = {5,4,3,3,2};//Nombre de zones maximales par bateaux (Calculé pendant l'initialisation de la partie)
int gameGrildBoats[GrildLenght][GrildLenght];//La carte du niveau entier est ici (0 - eau, de 1 à 5 - un id de bateau)


/*Génériques de fonctions*/
void displayMainMenu(), setup(),setupGame(),displayHelp(),displayParameters(),renewParameters(),clear(),logAction(int typeEvent,char * texte),showGameGrild(),getRandomGame(),displayGame(),displayScores(),touchBoat(int line,int col),visualEvent(int event),endGame(),setScore(),playASound(int id);
int askChoiceMin(int min,int max),askChoiceChar();