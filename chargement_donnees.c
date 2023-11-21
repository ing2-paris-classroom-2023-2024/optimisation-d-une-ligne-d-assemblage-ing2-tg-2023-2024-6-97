#include "header.h"

void chargementGrapheOriente() {
    FILE* precedences = fopen("precedences.txt", "r");
    FILE* durees = fopen("operations.txt", "r");

    if (precedences == NULL || durees == NULL) {
        printf("Erreur lors de l'ouverture des fichiers.\n");
        exit(1);
    }

    //Le nombre de sommets n'étant pas précisé on doit charger chaque ligne du fichier pour connaitre le nombre d'arcs
    //Et ensuite on peut trouver le nombre de sommets
    //Et donc allouer un nouvel arc à chaque chargement de ligne //Sachant que les id des sommets ne représentent pas leur position dans le tableau
    int nbArcs = 0;
    int nbSommets = 0;
    int s1, s2, poids;
    while (fscanf(precedences, "%d %d", &s1, &s2) != EOF) {
        nbArcs++;
        if (s1 > nbSommets) nbSommets = s1;
        if (s2 > nbSommets) nbSommets = s2;
    } //Cette boucle ne tient pas compte du fait que s1 et s2 ne sont pas forcément le bon numéro de sommet dans le tableau

    //On peut créer le graph avec le bon nombre de sommets et d'arcs, il faut maintenant relancer le fichier pour le relire
    rewind(precedences); //On remet le curseur au début du fichier

    Graphe* graphe = CreerGraphe(nbSommets, nbArcs); //On crée notre graphe

    //Remplissage sommets
    for(int i =0; i <nbSommets; i++){ //NOMS DES SOMMETS - ID
        fscanf(id, "%d", &id);
        fscanf(durees,"%d", &s1);
    }


}