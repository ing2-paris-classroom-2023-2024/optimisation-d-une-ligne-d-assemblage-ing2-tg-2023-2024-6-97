#include "header.h"

Graphe *chargementGrapheOriente() {
    FILE* precedences = fopen("precedences.txt", "r");
    FILE* durees = fopen("operations.txt", "r");
    if (precedences == NULL || durees == NULL) {
        printf("Erreur lors de l'ouverture des fichiers.\n");
        exit(1);
    }

    //Le nombre de sommets n'étant pas précisé, on doit charger chaque ligne du fichier pour connaitre le nombre d'arcs
    //Et ensuite, on peut trouver le nombre de sommets
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
    for(int z =0; z <nbSommetsMAX; z++){ tabSommetsUniques[z] =-500; } //On met le tableau des uniques à -500 valeur défaut

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
    } //nbSommets contient le nombre de sommets uniques

    ///On cherche le num du sommet max pour créer notre graphe
    int sommetMax =0;
    for(int i =0; i <nbSommets; i++){
        if(tabSommetsUniques[i] > sommetMax){
            sommetMax =tabSommetsUniques[i];
        }
    } //sommetMax correspond au numéro du sommet le plus grand

    ///================================================================================///
    ///========================== CREATION DU GRAPHE (STRUCT) =========================///
    Graphe *graphe;
    graphe = CreerGraphe(sommetMax, nbSommets, tabSommetsUniques);
    printf("Graphe cree\n");
    graphe->ordre =nbSommets;
    graphe->taille =nbArcs;

    /* Pour régler les problèmes dus à la non-utilisation de tous les sommets et à la manière dont on stocke le graphe en mémoire
     * (une liste du nombre exact de sommets donc le 35 peut être à la 30e place et créer des conflits) on change de système
     * et on passe sur une liste toujours mais du nombre max d'un sommet (donc 35) et on met un booléen qui indique si le sommet
     * existe ou non. Si le sommet n'existe pas, on ne le prend pas en compte dans le graphe. */

    rewind(precedences); //On remet le curseur au début du fichier
    //Créer les arêtes du graphe
    for (int i = 0; i < nbArcs; i++) {
        fscanf(precedences, "%d %d", &s1, &s2);
        printf("Chose\n");
        graphe->pSommet = CreerArete(graphe->pSommet, s1, s2, tabSommetsUniques);
    }


    ///================================================================================///
    ///============================= LECTURE POIDS SOMMETS ============================///

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

    for (int i = 0; i < graphe->ordre; i++) {
        printf("\nSommet %d :\n", graphe->pSommet[i]->id);
        printf("  Arcs : ");

        pArc arc = graphe->pSommet[i]->arc;
        while (arc != NULL) {
            printf("%d ", arc->sommet);
            arc = arc->arc_suivant;
        }

        printf("\n");
    }

    printf("\nFin du chargement\n");

    return graphe;
}



Graphe *CreerGraphe(int tailleMax,int ordre, int tab[ordre]) { // Alloue dynamiquement le graphe et ses sommets
    Graphe *Newgraphe =(Graphe*)malloc(sizeof(Graphe));
    Newgraphe->pSommet =(pSommet*)malloc(tailleMax *sizeof(pSommet));

    for(int i =0; i <tailleMax; i++){
        Newgraphe->pSommet[i]=(pSommet)malloc(sizeof(struct Sommet));
        Newgraphe->pSommet[i]->existe =0;
        Newgraphe->pSommet[i]->visite =0;
        Newgraphe->pSommet[i]->arc=NULL;
    }
    for(int i =0; i <tailleMax; i++){
        for(int u =0; u <ordre; u++){
            if(tab[u] == i){
                Newgraphe->pSommet[i]->id =tab[u];
                Newgraphe->pSommet[i]->existe =1;
            }
        }
    }
    return Newgraphe;
}



pSommet* CreerArete(pSommet* sommet, int s1, int s2, int *tabSommetsUniques) {
    if(sommet[s1]->existe ==0 || sommet[s2]->existe ==0){ //On vérifie si les sommets existent avant de tenter d'allouer
        printf("Erreur : Sommet inexistant.\n");
        return sommet;
    }

    int indexS1 = tabSommetsUniques[s1];
    int indexS2 = tabSommetsUniques[s2];

    pArc Newarc = (pArc)malloc(sizeof(struct Arc));
    Newarc->sommet = s2;
    Newarc->arc_suivant = NULL;

    if (sommet[s1]->arc == NULL || sommet[s1]->arc->sommet > s2) {
        // Insérer au début de la liste ou si la liste est vide
        Newarc->arc_suivant = sommet[s1]->arc;
        sommet[s1]->arc = Newarc;
    } else {
        pArc temp = sommet[s1]->arc;
        while (temp->arc_suivant != NULL && temp->arc_suivant->sommet < s2) {
            temp = temp->arc_suivant;
        }
        Newarc->arc_suivant = temp->arc_suivant;
        temp->arc_suivant = Newarc;
    }

    return sommet;
}