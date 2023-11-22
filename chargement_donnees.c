#include "header.h"

Graphe chargementGrapheOriente() {
    FILE* precedences = fopen("precedences.txt", "r");
    FILE* durees = fopen("operations.txt", "r");
    if (precedences == NULL || durees == NULL) {
        printf("Erreur lors de l'ouverture des fichiers.\n");
        exit(1);
    }

    //Le nombre de sommets n'étant pas précisé on doit charger chaque ligne du fichier pour connaitre le nombre d'arcs
    //Et ensuite on peut trouver le nombre de sommets
    //Et donc allouer un nouvel arc à chaque chargement de ligne //Sachant que les id des sommets ne représentent pas leur position dans le tableau


    ///================================================================================///
    ///========================= COMPTAGE DES ARCS ET SOMMETS =========================///
    int nbArcs = 0, nbSommets = 0, nbSommetsMAX = 0;
    int s1, s2, poids;
    int iter =0, corresp =0;

    while (fscanf(precedences, "%d %d", &s1, &s2) != EOF) { //Compteur du nombre d'arcs et sommets
        nbArcs++;     //Un arc par ligne
        nbSommetsMAX+=2; //Deux sommets par ligne
    }    ///On a notre taille maximale de tableau de sommets s'il sont tous uniques
    int tabSommetsMultiples[nbSommetsMAX], tabSommetsUniques[nbSommetsMAX];

    rewind(precedences); //On remet le curseur au début du fichier

    ///Lecture de tous les sommets du fichier
    for(int i =0; i <nbArcs; i++){
        fscanf(precedences, "%d %d", &s1, &s2);
        tabSommetsMultiples[iter] = s1; tabSommetsMultiples[iter+1] = s2;
        iter+=2;
    }

    ///Reset des variables
    tabSommetsUniques[0] = tabSommetsMultiples[0]; //On met le premier sommet dans le tableau des uniques
    for(int z =0; z <nbSommetsMAX; z++){ tabSommetsUniques[z] =-500; } //On set le tableau des uniques pour comparaison

    ///Trouve tous les sommets uniques et les compte
    for(int i =0; i <iter; i++){
        for(int u =0; u <iter; u++){
            if(tabSommetsMultiples[i] == tabSommetsUniques[u]){
                corresp =1;
            }
        }
        if(corresp ==0){
            tabSommetsUniques[nbSommets] = tabSommetsMultiples[i];
            nbSommets++;
        }
        corresp =0;
    }

    ///================================================================================///
    ///========================== CREATION DU GRAPHE (STRUCT) =========================///
    /*Graphe graphe;
    graphe.arc = (Arete *)malloc(arbreMinimum.nombreAretes * sizeof(Arete));
    arbreMinimum.sommets = (Sommet *)malloc(graphe.nombreSommets * sizeof(Sommet));*/


    ///================================================================================///
    ///============================== LECTURE POIDS ARCS ==============================///

    int sommet; float duree;
    /*while (fscanf(durees, "%d %d", &sommet, &duree) != EOF) {

    }*/
    //On peut maintenant allouer le bon nombre de sommets et d'arcs dans nos structures
    //Le nombre de sommets est égal à nbSommets
    //On peut créer le graph avec le bon nombre de sommets et d'arcs, il faut maintenant relancer le fichier pour le relire
    //rewind(precedences); //On remet le curseur au début du fichier

    //Graphe* graphe = CreerGraphe(nbSommets, nbArcs); //On crée notre graphe

    ///==================================== AFFICHAGE ==================================///
    printf("\nResulats du chargement :\n");
    printf("NbSommets : %d\nNbArcs : %d\n", nbSommets, nbArcs);
    printf("Sommets uniques : ");
    for(int i =0; i <nbSommets; i++){
        printf("%d ", tabSommetsUniques[i]);
    }
    printf("\nFin du chargement\n");

    free(tabSommetsUniques); //On libère la mémoire de ce tableau temporaire
    return graphe;
}