# Jeu "Bataille Navale"
**Description**
Une projet d'entrainement en C afin de s’entraîner à exécuter des mandats, gérer ses projets ainsi que les documenter. 

**Comment le tester (Windows)**

 1. Téléchargez le projet complet ici : https://github.com/EliottJaquierCPNV/BatailleNavale/archive/master.zip
 2. Trouvez un éditeur (CLion : [https://www.jetbrains.com/fr-fr/clion/](https://www.jetbrains.com/fr-fr/clion/) ou CodeBlocks : [http://www.codeblocks.org/](http://www.codeblocks.org/)) ainsi qu'un compilateur (MinGW : [http://www.mingw.org/](http://www.mingw.org/)
 3. Ouvrez le répertoire depuis l'éditeur 
 4. Compilez le (cela va indiquer où le .exe sera compilé)
 
      4.1 - Si vous décidez d'avoir une version optimisée pour la console intégrée CLION, ne changez rien et lancez l'application directement depuis l'éditeur.
 
      4.2 - Si vous desirez avoir accès à TOUTES les fonctionnalités (couleurs, animations ou des sonds), lancez le .exe en externe. Si vous faites cela, veuillez régler la constante du jeu "isEditor" sur 0. IL EST VIVEMENT CONSEILLE DE PRENDRE "Fichiers tests (A côté du .exe)" ET DE DEPLACER TOUS LES REPERTOIRES A COTE DU .EXE
 
 5. Appréciez ces graphismes de l'extrême du mode console en jouant à la bataille navale !

**Comment bien créer une carte**
(Un exemple est dans le dossier des "Fichiers de tests à déplacer")

1. Laissez une ligne vide à la fin de votre carte de 10 par 10
2. Les bateaux doivent avoir des ID différents allant de 1 à 5
3. Il n'est pas nécessaire de suivre un ordre de grandeur officiel car cela est calculé en temps réel dans le jeu (Exemple : un bateau peut n'avoir qu'une case _Très petit bateau_ ou 7 cases _Énorme bateau_)
4. Préférez l'encodage UTF-8 SANS BOM si cela est possible.
