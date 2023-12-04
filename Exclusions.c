//
// Created by comeb on 03/12/2023.
//
#include "header.h"


void chargerExclusions(t_assemblage *assemblage) {
    FILE *fichierExclusions = fopen("exclusions.txt", "r");
    if (fichierExclusions == NULL) {
        printf("Impossible d'ouvrir le fichier exclusions.txt.\n");
        return;
    }

    assemblage->nbExclusions = 0;

    while (fscanf(fichierExclusions, "%d %d", &assemblage->exclusions[assemblage->nbExclusions].actionA,
                  &assemblage->exclusions[assemblage->nbExclusions].actionB) == 2) {
        assemblage->nbExclusions++;
    }

    fclose(fichierExclusions);
    printf("Nombre d'exclusions : %d\n", assemblage->nbExclusions);

    // Optimiser la ligne d'assemblage en fonction des exclusions
    optimiserLigneAssemblage(assemblage);
}

void optimiserLigneAssemblage(t_assemblage *assemblage) {
    int nbStations = 0;
    int stations[MAX_OPERATIONS] = {0};  // Tableau pour stocker les stations de chaque action

    for (int i = 0; i < assemblage->nbExclusions; ++i) {
        int actionA = assemblage->exclusions[i][0];
        int actionB = assemblage->exclusions[i][1];

        // Vérifier si les actions peuvent être affectées à la même station
        int canBeInSameStation = 1;

        for (int j = 0; j < nbStations; ++j) {
            int stationAction = stations[j];

            // Vérifier les exclusions
            if ((stationAction == actionA) || (stationAction == actionB)) {
                canBeInSameStation = 0;
                break;
            }
        }

        if (canBeInSameStation) {
            // Affecter les actions à la même station
            stations[nbStations++] = actionA;
            stations[nbStations++] = actionB;
        } else {
            // Affecter les actions à des stations différentes
            stations[nbStations++] = actionA;
            printf("Station %d : Operation %d\n", nbStations, actionA);
            nbStations = 0;  // Réinitialiser le compteur de stations
            stations[nbStations++] = actionB;
        }
    }

    // Afficher la dernière station
    printf("Station %d : Operation %d\n", nbStations, stations[0]);
}
