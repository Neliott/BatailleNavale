/*
 * Projet : Bataille Navale
 * Description : Une bataille navale en C dans le cadre MA-20 et ICT-431 du CPNV
 * Auteur : Eliott Jaquier
 * Ce script sert à gérer des évènements spéciaux du jeu nécésitant une réaction graphique
*/
/**
 * Description : Fonction permettant de gérer différents évènement du jeu (Axé sur le front end)
 * @param event : L'id de l'évènement de partie
 */
void visualEvent(int event){//Event : (0->Lancement, 1->plouf, 2->touché, 3->coulé, 4->Fin de partie)
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);//Prise de l'instance de l'heure locale dans une structure
    switch (event){
        case 0://Animation de lancement

            /*Récupération de la date*/
            if((tm.tm_mday < 3) && ( tm.tm_mon + 1) == 4){//Déclenchement d'un poisson d'avril
                printf("Projet corrompu !\n");
                Sleep(1000);
                printf("Récupération automatique.");
                Sleep(1000);
                printf(".");
                Sleep(1000);
                printf(".");
                Sleep(1000);
                printf(".\n");
                printf("La récupération a échouée !!!\n");
                Sleep(2000);
                printf("Essayez de redémarer le jeu...\n");
                Sleep(3500);
                clear();
                Sleep(1000);
                playASound(14);
                if(!isEditor) {
                    system("color 91");
                }
                drawer(8,0);
                printf("\n Poisson d'avril !!!");
                for(int i = 0;i<10;i++){
                    system("color 4F");
                    Sleep(100);
                    system("color 6F");
                    Sleep(100);
                    system("color 2F");
                    Sleep(100);
                    system("color 1F");
                    Sleep(100);
                    system("color 9F");
                    Sleep(100);
                    system("color 5F");
                    Sleep(100);
                }
                Sleep(1000);
                clear();
                if(!isEditor) {
                    system("color F");
                }

                int choice = 1;
                do{
                    if(choice != 1){
                        Sleep(1000);
                        printf("");
                    }
                    printf("Avez-vous apprécié ce GAG ? \n 1. Oui \n 2. Non\n");
                    scanf("%d",&choice);
                    clear();
                    if(choice != 1){
                        Sleep(1000);
                        printf("Ok, je pense que vous avez mal compris la question...");
                        Sleep(3000);
                    }
                }while(choice != 1);
                clear();
                Sleep(1000);
                printf("Ahahahah ! Ouiiii ! J'en était sûre ! Tout le monde me dis ça !!!\n");
                Sleep(5000);
                printf("C'est vraiment un GAG super drôle non ?!\n");
                Sleep(1500);
                printf("Bon. Je vais vous laisser profiter du jeu maintenant !\n");
                Sleep(1000);
                printf("Bonne chance ! !\n");
                Sleep(6000);
                clear();
            }
			
			
            if(!isEditor){
                clear();//Bataille Navale
                playASound(1);
                system("color F0");
                drawer(1,0);
                Sleep(250);
                system("color 04");
                Sleep(2250);

                clear();//Par Eliott
                system("color F0");
                drawer(3,0);
                Sleep(250);
                system("color 04");
                Sleep(2250);

                clear();//Animation de chargement
                system("color 3E");
                for(int i=0;i<70;i++){
                    clear();
                    drawer(0,i);
                    Sleep(25);
                }
                system("color 1B");
                playASound(0);
            }else{
                printf("Chargement... (version interne seulement - changer la constante isEditor en 1 pour le mode console)");
                Sleep(2000);
            }
            break;
        case 1://Plouf
            if(isEditor|| !isEffect){
                printf("Plouf !\n");
                Sleep(1000);
            }else{
                //Evenement visuel ici
                playASound(4);
                system("color B1");
                Sleep(300);
                system("color 1B");
            }
            break;
        case 2://Touché
            if(isEditor || !isEffect){
                printf("Touché !\n");
                Sleep(1000);
            }else{
                playASound(5);
                system("color 40");
                Sleep(300);
                system("color 1B");
            }
            break;
        case 3://Coulé
            if(isEditor || !isEffect){
                printf("Coulé !\n");
                Sleep(1000);
            }else{
                //Evenement visuel ici
                playASound(6);
                system("color 40");
                Sleep(100);
                system("color 04");
                Sleep(100);
                system("color 40");
                Sleep(100);
                system("color 04");
                Sleep(100);
                system("color 40");
                Sleep(100);
                system("color 04");
                Sleep(100);
                system("color 1B");
            }
            break;
        case 4://Fin de partie
            if(isEditor){
                printf("\nFin de la partie !");
                Sleep(1000);
            }else{
                //Evenement visuel ici
                playASound(0);
                if(isEffect){
                    playASound(7);
                    playASound(6);
                    for(int i=0;i<25;i++) {
                        if(i==7){//Bravo
                            clear();
                            drawer(6,0);
                        }
                        if(i==14){//Bataille Navale
                            clear();
                            drawer(1,0);
                            printf("\n");
                            drawer(5,0);
                        }
                        if(i==20){//Par eliott
                            clear();
                            drawer(3,0);
                        }
                        /*Arc en ciel*/
                        system("color 4F");
                        Sleep(100);
                        system("color 6F");
                        Sleep(100);
                        system("color 2F");
                        Sleep(100);
                        system("color 1F");
                        Sleep(100);
                        system("color 9F");
                        Sleep(100);
                        system("color 5F");
                        Sleep(100);
                    }
                }
                system("color 1B");
                clear();
            }
            break;
        default:
            Sleep(1000);
            break;
    }
}