/*
 * Projet : Bataille Navale
 * Description : Une bataille navale en C dans le cadre MA-20 et ICT-114 du CPNV
 * Auteur : Eliott Jaquier
 * Ce script sert à centraliser tous les événements audio
*/
/**
 *  Description : Fonction facilitant la gestion des sons
 * @param id : L'id du son
 */
void playASound(int id){
    if(isAudio && !isEditor){
        switch(id){
            case 1: //Start
                system("start /min %cd%/sounds/sounder.exe /id start /stopbyid %cd%/sounds/CLIP0_START.wav");
                break;
            case 2: //Loop du menu
                system("start /min %cd%/sounds/sounder.exe /id 4dist /loop 100 /stopbyid %cd%/sounds/CLIP4_DIST.wav");
                break;
            case 3: //Click
                system("start /min %cd%/sounds/sounder.exe /id click /stopbyid %cd%/sounds/s7.wav");
                break;
            case 4: //Ploufe
                system("start /min %cd%/sounds/sounder.exe /id plouf /stopbyid %cd%/sounds/s3.wav");
                break;
            case 5: //Touché
                system("start /min %cd%/sounds/sounder.exe /id touche /stopbyid %cd%/sounds/s5.wav");
                break;
            case 6: //Coulé
                system("start /min %cd%/sounds/sounder.exe /id coule /stopbyid %cd%/sounds/s1.wav");
                break;
            case 7: //Loop du menu
                system("start /min %cd%/sounds/sounder.exe /id endparty /stopbyid %cd%/sounds/CLIP2_END.wav");
                break;
            case 8: //Loop du scoreset
                system("start /min %cd%/sounds/sounder.exe /id 3dist /loop 100 /stopbyid %cd%/sounds/CLIP4_DIST.wav");
                break;
            case 9: //Loop jeu1
                system("start /min %cd%/sounds/sounder.exe /id jeu1 /loop 100 /stopbyid %cd%/sounds/CLIP1_DIST.wav");
                break;
            case 10: //Loop jeu2
                system("start /min %cd%/sounds/sounder.exe /id jeu2 /loop 100 /stopbyid %cd%/sounds/CLIP1.wav");
                break;
            case 11: //Loop jeu3
                system("start /min %cd%/sounds/sounder.exe /id jeu3 /loop 100 /stopbyid %cd%/sounds/CLIP4_DIST.wav");
                break;
            case 12: //Loop jeu4
                system("start /min %cd%/sounds/sounder.exe /id jeu4 /loop 100 /stopbyid %cd%/sounds/CLIP4.wav");
                break;
            case 13: //Loop jeu5
                system("start /min %cd%/sounds/sounder.exe /id jeu5 /loop 100 /stopbyid %cd%/sounds/CLIP3.wav");
                break;
            case 14: //Loop prank
                system("start /min %cd%/sounds/sounder.exe /id prank /stopbyid %cd%/sounds/m.wav");
                break;
            case 0:
            default:
                system("start /min %cd%/sounds/sounder.exe /stop");
                break;
        }
    }
}