/*
 * Projet : Bataille Navale
 * Description : Une bataille navale en C dans le cadre MA-20 et ICT-114 du CPNV
 * Auteur : Eliott Jaquier
 * Ce script sert à gérer des évènements spéciaux du jeu nécésitant une réaction graphique
*/
/**
 * Description : Fonction permettant de gérer différents évènement du jeu (Axé sur le front end)
 * @param event : L'id de l'évènement de partie
 */
void visualEvent(int event){//Event : (0->Lancement, 1->plouf, 2->touché, 3->coulé, 4->Fin de partie)
    switch (event){
        case 0://Animation de lancement
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
                        if(i==7){
                            clear();
                            drawer(6,0);
                        }
                        if(i==14){
                            clear();
                            drawer(1,0);
                            printf("\n");
                            drawer(5,0);
                        }
                        if(i==20){
                            clear();
                            drawer(3,0);
                        }
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