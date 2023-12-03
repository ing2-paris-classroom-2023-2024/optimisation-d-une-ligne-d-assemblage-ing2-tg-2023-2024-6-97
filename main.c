#include "header.h"

int main() {
    //Graphe *ligneAssemblage;
    //ligneAssemblage =chargementGrapheOriente();

    //chargementExclusions();

    preced_cycles();

    return 0;
}


int preced_cycles(){  //Sous-programme qui gère les précédences et le temps de cycle - Appelé depuis le menu
    t_precedences graph;

    initialiserMatrice(&graph);
    lireContraintePrecedence(&graph);
    afficherGraphePrecedenceConsole(&graph);

    // Initialiser les opérations triées
    for (int i = 0; i < graph.nbOperations; ++i) {
        graph.operationsTriees[i] = i;
    }

    // Trier les opérations en fonction du nombre de prédécesseurs
    trierOperations(&graph);

    triTopologique(&graph);

    printf("\nOrdre trie des operations : ");
    for (int i = 0; i < graph.nbOperations; ++i) {
        printf("%d ", graph.operationsTriees[i] + 1);
    }
    printf("\n");

    lireTempsOperations(&graph);
    float sommeTemps = calculerSommeTemps(&graph);
    printf("Somme des temps : %.2f\n", sommeTemps);

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

    printf("\nTemps de cycle : %.2f\n", tempsCycle);

    // Répartir les opérations en stations en respectant le temps de cycle
    repartirEnStations(&graph, tempsCycle);

    return 0;
}
