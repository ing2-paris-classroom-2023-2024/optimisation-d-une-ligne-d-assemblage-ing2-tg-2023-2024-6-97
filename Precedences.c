#include "header.h"


void initialiserMatrice(t_precedences *graph) {
    for (int i = 0; i < MAX_OPERATIONS; ++i) {
        for (int j = 0; j < 2; ++j) {
            graph->precedences[i][j] = 0;
        }
        graph->nbPredecesseurs[i] = 0;
    }
    graph->nbSommets =0;

    for(int i=0; i<MAX_OPERATIONS; i++){
        graph->existe[i]=0;
    }
}

void lireContraintePrecedence(t_precedences *graph) {
    FILE *fichier = fopen("precedences.txt", "r");
    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return;
    }
    //printf("Lecture du fichier precedences.txt\n");

    int operationA, operationB;
    graph->nbOperations = 0;  // Initialisation ajoutée
    rewind(fichier); //On remet le curseur au début du fichier
    while (fscanf(fichier, "%d %d", &operationA, &operationB) == 2) {
        //printf("Operation %d -> Operation %d\n", operationA, operationB);
        graph->precedences[operationA - 1][operationB - 1] = 1;
        graph->nbPredecesseurs[operationB - 1]++;
        graph->nbOperations = (operationA > graph->nbOperations) ? operationA : graph->nbOperations;
        graph->nbOperations = (operationB > graph->nbOperations) ? operationB : graph->nbOperations;
    }

    //On marque les sommets qui existent vraiment :
    rewind(fichier); //On remet le curseur au début du fichier
    int val1 =0, val2 =0;
    int nbOperations =0;
    while (fscanf(fichier, "%d %d", &val1, &val2) != EOF) { //Compteur du nombre d'arcs et sommets
        nbOperations +=2; //Deux sommets par ligne
    }    ///On a notre taille maximale de tableau de sommets s'il sont tous uniques
    graph->nbSommets = val1;

    int iter =0, corresp =0, nbSommets =0;
    int tabSommetsMultiples[nbOperations], tabSommetsUniques[nbOperations];
    rewind(fichier); //On remet le curseur au début du fichier
    for(int i =0; i <graph->nbSommets; i++){
        fscanf(fichier, "%d %d", &val1, &val2);
        graph->existe[val1-1] = 1;
        graph->existe[val2-1] = 1;
        if(val1 > graph->nbSommets) graph->nbSommets = val1;
        if(val2 > graph->nbSommets) graph->nbSommets = val2;

        tabSommetsMultiples[iter] = val1; tabSommetsMultiples[iter+1] = val2;
        iter+=2;
    }


    ///Reset des variables
    for(int z =0; z <nbOperations; z++){ tabSommetsUniques[z] =-500; } //On met le tableau des uniques à -500 valeur défaut
    iter =0;

    ///Trouve tous les sommets uniques et les compte
    for(int i=0; i<nbOperations; i++){
        for(int u=0; u<graph->nbSommets; u++){
            if(tabSommetsMultiples[i] == tabSommetsUniques[u]){
                corresp =1;
            }
        }
        if(corresp ==0){
            tabSommetsUniques[iter] = tabSommetsMultiples[i];
            iter++;
        }
        corresp =0;
    }
    for(int a=0; a <graph->nbSommets; a++){
        graph->tabSommets[a] = tabSommetsUniques[a];
    }


    //Boucle de vérification :
    /*for(int i=0; i<graph->nbSommets; i++){
        printf("Sommet unique %d : %d\n", i+1, tabSommetsUniques[i]);
    }*/
    /*for(int i=0; i<graph->nbSommets; i++){
        if(graph->existe[i] == 1){
            printf("Sommet %d existe\n", i+1);
        }
    }
    printf("nbSommets : %d\n", graph->nbSommets);*/

    fclose(fichier);
}

void lireTempsOperations(t_precedences *graph) {
    FILE *fichier = fopen("operations.txt", "r");
    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return;
    }

    for(int i = 0; i < graph->nbOperations; i++){
        graph->temps[i] = 0;
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

    printf("\nOptimisation Precedences + Temps :\n");
    for (int i = 0; i < graph->nbOperations; ++i) {
        int currentOperation = graph->operationsTriees[i];
        if ((tempsStation + graph->temps[currentOperation] <= tempsCycle)) {
            if(graph->temps[currentOperation] ==0) tempsStation += graph->temps[currentOperation];
            else {
                tempsStation += graph->temps[currentOperation];
                printf("Station %d : Operation %d (%.2f)\n", station, currentOperation + 1, graph->temps[currentOperation]);}
        } else {
            tempsStation = graph->temps[currentOperation];
            printf("\nStation %d : Operation %d (%.2f)\n", ++station, currentOperation + 1, graph->temps[currentOperation]);
        }
    }
    Color(4,0); //Rouge
    printf("\nNombre stations finales : %d\n", station);
    Color(15,0); //Blanc
}
