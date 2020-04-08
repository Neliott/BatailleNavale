/*
 * Projet : Bataille Navale
 * Description : Une bataille navale en C dans le cadre MA-20 et ICT-431 du CPNV
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
                system("start /min ./sounds/sounder.exe /id start /stopbyid ./sounds/CLIP0_START.wav");
                break;
            case 2: //Loop du menu
                system("start /min ./sounds/sounder.exe /id 4dist /loop 100 /stopbyid ./sounds/CLIP4_DIST.wav");
                break;
            case 3: //Click
                system("start /min ./sounds/sounder.exe /id click /stopbyid ./sounds/s7.wav");
                break;
            case 4: //Ploufe
                system("start /min ./sounds/sounder.exe /id plouf /stopbyid ./sounds/s3.wav");
                break;
            case 5: //Touché
                system("start /min ./sounds/sounder.exe /id touche /stopbyid ./sounds/s5.wav");
                break;
            case 6: //Coulé
                system("start /min ./sounds/sounder.exe /id coule /stopbyid ./sounds/s1.wav");
                break;
            case 7: //Loop du menu
                system("start /min ./sounds/sounder.exe /id endparty /stopbyid ./sounds/CLIP2_END.wav");
                break;
            case 8: //Loop du scoreset
                system("start /min ./sounds/sounder.exe /id 3dist /loop 100 /stopbyid ./sounds/CLIP4_DIST.wav");
                break;
            case 9: //Loop jeu1
                system("start /min ./sounds/sounder.exe /id jeu1 /loop 100 /stopbyid ./sounds/CLIP1_DIST.wav");
                break;
            case 10: //Loop jeu2
                system("start /min ./sounds/sounder.exe /id jeu2 /loop 100 /stopbyid ./sounds/CLIP1.wav");
                break;
            case 11: //Loop jeu3
                system("start /min ./sounds/sounder.exe /id jeu3 /loop 100 /stopbyid ./sounds/CLIP4_DIST.wav");
                break;
            case 12: //Loop jeu4
                system("start /min ./sounds/sounder.exe /id jeu4 /loop 100 /stopbyid ./sounds/CLIP4.wav");
                break;
            case 13: //Loop jeu5
                system("start /min ./sounds/sounder.exe /id jeu5 /loop 100 /stopbyid ./sounds/CLIP3.wav");
                break;
            case 14: //Loop prank
                system("start /min ./sounds/sounder.exe /id prank /stopbyid ./sounds/m.wav");
                break;
            case 0: //Arrêter les sons
            default:
                system("start /min ./sounds/sounder.exe /stop");
                break;
        }
    }
}