#include "header.h"

void lireTempsDesOpe(t_precedences *graph) {
    FILE *fichier = fopen("operations.txt", "r");
    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return;
    }

    for (int i = 0; i < graph->nbOperations; i++) {
        graph->temps[i] = 0;
    }

    int operation;
    float tempsOperation;
    while (fscanf(fichier, "%d %f", &operation, &tempsOperation) == 2) {
        graph->temps[operation - 1] = tempsOperation;
    }

    fclose(fichier);
}

int repartirDansStations(t_precedences *graph) {
    float tempsStation = 0;
    int station = 1;


    // Lire le temps de cycle depuis le fichier temps_cycle.txt (à ajuster selon le format du fichier)
    FILE *fichierCycle = fopen("temps_cycle.txt", "r");
    if (fichierCycle == NULL) {
        printf("Impossible d'ouvrir le fichier temps_cycle.txt.\n");
        return 1;
    }

    float tempsCycle;
    if (fscanf(fichierCycle, "%f", &tempsCycle) != 1) {
        printf("Erreur de lecture du temps de cycle.\n");
        fclose(fichierCycle);
        return 1;
    }
    fclose(fichierCycle);


    printf("\nRepartition en stations :\n");
    for (int i = 0; i < graph->nbOperations; ++i) {
        int currentOperation = i;  // Utilisation de l'indice directement sans tri
        if ((tempsStation + graph->temps[currentOperation] <= tempsCycle)) {
            if (graph->temps[currentOperation] != 0) {
                tempsStation += graph->temps[currentOperation];
                printf("Station %d : Operation %d (%.2f)\n", station, currentOperation + 1, graph->temps[currentOperation]);
            }
        } else {
            tempsStation = graph->temps[currentOperation];
            printf("\nStation %d : Operation %d (%.2f)\n", ++station, currentOperation + 1, graph->temps[currentOperation]);
        }
    }
    printf("\nNombre stations finales : %d\n", station);
}


int repartirDansStationsMODIF(t_precedences *graph){
    float tempsStation = 0;
    int station = 1;


    // Lire le temps de cycle depuis le fichier temps_cycle.txt (à ajuster selon le format du fichier)
    FILE *fichierCycle = fopen("temps_cycle.txt", "r");
    if (fichierCycle == NULL) {
        printf("Impossible d'ouvrir le fichier temps_cycle.txt.\n");
        return 1;
    }

    float tempsCycle;
    if (fscanf(fichierCycle, "%f", &tempsCycle) != 1) {
        printf("Erreur de lecture du temps de cycle.\n");
        fclose(fichierCycle);
        return 1;
    }
    fclose(fichierCycle);

    int vu =0, vu2 =0;

    printf("\n\nOptimisation Temps de Cycle :\n");
    for (int i = 0; i < graph->nbOperations; ++i) {
        int currentOperation = i;  // Utilisation de l'indice directement sans tri
        if ((tempsStation + graph->temps[currentOperation] <= tempsCycle)) {
            if (graph->temps[currentOperation] != 0) {
                tempsStation += graph->temps[currentOperation];
                if(station ==2){
                    vu =0;
                    vu2 =0;}

                if (vu ==0){
                    printf("Station %d : ", station);
                    vu =1;}
                printf("%d (%.2f) / ", currentOperation + 1, graph->temps[currentOperation]);
            }
        } else {
            tempsStation = graph->temps[currentOperation];
            if (vu2 ==0){
                printf("\nStation %d : ", ++station);
                vu2 =1;
            }
            printf("%d (%.2f) / ", currentOperation + 1, graph->temps[currentOperation]);
        }
        //vu =0; vu2 =0;
    }
    Color(4,0); //Rouge
    printf("\n\nNombre stations finales : %d\n", station);
    Color(7,0); //Blanc
}


