#include "header.h"


void initialiserMatrice(t_precedences *graph) {
    for (int i = 0; i < MAX_OPERATIONS; ++i) {
        for (int j = 0; j < MAX_OPERATIONS; ++j) {
            graph->precedences[i][j] = 0;
        }
        graph->nbPredecesseurs[i] = 0;
    }
}

void lireContraintePrecedence(t_precedences *graph) {
    FILE *fichier = fopen("precedences.txt", "r");
    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return;
    }

    int operationA, operationB;
    graph->nbOperations = 0;  // Initialisation ajoutée
    while (fscanf(fichier, "%d %d", &operationA, &operationB) == 2) {
        printf("Operation %d -> Operation %d\n", operationA, operationB);
        graph->precedences[operationA - 1][operationB - 1] = 1;
        graph->nbPredecesseurs[operationB - 1]++;
        graph->nbOperations = (operationA > graph->nbOperations) ? operationA : graph->nbOperations;
        graph->nbOperations = (operationB > graph->nbOperations) ? operationB : graph->nbOperations;
    }

    fclose(fichier);
}

void lireTempsOperations(t_precedences *graph) {
    FILE *fichier = fopen("operations.txt", "r");
    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return;
    }

    int operation;
    float tempsOperation;
    while (fscanf(fichier, "%d %f", &operation, &tempsOperation) == 2) {
        graph->temps[operation - 1] = tempsOperation;
    }

    fclose(fichier);
}

void afficherGraphePrecedenceConsole(t_precedences *graph) {
    printf("Graphe de precedence :\n");
    for (int i = 0; i < graph->nbOperations; ++i) {
        printf("Operation %d : ", i + 1);
        for (int j = 0; j < graph->nbOperations; ++j) {
            if (graph->precedences[i][j]) {
                printf("%d -> %d   ", i + 1, j + 1);
            }
        }
        printf("\n");
    }
}

void trierOperations(t_precedences *graph) {
    // Tri à bulles pour trier les opérations en fonction du nombre de prédécesseurs
    for (int i = 0; i < graph->nbOperations - 1; ++i) {
        for (int j = 0; j < graph->nbOperations - i - 1; ++j) {
            if (graph->nbPredecesseurs[j] > graph->nbPredecesseurs[j + 1]) {
                // Échanger les positions des opérations et de leurs nombres de prédécesseurs
                int temp = graph->nbPredecesseurs[j];
                graph->nbPredecesseurs[j] = graph->nbPredecesseurs[j + 1];
                graph->nbPredecesseurs[j + 1] = temp;

                temp = graph->operationsTriees[j];
                graph->operationsTriees[j] = graph->operationsTriees[j + 1];
                graph->operationsTriees[j + 1] = temp;
            }
        }
    }
}

void triTopologique(t_precedences *graph) {
    int degre[MAX_OPERATIONS] = {0};
    int queue[MAX_OPERATIONS];
    int front = 0, rear = -1;

    // Initialiser la file avec les opérations sans prédécesseurs
    for (int i = 0; i < graph->nbOperations; ++i) {
        int current = graph->operationsTriees[i];
        for (int j = 0; j < graph->nbOperations; ++j) {
            if (graph->precedences[j][current]) {
                degre[current]++;
            }
        }
        if (degre[current] == 0) {
            queue[++rear] = current;
        }
    }

    // Effectuer le tri topologique
    while (front <= rear) {
        int current = queue[front++];
        graph->operationsTriees[front - 1] = current;

        for (int i = 0; i < graph->nbOperations; ++i) {
            if (graph->precedences[current][i]) {
                if (--degre[i] == 0) {
                    queue[++rear] = i;
                }
            }
        }
    }
}

float calculerSommeTemps(t_precedences *graph) {
    float somme = 0;
    for (int i = 0; i < graph->nbOperations; ++i) {
        somme += graph->temps[graph->operationsTriees[i]];
    }
    return somme;
}

void repartirEnStations(t_precedences *graph, float tempsCycle) {
    float tempsStation = 0;
    int station = 1;
    float tempsTotal = 0;

    printf("\nRepartition en stations :\n");
    for (int i = 0; i < graph->nbOperations; ++i) {
        int currentOperation = graph->operationsTriees[i];
        if (tempsStation + graph->temps[currentOperation] <= tempsCycle) {
            tempsStation += graph->temps[currentOperation];
            printf("Station %d : Operation %d (%.2f)\n", station, currentOperation + 1, graph->temps[currentOperation]);
        } else {
            tempsStation = graph->temps[currentOperation];
            printf("\nStation %d : Operation %d (%.2f)\n", ++station, currentOperation + 1, graph->temps[currentOperation]);
        }
    }
}
