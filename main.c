#include "header.h"

int main() {
    //Graphe *ligneAssemblage;
    //ligneAssemblage =chargementGrapheOriente();

    //chargementExclusions();
    int choix =menu();
    switch(choix){
        case 1:
            //exclusions();
            break;
        case 2:
            //exclusions_cycles();
            break;
        case 3:
            preced_cycles();
            break;
        case 4:
            //preced_exclu();
            break;
        case 5:
            //preced_exclu_cycles();
            break;
        case 6:
            //comparaison();
            break;
        case 7:
            exit(0);
            break;
    }

    return 0;
}

int menu(){
    system("cls");
    Color(2,0);//Vert
    printf("====== Bienvenue dans votre programme d'optimisation de ligne d'assemblage ======\n");
    Color(1,0);//Bleu
    printf("Choix :\n");
    printf("1. Exclusions\n");
    printf("2. Exclusions et Temps de cycle\n");
    printf("3. Precedences et Temps de cycle\n");
    printf("4. Precedences et Exclusions\n");
    printf("5. Precedences, Exclusions et Temps de cycle\n");
    printf("6. Comparaison des 3 dernieres\n");
    printf("7. Quitter\n");

    int choix =0;
    Color(6,0); //Jaune
    printf("Votre choix : ");
    Color(7,0); //Blanc
    scanf("%d", &choix);
    fflush(stdin);

    while (choix < 1 || choix > 7){
        Color(6,0); //Jaune
        printf("Veuillez recommencer\n");
        printf("Votre choix : ");
        Color(7,0); //Blanc
        scanf("%d", &choix);
        fflush(stdin);
    }
    return choix;
}



int preced_cycles(){  //Sous-programme qui gère les précédences et le temps de cycle - Appelé depuis le menu
    t_precedences graph;

    initialiserMatrice(&graph);
    lireContraintePrecedence(&graph);
    //afficherGraphePrecedenceConsole(&graph);

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


//Fonction color de la biliothèque windows.h pour changer la couleur de la console
void Color(int couleurDuTexte,int couleurDeFond){ // fonction d'affichage de couleurs
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}
