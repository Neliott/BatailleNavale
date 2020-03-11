/*
 * Projet : Bataille Navale
 * Description : Une bataille navale en C dans le cadre MA-20 et ICT-114 du CPNV
 * Auteur : Eliott Jaquier
 * Version : 1.1.0 - Super Bark NOCOLORED Version (Finalisation de la 0.1)
 * Date : 11.03.2020
*/

#include <stdio.h> //Par défaut
#include <stdlib.h>
#include "windows.h" //Gérer les commandes console
#include "string.h"

/*#include <windowsx.h> //Système de console étendu
#include "time.h" //Gérer le temps
#include "math.h" //Gérer des maths avancés
 */


/*Génériques de fonctions*/
void displayMainMenu(), setup(),setupGame(),displayHelp(),clear(),showGameGrild(),displayGame(),displayScores(),touchBoat(int line,int col),visualEvent(int event),endGame(),setScore(),showScores(),drawer(int type,int espace);
int askChoiceMin(int min,int max),askChoiceChar();

/*CONSTANTES DE JEU*/
const int isEditor = 1; //Certaine fonctions seront remplacée pour marcher dans l'editeur
const int linesMax = 10; //Détermination de l'aire de jeu
const int colsMax = 10; //Détermination de l'aire de jeu

/*CONSTANTES - PERSONALISATION D'INTERFACE*/
const char gameConversion[10]={'a','b','c','d','e','f','g','h','i','j'};
const char gameConversionMaj[10]={'A','B','C','D','E','F','G','H','I','J'};
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
int gameGrild[10][10]; //Grille affichée à l'écran

/*VARIABLES - BEATEAUX (Cachée du joueur)*/
const int gameGrildBoatsNb = 5; //Nombres de bateaux
int gameGrildBoatsHit[5] = {0,0,0,0,0}; //Nombre de zones touchées par le joueur pour chaque bateaux
int gameGrildBoatsLenght[5] = {5,4,3,3,2};//Nombre de zones maximales par bateaux (Calculé pendant l'initialisation de la partie)
int gameGrildBoats[10][10] = /*LA PARTIE EST POUR l'INSTANT MARQUEE DANS LE CODE*/
{
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,5,5,0,0,0,0,0,0},
        {0,3,3,3,0,0,0,0,0,1},
        {0,4,4,4,0,0,0,0,0,1},
        {0,0,0,0,0,0,0,0,0,1},
        {0,0,0,0,0,0,0,0,0,1},
        {0,0,2,2,2,2,0,0,0,1}
};

/**
 * Description : Le lancement et la fermeture du programme est ici
 * @return Le code de fin du programme
 */
int main() {
    setup();
    displayScores();
    //displayMainMenu();
    return 0;
}

/**
 * Description : Cette fonction est executée lors du démarage du programme pour assurer son bon fonctionnement
 */
void setup(){
    SetConsoleOutputCP(CP_UTF8); //Les accents sont maintenant supportés
    if(!isEditor){
        SetConsoleTitle("Bataille Navale"); //Peut provoquer des erreurs dans la version sur CLION en affichant le contenu dans la console (ceci est maintenant protégé)
        //system("color 13");//69,67,14,73
    }else{
        printf("ATTENTION ! VERSION CLION ONLY ! NE PAS COMPILER EN DEHORS ! (Changer la constante isEditor)\n");
    }
    printf("\n");
    clear();
    //visualEvent(0);
}

/**
 * Description : Affiche le menu et traîte le choix de l'utilisateur
 */
void displayMainMenu(){
    clear();

    /*Affichage de l'entête*/
    if(isEditor){
        printf("----Menu---- \n");
    }else{
        //drawer(1,0);
    }
    printf("  \n");

    /*Affichage des choix disponibles*/
    printf("Bienvenue sur le jeu 'Bataille Navale' !\n");
    printf("(1) - Jouer \n");
    printf("(2) - Aide \n");
    printf("(3) - Scores\n");
    printf("(4) - Où nous trouver \n");
    printf("(5) - Quitter \n");
    printf(" \n");

    printf("Veuillez choisir une option : \n");

    /*Traîtement du choix*/
    switch (askChoiceMin(1,5)){
        case 1:
            setupGame();
            break;
        case 2:
            displayHelp();
            break;
        case 3:
            displayScores();
            break;
        case 4:
            system("explorer https://www.eliott.pro/liens.php");
            printf("Naviguateur non-trouvé");
            displayMainMenu();
            break;
        case 5:
            printf("Fermeture...\n");
            break;
        default:
            printf("Ceci n'est pas une option valide !\n");
            displayMainMenu();
            break;
    }
}

/**
 * Description : Affichage d'un menu d'aide expliquant les règles de la bataille navale
 */
void displayHelp(){
    clear();

    /*Affichage de l'entête*/
    if(isEditor){
        printf("----Aide---- \n");
    }else{
        //drawer(2,0);
    }

    /*Affichage des explications*/
    printf("  \n");
    printf("Bienvenue sur la bataille navale ! \n");
    printf("Le but est de toucher tout les bateaux en le moins de coups possibles. \n");
    printf("Indiquez une case pour envoyer un missile dessus. Vous recevrez le résultat de votre action : \n");
    printf("Plouf - %s - Vous n'avez touché aucun bateau. \n",gameGrildPlouf);
    printf("Touché - %s - Vous avez touché un bout d'un bateau. \n",gameGrildTouche);
    printf("Coulé - %s - Vous avez coulé un bateau entier. \n",gameGrildCoule);
    printf("  \n");

    system("pause");
    clear();
    displayMainMenu();
}

void displayScores(){//WIK
    printf("Scores :  \n");
    FILE* fichier = NULL;

    fichier = fopen("./gameassets/scores.bn", "r+");

    if (fichier != NULL)
    {
        //fscanf(fichier, "%d", &choixTemp);
        int positionPseu[10][6];
        int counter = 0;
        int line = 0;
        char prevChar;
        char actualChar;
        int pvCounter = 0;

        do {
            counter++;
            prevChar = actualChar;
            fseek(fichier, counter, SEEK_SET);
            actualChar = (char)fgetc(fichier);
            printf("%d : %c %c \n",counter,actualChar,prevChar);
            /*if(actualChar == ';'){
                pvCounter++;
                if(pvCounter%4 == 0){
                    positionPseu[line][5] = counter-1;
                    line++;
                }
                if(pvCounter%4 == 1){
                    printf("1\n");
                    positionPseu[line][0] = counter-1;
                }
                if(pvCounter%4 == 2){
                    printf("2\n");
                    positionPseu[line][1] = counter-1;
                    positionPseu[line][2] = counter+1;
                }
                if(pvCounter%4 == 3){
                    printf("3\n");
                    positionPseu[line][3] = counter-1;
                    positionPseu[line][4] = counter+1;
                }
            }*/
        } while(actualChar != prevChar);

        for(int i1= 0;i1 < 10;i1++){
            for(int i2= 0;i2 < 6;i2++){
                printf("%d",positionPseu[i1][i2]);
            }
        }
        /*char carr;
        do {
            carr = (char) fgetc(fichier);
            if (carr == ';') {
                printf("; Actuellement : %d Pseudo : %s \n", inc, pseudo[0]);
                if (inc == 1) {
                    couts = atoi(coutsNoConversion);
                }
                inc++;
                if (inc == 3) {
                    printf("Pseudo : %s Couts %d Date : %s \n", pseudo[0], couts, date);
                    inc = 0;
                    pseudo = "RIEN";
                    coutsNoConversion = "RIEN";
                    date = "RIEN";
                }
            } else {
                if (inc == 0) {
                    printf("COUTS 0\n");
                    strncat(pseudo[0], &carr, 1);
                }
                if (inc == 1) {
                    printf("COUTS 1\n");
                    char*ccc = "";
                    strncat(ccc, &carr, 1);
                }
                if (inc == 2) {
                    //strncat(date, &carr, 1);
                }
            }

        } while(carr != EOF);
        printf("%s",pseudo);*/
        fclose(fichier);

    }else{
        printf("NOT FOUND");
    }
}

/**
 * Description : Fonction s'executant au démarage d'une partie pour remettre des variables de précédantes parties à leur état initial.
 */
void setupGame(){
    gameGrildCoups = 0;//Le joueur n'a pas encore joué de coups

    /*Remise à 0 de la grille du joueur*/
    for(int lines=0;lines<linesMax;lines++){
        for(int cols=0;cols<colsMax;cols++){
            gameGrild[lines][cols] = 0;
        }
    }
    /*Remise à 0 du nombre de zone par bateaux touchées*/
    for(int i=0;i<gameGrildBoatsNb;i++){
        gameGrildBoatsHit[i] = 0;
    }

    /*Calculation du nombre de zones totales par bateau*/
    for(int i=0;i<gameGrildBoatsNb;i++){ //Vidage de précédentes valeurs
        gameGrildBoatsLenght[i] = 0;
    }
    for(int lines=0;lines<linesMax;lines++){ //Recalculation selon la grille des bateaux
        for(int cols=0;cols<colsMax;cols++){
            if(gameGrildBoats[lines][cols] != 0){
                gameGrildBoatsLenght[gameGrildBoats[lines][cols]-1] ++;
            }
        }
    }
    displayGame();
}

/**
 * Description : Fonction s'éxecutant à chaques tours durant une partie
 */
void displayGame(){
    /*Valeurs où le joueur va décider d'envoyer un missile*/
    int lineAttack = -1;
    int colAttack = -1;

    int isCaseValid = 0;//Si la case que le joueur a choisi n'a pas déjà été jouée

    showGameGrild();//Affichage de la grille de jeu (joueur)
    do {
        printf("Entrez la colone à attaquer :");
        colAttack = askChoiceChar(); //Le scanf seulement n'étant pas suffisant pour cette requête, une fonction spéciale de traîtement a été créée (Demande à l'utilisateur et transforme son choix en une valeur INT utilisable pour tableau)

        /*Remise au même état que si la précédante commande n'avait pas existé (Plus jolis et prends moins de place)*/
        showGameGrild();

        printf("Entrez la ligne à attaquer :");
        lineAttack = askChoiceMin(1, 10)-1; //Le scanf seulement n'étant pas suffisant pour cette requête, une fonction spéciale a été créée. Si le MIN ou le MAX n'est pas respecté, elle tourne en boucle jusqu'à ce que le joueur entre une valeur correcte (-1 à cause des tableaux)

        /*Remise au même état que si la précédante commande n'avait pas existé (Plus jolis et prends moins de place)*/
        showGameGrild();

        if(gameGrild[lineAttack][colAttack] == 0){ //Si la case est vide
            isCaseValid = 1;
            gameGrildCoups++;
            touchBoat(lineAttack,colAttack); //La case est touchée avec le valeurs saisies pas le joueur
        }else{
            printf("Veuillez entrer une case qui n'a pas déjà été jouée.\n");
        }
    }while(!isCaseValid); //Tourne tant que le joueur saisi une case qui a déja été jouéee
}

/**
 * Description : Une fonction qui va traîter diverses sortes d'intéraction avec une case désignée.
 * @param line : La ligne cible du tir
 * @param col : La colone cible du tir
 */
void touchBoat(int line,int col){
    if(gameGrildBoats[line][col] != 0){ //Si un bateau est sur la case
        int boatType = gameGrildBoats[line][col]-1; //Stockage de l'id du bateau se trouvant sur la case

        gameGrild[line][col] = 2;//Désigne l'affichage d'un caractère indiquant qu'il y a un bateau sur la grille de jeu
        gameGrildBoatsHit[boatType] ++;//Le bateau que le jouer à touché a plus de zones touchées qu'avant

        if(gameGrildBoatsHit[boatType] == gameGrildBoatsLenght[boatType]){ //Si le bateau est coulé (qu'il y a autant de zones touchées que de zones totales)
            /*Affichage de retours pour le joueur*/
            printf("Coulé !");

            for(int lines=0;lines<linesMax;lines++){//Le bateau qui vient de couler sera maintenant affiché différemement sur la carte du joueur
                for(int cols=0;cols<colsMax;cols++){
                    if(gameGrildBoats[lines][cols] == boatType+1){ //Recherche de toutes les cases avec le même ID
                        gameGrild[lines][cols] = 3;
                    }
                }
            }

            /*Maintenant qu'un bateau est coulé, cela peut être la fin du jeu. Il faut donc calculer le nombres de bateaux coulés depuis le début de la partie*/
            int bateauxTouche = 0;//Le nobmre de bateaux touchés (coulés)

            for(int boatNumber = 0;boatNumber<gameGrildBoatsNb;boatNumber++){//Scan de tous les bateaux pour voir si il sont coulés
                if(gameGrildBoatsHit[boatNumber] == gameGrildBoatsLenght[boatNumber]){//Si le bateau est coulé (qu'il y a autant de zones touchées que de zones totales)
                    bateauxTouche++;
                }
            }

            /*Actions en fontion du résultat du nombre de bateaux coulés*/
            if(bateauxTouche == gameGrildBoatsNb){//Si il y a autant de bateaux coulés que de bateaux max
                /*le joueur a gagné*/
                printf("\nFin de la partie !");
                endGame();
            }else{
                /*La partie continue*/
                //visualEvent(3);
                Sleep(1000);
                displayGame();
            }
        }else{
            /*Le bateau est juste touché*/
            printf("Touché !");
            //visualEvent(2);
            Sleep(1000);
            displayGame();
        }
    }else{
        /*Il n'y a pas de bateaux*/
        gameGrild[line][col] = 1; //Cette case sera maintenant affiché différemement sur la carte du joueur car elle a été découverte
        printf("Plouf !");
        //visualEvent(1);
        Sleep(1000);
        displayGame();
    }
}

/**
 * Description : Fonction s'éxecutant à la fin d'une partie
 */
void endGame(){
    showGameGrild();
    //visualEvent(4);
    printf("PARTIE TERMINEE EN %d COUPS !",gameGrildCoups);
    system("pause");

    clear();
    setScore(); //Fonction non-disponible
    displayScores();
}

/**
 * Description : Affiche la grille du joueur de la bataille navale
 */
void showGameGrild(){
    clear();

    /*Caractères de A à J*/
    printf("   ");
    for(int i = 0;i < (colsMax);i++){
        printf("  %c ",gameConversionMaj[i]); //Affichage de toutes les lettre en majuscules succésivement
    }

    printf("\n");

    /*Véritable première ligne du tableau*/
    printf("   ");//Espace de syncronisation (pour que le rendu soit jolis
    // )
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
                printf("%s",gameGrildVertical);//Fermeture de l'extremité droite du tableau (séparateur vertical)

            }

        }else{
            printf("%2d ",(line/2)+1);
            for (int col = 0; col < colsMax; col++) {//Se répéte le nombre de colones qu'il y a dans les données
                int celluleActuelle = gameGrild[line / 2][col];
                switch (celluleActuelle){ //Détermine de quelle façon la cellule va être affichée (plouf,touché,coulé)
                    case 1:
                        printf("%s%s",gameGrildVertical,gameGrildPlouf);
                        break;
                    case 2:
                        printf("%s%s",gameGrildVertical,gameGrildTouche);
                        break;
                    case 3:
                        printf("%s%s",gameGrildVertical,gameGrildCoule);
                        break;
                    default:
                        printf("%s   ",gameGrildVertical);
                        break;
                }
            }
            printf("%s",gameGrildVertical);//Fermeture de l'extremité droite du tableau (séparateur vertical)

        }

        printf("\n");//La ligne a été entièrement affichée à ce stade. Il suffit juste d'un retour à la ligne.
    }
}

/**
 * Description : Efface le contenu de la fenêtre
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
*  Description : Permet de mieux traîter les choix que la manière native avec scanf seulement (vidage du scanf, gestion de problèmes et limitation de la saisie entre Min et Max)
*/
int askChoiceMin(int min,int max){
    int choice = min-1;//Si le scanf échoue, cette variable gardera cet état

    scanf("%d", &choice);//Si l'utilisateur a entré une lettre, le scanf va la garder en buffer pour la prochaine fois.

    /*Vidage du scanf si un problème précédant est survenu*/
    int voider; //La variable la plus temporaire que je n'ai jamais vue.
    while((voider=getchar()) != EOF && voider != '\n'); //Li un caractère jusqu'à ce que le "scanf" ne lui envoye plus rien d'interresant

    if(!(choice >= min && choice <= max)){
        printf("\nVeuillez taper un nombre de %d à %d : ",min,max);
        choice = askChoiceMin(min,max);
    }
    printf("\n");
    return choice;
}

/**
 * Idem que askChoiceMin mais avec les caractères converti en décimal à l'aide d'une grille
 * @return
 */
int askChoiceChar(){
    int isCharFounded = 0;
    char choice = 0;
    int charConverted = 0;

    scanf("%c", &choice);//Si l'utilisateur a entré trop de lettres, le scanf va garderles lettres en buffer pour la prochaine fois.

    /*Vidage du scanf si un problème précédant est survenu*/
    int voider; //La variable la plus temporaire que je n'ai jamais vue.
    while((voider=getchar()) != EOF && voider != '\n');//Li un caractère jusqu'à ce que le "scanf" ne lui envoye plus rien d'interresant

    for(int i= 0;i<colsMax;i++){
        if(gameConversion[i] == choice || gameConversionMaj[i] == choice){ //Regarde dans la base de chars si il y a une correspondance majuscule ou minuscule
            isCharFounded = 1;
            charConverted = i;
        }
    }
    printf("\n");
    if(!isCharFounded){
        printf("Veuuillez taper un caractère de A à J :");
        charConverted = askChoiceChar();
    }
    return charConverted;
}

/*---- FONCTIONS DE LA VERSION 1 - NON-FONCTIONNEL ----*/
void setScore(){

}