/*
 * Projet : Bataille Navale
 * Description : Une bataille navale en C dans le cadre MA-20 et ICT-114 du CPNV
 * Auteur : Eliott Jaquier
 * Version : 1.4.1 - Pixelated Boat Style Version (Mise en place des couleurs et des sons)
 * Date : 27.03.2020
*/
/*Bibliothèques par défaut*/
#include <stdio.h>
#include <stdlib.h>
#include "windows.h" //Gérer les commandes console
#include "string.h" //Ajoute quelques fonctions utiles pour les tableaux de char
#include <time.h> //Le système servant pour la date
#include <dirent.h>
#include <mmsystem.h>
#include <windowsx.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dos.h>
#include <conio.h>
/*Bibliothèques du jeu*/
#include "globalvarsinit.h" //Le isEditor et isAudio ont été déplacé ici
#include "drawer.c"
#include "soundsystem.c"
#include "visualevents.c"

/**
 * Description : Le lancement et la fermeture du programme est ici
 * @return Le code de fin du programme
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
    logAction(1,"Lancement du jeu");
    SetConsoleOutputCP(CP_UTF8); //Les accents sont maintenant supportés
    if(!isEditor){
        SetConsoleTitle("Bataille Navale"); //Peut provoquer des erreurs dans la version sur CLION en affichant le contenu dans la console (ceci est maintenant protégé)
        system("mode con: cols=180 lines=50");
    }else{
        printf("ATTENTION !");
        Sleep(200);
        printf(" VERSION CLION - EDITEUR ONLY !");
        Sleep(200);
        printf(" NE PAS EXECUTER EN DEHORS DU MODE INTEGRE de CLION! ");
        Sleep(200);
        printf("(Changer la constante isEditor)\n");
        Sleep(500);
    }
    /*Création des dossiers requis pour commencer le jeu*/
    logAction(1,"Création des dossiers requis au démarage");
    mkdir("maps");
    mkdir("gameassets");
    DIR* dir = opendir("sounds");
    if (!dir) {//L'utilisateur n'a pas de sons
        isAudio = 0;
        logAction(1,"Aucun audio detecté.");
        if(!isEditor){//Si l'utilisateur n'a pas de sons et qu'il est en mode console,
            printf("Bienvenue sur la bataille navale ! Dans l'état actuel, vous pouvez lancer l'application mais vous ne pourrez pas profiter de tous ces avantages ! Si vous désirez avoir une expérience optimale, veuillez ajouter le dossier 'sounds' avec tout son contenu pris depuis github. \n");
            printf("SI VOUS AVEZ AJOUTE LE DOSSIER ET QUE VOUS REVOYEZ CETTE FENETRE, CONTACTEZ LE DEVELOPPEUR. (Ou changez l'état par défaut de la variable isAudio à 1 dans le fichier main.c)\n");
            printf("Que voulez-vous faire ?\n");
            printf("1. Je veux jouer sans les sonds (expérience non-optimale)\n");
            printf("2. Ouvrir le github du projet et fermer l'application\n");
            int choixOpener = askChoiceMin(1,2);
            if(choixOpener == 2){//Si l'utilisateur désire avoir accès au github pour prendre le dossier des sonds.
                system("explorer https://github.com/EliottJaquierCPNV/BatailleNavale");
                logAction(0,"Le joueur a voulu quitter l'application et aller sur github pour télecharger les sons du projet.");
                exit(1);
            }
        }
    }
    printf("\n");
    clear();
    visualEvent(0);
}

/**
 * Description : Affiche le menu et traîte le choix de l'utilisateur
 */
void displayMainMenu(){
    system("color 1B");
    logAction(2,"Affichage du menu");
    clear();
    playASound(0);
    playASound(2);
    playASound(3);

    /*Affichage de l'entête*/
    if(isEditor){
        printf("----Menu---- \n");
    }else{
        drawer(1,0);
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
            displayMainMenu();
            break;
        case 5:
            playASound(0);
            logAction(1,"Fin du jeu sans erreur");
            printf("Fermeture...\n");
            break;
        /*case 6:
            setScore();
            displayMainMenu();
            break;*/
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
    playASound(3);
    logAction(2,"Affichage de l'aide");
    clear();

    /*Affichage de l'entête*/
    if(isEditor){
        printf("----Aide---- \n");
    }else{
        drawer(2,0);
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
    displayMainMenu();
}
/**
 * Description : Une fonction qui stocke le dernier score fait par le joueur dans un fichier
 */
void setScore(){
    logAction(3,"Définition du score");
    clear();

    /*Affichage de l'entête*/
    if(isEditor){
        printf("----Scores---- \n");
    }else{
        drawer(4,0);
    }

    /*Récupération du pseudo*/
    logAction(3,"Demande d'un pseudo");
    char pseudo[63];
    int isValidPseudo;
    do{
        isValidPseudo = 1;
        printf("Veuillez entrer un pseudo : \n");
        scanf("%63s", &pseudo);
        for(int i = 0;i<strlen(pseudo) ;i++){
            if(pseudo[i] == ';' && isValidPseudo == 1){
                isValidPseudo = 0;
                printf("VOUS NE POUVEZ PAS AVOIR DE PSEUDO CONTENANT UN ; !\n");
                logAction(3,"Le pseudo contient un ;");
            }
        }
        if(strlen(pseudo) < 3 && isValidPseudo == 1){
            isValidPseudo = 0;
            printf("VOTRE PSEUDO DOIT ETRE ENTRE 3 ET 64 CARACTERES !\n");
            logAction(3,"Le pseudo est plus petit que 3 caractères");
        }
    } while(isValidPseudo == 0);

    /*Vidage du scanf si il y a un débordement*/
    int voider; //La variable la plus temporaire que je n'ai jamais vue.
    while((voider=getchar()) != EOF && voider != '\n'); //Li un caractère jusqu'à ce que le "scanf" ne lui envoye plus rien d'interresant

    /*Récupération de la date*/
    time_t t = time(NULL); //https://stackoverflow.com/questions/1442116/how-to-get-the-date-and-time-values-in-a-c-program
    struct tm tm = *localtime(&t);//Prise de l'instance de l'heure locale dans une structure

    /*Récupération du score*/
    int score = gameGrildCoups; //Le système de score sera plus poussé pas la suite

    /*Enregistrement du score*/
    logAction(1,"Enregistrement du score");
    mkdir("gameassets");//Création du dossier (Au cas ou il ne le serait plus - supprimé entre temps)

    /*Ouverture du fichier*/
    FILE* fichier = NULL;
    fichier = fopen("./gameassets/scores.bn", "r+");//Ouverture du fichier dans le mode LECTURE/ECRITURE

    if(fichier!= NULL){ //Si le fichier existe
        int nbLines = 0;//Nombre de lignes du fichier
        char lines[MaxScoresDispalyed][128]; //Le contenu du fichier lignes par lignes

        /*Vidage de tous les caractères précédemment stocké dans la mémoire*/
        for(int i = 0;i<MaxScoresDispalyed;i++){
            for(int leng = 0;leng<128;leng++){
                lines[i][leng] = ' ';
            }
        }

        /*Récupération du nombre de lignes du fichier et séparation des lignes dans un tableau à 2 dimenstions*/
        while(fgets(lines[nbLines], strlen(lines[nbLines]), fichier))
        {
            if(nbLines < MaxScoresDispalyed-1){
                lines[nbLines][strlen(lines[nbLines]) - 1] = '\0';
                nbLines++;
            }
        }
        fclose(fichier);//Fermeture du fichier

        /*Effacement du contenu du fichier*/
        FILE *fp = fopen("./gameassets/scores.bn", "w"); //Ce mode efface toutes les lignes au lancement
        fclose(fp);//Fermeture du fichier
        FILE* fp3 = NULL;
        fp3 = fopen("./gameassets/scores.bn", "r+"); //Ouverture du fichier dans le mode LECTURE/ECRITURE

        rewind(fp3);//Retour au début du fichier
        fprintf(fp3, ";%s;%d;%d.%02d.%02d - %02d:%02d;\n", pseudo, gameGrildCoups, tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min);//Ecriture de la nouvelle ligne

        /*Ecriture de tuotes les anciennes lignes*/
        for(int i = 0; i < nbLines; ++i) {
            fprintf(fp3, "%s\n",lines[i]);
        }

        fclose(fp3);//Fermeture du fichier
    }else{
        printf("Fichier non-trouvé ! Création.");
        logAction(1,"Le fichier n'est pas trouvé. Création...");
        fclose(fichier);

        /*Création d'un nouveau fichier*/
        FILE* fichier2 = NULL;
        fichier2 = fopen("./gameassets/scores.bn", "w"); //Ouverture du fichier dans le mode ECRITURE (Créer automatiquement un fichier)
        fprintf(fichier2, ";%s;%d;%d.%02d.%02d -  %02d:%02d;\n", pseudo, gameGrildCoups, tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min);
        fclose(fichier2);
    }
    logAction(1,"Score enregistré dans le fichier avec succès !");
    system("pause");
}

/**
 * Description : Affichage des derniers scores depuis un fichier externe
 */
void displayScores(){
    playASound(3);
    logAction(2,"Affichage des scores");
    clear();

    /*Affichage de l'entête*/
    if(isEditor){
        printf("----Scores---- \n");
    }else{
        drawer(4,0);
    }
    printf("\n");

    FILE* fichier = NULL;
    logAction(1,"Mise en place du dossier");
    mkdir("gameassets");
    logAction(1,"Ouverture du fichier");
    fichier = fopen("./gameassets/scores.bn", "r+");//Ouverture du fichier dans le mode LECTURE/ECRITURE

    if(fichier!= NULL){//Si le fichier existe
        logAction(1,"Fichier de scores trouvé");
        int nbLines = 0; //Nombres de lignes dans le fichier
        char lines[MaxScoresDispalyed][128];//Le contenu du fichier ligne par ligne

        //Variables pour la séparation de la date, des points et des pseudos depuis les lignes
        char* names[MaxScoresDispalyed];
        char* date[MaxScoresDispalyed];
        char* pointS[MaxScoresDispalyed];

        /*Vidage de tous les caractères précédemment stocké dans la mémoire*/
        logAction(1,"Initialisation des tableaux");
        for(int i = 0;i<MaxScoresDispalyed;i++){
            for(int leng = 0;leng<128;leng++){
                lines[i][leng] = ' ';
            }
        }

        /*Récupération du nombre de lignes du fichier et séparation des lignes dans un tableau à 2 dimenstions*/
        logAction(1,"Récupération des lignes");
        while(fgets(lines[nbLines], strlen(lines[nbLines]), fichier))
        {
            if(nbLines < MaxScoresDispalyed-1){
                lines[nbLines][strlen(lines[nbLines]) - 1] = '\0';
                nbLines++;
            }
        }

        /*Séparation de la date, des points et des pseudos depuis les lignes*/
        logAction(1,"Séparation des informations");
        for(int i = 0; i < nbLines; ++i)
        {
            /*  https://www.educative.io/edpresso/splitting-a-string-using-strtok-in-c  */
            char * token = strtok(lines[i], ";"); //Division une première fois des différentes parties (dans un pointeur)
            int countWords = 0;

            char *strg[100];
            while( token != NULL ) { //Boucle avec un pointeur permettant d'identifier l'emplacement de chaques mots
                strg[countWords] = token; //Duplication du pointeur temporaire dans un petit tableau
                token = strtok(NULL, ";"); //Division suivante des différentes parties
                countWords++;
            }
            /*Ecriture (Transfert) de pointeurs dans les tableaux de pointeur officiels*/
            names[i] = strg[0];
            pointS[i] = strg[1];
            date[i] = strg[2];
        }
        /*Affichage des scores*/
        logAction(2,"Affichage des scores au joueur");
        printf("DATE/HEURE\t\tCOUPS\tPSEUDO\n");
        for(int i = 0;i<nbLines;i++){
            printf("%s\t%s\t%s\n",date[i],pointS[i],names[i]);
        }
        fclose(fichier);
    }else{
        logAction(1,"Aucun fichier de scores trouvé");
        printf("DATE/HEURE\tCOUPS\tPSEUDO\n");
        printf("Aucun résulta.\n");
    }
    system("pause");
    displayMainMenu();
}

/**
 * Description : Fonction s'executant au démarage d'une partie pour remettre des variables de précédantes parties à leur état initial.
 */
void setupGame(){
    playASound(0);
    playASound(9);
    playASound(3);
    logAction(1,"Démarage d'une partie");
    gameGrildCoups = 0;//Le joueur n'a pas encore joué de coups
    logAction(3,"Attente du retour de la carte choisie...");
    getRandomGame(); //Prends une carte au hasard d'un sous-dossier

    logAction(3,"Carte initialisée...");
    logAction(1,"Mise de la carte dans les tableaux de jeux");
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
    logAction(1,"Remise à zéro des tableaux terminée");
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
    logAction(1,"Fin de la manipulation des tableaux");
    logAction(3,"Carte opérationnelle");
    displayGame();
}
/**
 * Descriptino : Récupère une partie existante à partir d'un fichier ou demande à l'utilisateur de la choisir
 */
void getRandomGame(){
    logAction(1,"Démarage du choix de la carte");
    char pathFile[128] = "./maps/"; //Le chemin d'acces à la carte
    int hasValidFile = 0;
    do {
        clear();
        /*Séléction du choix par l'utilisateur*/
        logAction(2,"Demande de la méthode de jeu à l'utilisateur");
        printf("Comment souhaitez-vous jouer ?\n\n");
        printf("1. Choisir la carte de mon choix dans le dossier 'maps'\n");
        printf("2. Prendre une carte aléatoire du dossier 'maps'\n");
        printf("3. Générer une carte aléatoire (non-disponible actuellement)\n");

        int choix = askChoiceMin(1,2);

        /*Séléction du type de chargment de map*/
        if(choix > 0 && choix < 3){
            pathFile[128] = "./maps/";
            DIR* rep = opendir("maps"); //https://waytolearnx.com/2019/09/lister-les-fichiers-dans-un-repertoire-en-c.html

            if (rep != NULL)//Si le répertoire existe
            {
                logAction(1,"Mise en place des tableaux");
                struct dirent *ent;//Création d'une structure d'un fichier

                int nbFiles = 0;//Nombre de fichiers listé dans le dossier en question
                char filesFounded[100][64];//Nom des fichiers dans le dossier en question (ceci n'est pas le chemin d'accès car ils sont dans un sous-dossier)

                /*Initialisation des fichiers trouvés avec une valeur par défaut*/
                for (int flLine = 0; flLine < 100; flLine++) {
                    for (int flContent = 0; flContent < 64; flContent++) {
                        filesFounded[flLine][flContent] = NULL;
                    }
                }

                clear();
                /*Affichage des carte trouvées dans tout les cas*/
                printf("----Cartes trouvées----\n\n");
                logAction(2,"Affichage des cartes trouvées");

                while ((ent = readdir(rep)) != NULL)//Tourne tant qu'il reste des fichier qui n'ont pas été pris
                {
                    if (ent->d_name[0] != '.') {//Si ce n'est pas un chemin d'accès pour revenir en arrière (ex : ".." ou ".")
                        for (int i = 0; i < strlen(ent->d_name); i++) {
                            filesFounded[nbFiles][i] = ent->d_name[i]; //Tous les fichiers trouvés se stockent dans le tableau des fichiers trouvés
                        }
                        printf("%s \n", filesFounded[nbFiles]);//Liste utilile si le joueur veut pouvoir choisi plus facilement sa carte
                        nbFiles++;
                    }
                }

                closedir(rep);//Fermeture de la gestion du répertoire (étant donné qi'il y a déja un tablea avec tous les ficheirs dedans)

                if (nbFiles == 0) {//Si il n'y a pas de fichiers trouvés
                    logAction(1,"Aucun fichier n'a été trouvé");
                    printf("Oops ! Aucune carte n'a été trouvé dans le dossier 'maps'.\n");
                    printf("Veuillez mettre une carte en .bnmap (utf-8 sans BOM vivement conseillé) dedans pour continuer...\n");
                    system("pause");
                    hasValidFile = 0;
                } else {
                    if (choix == 1) {//Si le joueur veut choisir sa carte
                        /*Selection du joueur*/
                        logAction(2,"Demande du nom de la carte à charger");
                        printf("\nVeuillez entrer le nom de la carte :\n");
                        char file[64] = "";
                        scanf("%62s", file);

                        int voider; while ((voider = getchar()) != EOF && voider !='\n'); //Vidage du scanf si un problème précédant est survenu ou un dépassement//

                        int founded = 0;
                        for (int i = 0; i < nbFiles; i++) {
                            if (founded == 0) {
                                //printf("Dans %s ressemblance : %d \n", filesFounded[i], strcmp(file, filesFounded[i]));
                                if (strcmp(file, filesFounded[i]) == 0) { //Comparaison du choix de l'utilisateur avec chaque fichiers (fonction déterminant quel différences il y a ua niveau des caractères) si la fonctino retourne 0, il n'y a aucune différence et donc la carte existe
                                    founded = 1;
                                    strcat(pathFile, filesFounded[i]); //Ajout du chemin d'accès au dossier + le fichier poru avoir un chemin d'accès complet j'usqu'au fichier
                                    hasValidFile = 1;
                                }
                            }
                        }
                        if(founded == 0){//Si aucune cartte ne correspond
                            logAction(1,"La carte choisie n'est pas trouvée");
                            printf("Carte non-trouvée !\n");
                            system("pause");
                            hasValidFile = 0;
                        }
                    }
                    if (choix == 2) {//Prise d'une carte aléatoire
                        logAction(1,"Prise d'une carte aléatoire");
                        srand(time(NULL));
                        int random = (rand() % nbFiles);
                        strcat(pathFile, filesFounded[random]);//Ajout du chemin d'accès au dossier + le fichier poru avoir un chemin d'accès complet j'usqu'au fichier
                        hasValidFile = 1;
                    }
                }
            } else {
                logAction(1,"Le dossier 'maps' n'a pas été trouvé");
                mkdir("maps"); //Ce cas arrive seulement si le joueur supprime le dossier entre temps.
                printf("Oops ! Le dossier 'maps' n'a pas été trouvé. Il viens donc d'être créé.'\n");
                printf("Veuillez mettre une carte en .bnmap dedans pour continuer...\n");
                system("pause");
                hasValidFile = 0;
            }
        }
    }while (hasValidFile == 0);


    /*Traîtement et importation du niveau*/
    logAction(1,"Ouverture de la carte");
    printf("Ouverture de : %s\n",pathFile);

    FILE* fichier = NULL;
    fichier = fopen(pathFile, "r+");//Ouverture du fichier dans le mode LECTURE/ECRITURE

    if(fichier!= NULL) {//Si le fichier existe
        int nbLines = 0; //Nombres de lignes dans le fichier
        char lines[GrildLenght+2][GrildLenght*2+2];//Le contenu du fichier ligne par ligne

        /*Récupération du nombre de lignes du fichier et séparation des lignes dans un tableau à 2 dimenstions*/
        while (fgets(lines[nbLines],(GrildLenght*2)+2, fichier)) {
            lines[nbLines][strlen(lines[nbLines]) - 1] = '\0';
            nbLines++;
        }
        /*Recopie la structure du fichier pour la metttre dans le tableau*/
        for(int i = 0;i< GrildLenght;i++){
            for(int placeColone = 0;placeColone < GrildLenght;placeColone++){
                char ch = lines[i][placeColone];
                gameGrildBoats[i][placeColone] = (int) strtol(&ch, NULL, 10);
            }
        }
        logAction(1,"Le tableau des bateaux a été traîté avec succès");
    }else{
        printf("Oops ! Une erreur est survenue ! Le fichier précédemment trouvé n'est plus disponible. Essayez de redémarer le jeu pour régler le problème.\n");
        logAction(0,"Le fichier précédemment trouvé n'est plus disponible. Essayez de redémarer le jeu pour régler le problème.");
        system("pause");

        exit(1);
    }
}

/**
 * Description : Fonction s'éxecutant à chaques tours durant une partie
 */
void displayGame(){

    /*Valeurs où le joueur va décider d'envoyer un missile*/
    int lineAttack = -1;
    int colAttack = -1;

    int isCaseValid = 0;//Si la case que le joueur a choisi n'a pas déjà été jouée

    logAction(2,"Affichage de la grille de jeu");
    showGameGrild();//Affichage de la grille de jeu (joueur)

    do {
        logAction(3,"Le joueur entre une position...");
        colAttack = askChoiceChar(); //Le scanf seulement n'étant pas suffisant pour cette requête, une fonction spéciale de traîtement a été créée (Demande à l'utilisateur et transforme son choix en une valeur INT utilisable pour tableau)
        /*Remise au même état que si la précédante commande n'avait pas existé (Plus jolis et prends moins de place)*/
        showGameGrild();

        printf("Entrez la ligne à attaquer :");
        lineAttack = askChoiceMin(1, linesMax)-1; //Le scanf seulement n'étant pas suffisant pour cette requête, une fonction spéciale a été créée. Si le MIN ou le MAX n'est pas respecté, elle tourne en boucle jusqu'à ce que le joueur entre une valeur correcte (-1 à cause des tableaux)

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
                logAction(3,"Le joueur a coulé le dernier bateau");
                endGame();
            }else{
                /*La partie continue*/
                playASound(0);
                playASound(9+bateauxTouche);
                logAction(3,"Le joueur a coulé un bateau");
                visualEvent(3);
                displayGame();
            }
        }else{
            /*Le bateau est juste touché*/
            logAction(3,"Le joueur a touché un bateau");
            visualEvent(2);
            displayGame();
        }
    }else{
        /*Il n'y a pas de bateaux*/
        logAction(3,"Le joueur n'a rien touché");
        gameGrild[line][col] = 1; //Cette case sera maintenant affiché différemement sur la carte du joueur car elle a été découverte
        visualEvent(1);
        displayGame();
    }
}

/**
 * Description : Fonction s'éxecutant à la fin d'une partie
 */
void endGame(){
    showGameGrild();
    visualEvent(4);
    system("color df");
    drawer(6,0);
    printf("\nPARTIE TERMINEE EN %d COUPS ! \n",gameGrildCoups);
    logAction(3,"FIN DE PARTIE !");
    system("pause");
    playASound(8);
    system("color ed");
    clear();
    setScore();
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
    printf("   ");//Espace de syncronisation (pour que le rendu soit jolis)
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
        for(int i=0;i<=5;i++){
            printf("\n");
        }
    }
}

/**
 * Description : Une fcontion qui stoque automatiquement les logs dans un fichier
 * @param typeEvent le type d' entre 0 et 3
 * @param texte la descruption
 */
void logAction(int typeEvent,char * texte){
    char eventName[4][64] = {"FATAL ERROR","BOOT AND LOW-SYSTEMS","UI SYSTEM AND MANAGER","GAME EVENT"};

    //Récupération de la date actuelle
    time_t t = time(NULL); //https://stackoverflow.com/questions/1442116/how-to-get-the-date-and-time-values-in-a-c-program
    struct tm tm = *localtime(&t);//Prise de l'instance de l'heure locale dans une structure

    if(enablePrintLogsInConsole){
        printf("\n %d.%02d.%02d à %02d:%02d %s - %s : %s \n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min,eventName[typeEvent],texte);
    }
    /*OUVERTURE DU FICHIER*/
    FILE* fichier = NULL;

    fichier = fopen("logs.txt", "a");
    fprintf(fichier,"%d.%02d.%02d à %02d:%02d - %s : %s\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min,eventName[typeEvent],texte);
    fclose(fichier);
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
 * Description : Idem que askChoiceMin mais avec les caractères converti en décimal à l'aide d'une grille
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