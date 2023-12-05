//
// Created by comeb on 03/12/2023.
//
#include "header.h"


void chargerExclusions(t_assemblage *assemblage, t_precedences *graph) {
    FILE *fichierExclusions = fopen("exclusions.txt", "r");
    if (fichierExclusions == NULL) {
        printf("Impossible d'ouvrir le fichier exclusions.txt.\n");
        return;
    }

    // Réinitialiser les exclusions
    for (int i = 0; i < MAX_OPERATIONS; i++) {
        for (int u = 0; u < 2; u++) {
            assemblage->exclusions[i][u] = -5;
        }
    }
    assemblage->nbExclusions = 0;

    while (fscanf(fichierExclusions, "%d %d", &assemblage->exclusions[assemblage->nbExclusions][0],
                  &assemblage->exclusions[assemblage->nbExclusions][1]) != EOF) {
        assemblage->nbExclusions++;
    }

    // Mettre à jour le tableau des sommets exclus
    for (int i = 0; i < assemblage->nbExclusions; i++) {
        assemblage->tabSommetsExclus[i * 2] = assemblage->exclusions[i][0];
        assemblage->tabSommetsExclus[i * 2 + 1] = assemblage->exclusions[i][1];
    }
    for(int i=0; i<MAX_OPERATIONS; i++){
        for(int u=0; u<MAX_OPERATIONS; u++) {
            assemblage->stations[i][u] = 0;
        }
    }

    fclose(fichierExclusions);
    /*printf("Nombre d'exclusions : %d\n", assemblage->nbExclusions);
    for(int i = 0; i < assemblage->nbExclusions; i++){
        printf("Exclusion %d : %d %d\n", i + 1, assemblage->exclusions[i][0], assemblage->exclusions[i][1]);
    }*/
}

// Fonction utilitaire pour afficher les exclusions
void afficherStationsOptimisees(t_assemblage *assemblage) {
    printf("\nStations optimisees :\n");
    for (int i = 1; i <= assemblage->nbStations; i++) {
        printf("Station %d : ", i);
        for (int j = 0; j < assemblage->nbExclusions; j++) {
            if (assemblage->stations[i][j] != 0) {
                printf("%d ", assemblage->stations[i][j]);
            }
        }
        printf("\n");
    }
    printf("\nNombre de stations finales : %d\n", assemblage->nbStations);
}

// Fonction utilitaire pour vérifier si un sommet a des exclusions
int aDesExclusions(t_assemblage *assemblage, int sommet) {
    for (int i = 0; i < assemblage->nbExclusions; i++) {
        if (assemblage->exclusions[i][0] == sommet || assemblage->exclusions[i][1] == sommet) {
            return 1;  // Le sommet a des exclusions
        }
    }
    return 0;  // Le sommet n'a pas d'exclusions
}


// Fonction utilitaire pour vérifier si un sommet est déjà dans une station
int estDansUneStation(t_assemblage *assemblage, int sommet) {
    for (int i = 1; i <= assemblage->nbStations; i++) {
        for (int j = 0; j < MAX_OPERATIONS; j++) {
            if (assemblage->stations[i][j] == sommet) {
                return 1;  // Le sommet est déjà dans une station
            }
        }
    }
    return 0;  // Le sommet n'est pas dans une station
}

// Fonction utilitaire pour obtenir le numéro de la station à laquelle un sommet appartient
int getNumeroStation(t_assemblage *assemblage, int sommet) {
    for (int i = 1; i <= assemblage->nbStations; i++) {
        for (int j = 0; j < MAX_OPERATIONS; j++) {
            if (assemblage->stations[i][j] == sommet) {
                return i;  // Retourne le numéro de la station
            }
        }
    }
    return -1;  // Retourne -1 si le sommet n'est pas dans une station
}


int regrouperActions(t_assemblage *assemblage, t_precedences *graph) {
    //printf("Debut de la fonction regrouperActions\n");
    // Initialiser les stations
    int stationCount = 0;  // Déclaration globale

    // Ajouter les sommets sans exclusion à la première station
    int sommetsSansExclusion = 0;
    for (int i = 0; i < graph->nbSommets; i++) {
        int sommet = graph->tabSommets[i];
        if (!aDesExclusions(assemblage, sommet)) {
            if(sommet !=-500) { //On sort de la boucle si on arrive à un sommet qui n'existe pas
                assemblage->sommetsNonExclus[sommetsSansExclusion] = sommet;
                //ajouterAStation(assemblage, sommet, stationCount);
                sommetsSansExclusion++;
            }
        }
    }
    //printf("Nombre de sommets sans exclusion : %d\n", sommetsSansExclusion);
    //return 0;

    for (int i = 0; i < assemblage->nbExclusions; i++) {
        int sommet1 = assemblage->exclusions[i][0];
        int sommet2 = assemblage->exclusions[i][1];

        if (!estDansUneStation(assemblage, sommet1) && !estDansUneStation(assemblage, sommet2)) {
            // Aucun des sommets n'est encore dans une station, créer une nouvelle station
            //printf("Nouvelle station créée pour sommet %d et %d\n", sommet1, sommet2);
            stationCount++;
            ajouterAStation(assemblage, sommet1, stationCount);
            ajouterAStation(assemblage, sommet2, stationCount);
            //printf("Nouvelle station créée pour sommet %d et %d, stationCount = %d\n", sommet1, sommet2, stationCount);
        } else if (estDansUneStation(assemblage, sommet1) && !estDansUneStation(assemblage, sommet2)) {
            // sommet1 est dans une station, ajouter sommet2 à la même station
            //printf("Ajout de sommet %d à la station %d\n", sommet2, getNumeroStation(assemblage, sommet1));
            ajouterAStation(assemblage, sommet2, getNumeroStation(assemblage, sommet1) - 1);
            //printf("Ajout de sommet %d à la station %d\n", sommet2, getNumeroStation(assemblage, sommet1));
        } else if (!estDansUneStation(assemblage, sommet1) && estDansUneStation(assemblage, sommet2)) {
            // sommet2 est dans une station, ajouter sommet1 à la même station
            //printf("Ajout de sommet %d à la station %d\n", sommet1, getNumeroStation(assemblage, sommet2));
            ajouterAStation(assemblage, sommet1, getNumeroStation(assemblage, sommet2) - 1);
            //printf("Ajout de sommet %d à la station %d\n", sommet1, getNumeroStation(assemblage, sommet2));
        } else {
            // Les deux sommets sont déjà dans des stations différentes, fusionner les stations
            //printf("On fusionne les stations %d et %d\n", getNumeroStation(assemblage, sommet1), getNumeroStation(assemblage, sommet2));
            int station1 = getNumeroStation(assemblage, sommet1) - 1;
            int station2 = getNumeroStation(assemblage, sommet2) - 1;
            // Vérifier si les stations sont différentes
            if (station1 != station2) {
                fusionnerStations(assemblage, station1, station2);
                //printf("Fusion des stations %d et %d\n", station1 + 1, station2 + 1);
            }
        }
    }
}

// Fonction utilitaire pour ajouter un sommet à une station
void ajouterAStation(t_assemblage *assemblage, int sommet, int station) {
    for (int i = 0; i < MAX_OPERATIONS; i++) {
        if (assemblage->stations[station][i] == 0) {
            assemblage->stations[station][i] = sommet;
            //printf("Ajout de sommet %d a la station %d\n", sommet, station + 1);
            break;
        }
    }
}

// Fonction utilitaire pour fusionner deux stations
void fusionnerStations(t_assemblage *assemblage, int station1, int station2) {
    //printf("Fusion des stations %d et %d\n", station1 + 1, station2 + 1);

    // Trouver la première position vide dans la station1
    int positionVide = 0;
    while (assemblage->stations[station1][positionVide] != 0) {
        positionVide++;
    }

    // Ajouter les sommets de la station2 à la station1 à partir de la position vide
    for (int i = 0; i < MAX_OPERATIONS; i++) {
        if (assemblage->stations[station2][i] != 0) {
            assemblage->stations[station1][positionVide++] = assemblage->stations[station2][i];
            printf("Ajout de sommet %d à la station %d\n", assemblage->stations[station2][i], station1 + 1);
        }
    }
    // Réinitialiser la station fusionnée
    for (int i = 0; i < MAX_OPERATIONS; i++) {
        assemblage->stations[station2][i] = 0;
    }
}

void affichageStationsOptimisees(t_assemblage *assemblage, t_precedences *graph) {
    printf("\nStations optimisees exclusions :\n\n");
    printf("Station %d : ", 1);
    //printf("Graphe nbExclusions : %d\n", assemblage->nbExclusions);


    int tableauExclusionsUniques[assemblage->nbExclusions];
    for(int i=0; i<assemblage->nbExclusions; i++){
        tableauExclusionsUniques[i] = -500;
    }
    int duplic =0, increment =0;
    for(int i=0; i<assemblage->nbExclusions; i++){
        int chose = assemblage->exclusions[i][0];
        for(int u=0; u<assemblage->nbExclusions; u++){
            if(tableauExclusionsUniques[u] == assemblage->exclusions[i][0]){
                duplic =1;
            }
        }
        if(duplic ==0){
            if(chose !=-500) {
                tableauExclusionsUniques[i] = chose;
                increment++;
            }
        }
        duplic =0;
    }
    triBulle(tableauExclusionsUniques, increment);

    for(int i=0; i < assemblage->nbExclusions; i++){
        if(tableauExclusionsUniques[i] !=-500) printf("%d ", tableauExclusionsUniques[i]);
    }

    int sommetsSansExclusion = 0, corresp =0;
    for (int i = 0; i < graph->nbSommets; i++) {
        int sommet = graph->tabSommets[i];
        for(int u =0; u<assemblage->nbExclusions; u++){
            if(sommet == assemblage->exclusions[u][0] || sommet == assemblage->exclusions[u][1]){
                corresp =1;
            }
        }
        if(corresp ==0){
            if(sommet !=-500) { //On sort de la boucle si on arrive à un sommet qui n'existe pas
                assemblage->sommetsNonExclus[sommetsSansExclusion] = sommet;
                //ajouterAStation(assemblage, sommet, stationCount);
                sommetsSansExclusion++;
            }
        }
        corresp =0;
    }
    ///Afficahge sommets non exclus
    printf("| ");
    for(int i =0; i< sommetsSansExclusion; i++){
        printf("%d ", assemblage->sommetsNonExclus[i]);
    }

    ///STATION 2
    printf("\nStation %d : ", 2);

    FILE *fichierExclusions = fopen("exclu.txt", "r");
    if (fichierExclusions == NULL) {
        printf("Impossible d'ouvrir le fichier exclusions.txt.\n");
        return;
    }
    rewind(fichierExclusions); //On remet le curseur au début du fichier
    //printf("Fichier ouvert");
    for(int i=0; i<assemblage->nbExclusions; i++){
        tableauExclusionsUniques[i] = -500;
    }

    int A, B; int tabTemporaire[MAX_OPERATIONS];
    for(int i=0; i<assemblage->nbExclusions; i++){
        fscanf(fichierExclusions, "%d %d", &A, &B);
        tabTemporaire[i] = B;
    }
    fclose(fichierExclusions);

    duplic =0, increment =0;
    for(int i=0; i<assemblage->nbExclusions; i++){
        int chose = tabTemporaire[i];
        for(int u=0; u<assemblage->nbExclusions; u++){
            if(tableauExclusionsUniques[u] == tabTemporaire[i]){
                duplic =1;
            }
        }
        if(duplic ==0){
            if(chose !=-500) {
                tableauExclusionsUniques[i] = chose;
                increment++;
            }
        }
        duplic =0;
    }
    //triBulle(tableauExclusionsUniques, increment);

    for(int i=0; i < assemblage->nbExclusions; i++){
        if(tableauExclusionsUniques[i] !=-500) printf("%d ", tableauExclusionsUniques[i]);
    }

    Color(4,0); //Rouge
    printf("\n\nNombre de stations totales : %d\n", 2);
    Color(7,0); //Blanc
}



void echanger(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void triBulle(int tableau[], int taille) {
    for (int i = 0; i < taille - 1; i++) {
        for (int j = 0; j < taille - i - 1; j++) {
            if (tableau[j] > tableau[j + 1]) {
                echanger(&tableau[j], &tableau[j + 1]);
            }
        }
    }
}