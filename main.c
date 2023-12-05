#include "header.h"

int main() {
    //Graphe *ligneAssemblage;
    //ligneAssemblage =chargementGrapheOriente();
    //chargementExclusions();

    t_precedences graph; //Structure du graphe avec precedences
    t_assemblage assemblage;

    initialiserMatrice(&graph);
    lireContraintePrecedence(&graph);
    chargerExclusions(&assemblage, &graph);
    for(int i=0; i<graph.nbSommets; i++){
        assemblage.sommetsNonExclus[i] =graph.tabSommets[i];
    }
    //afficherGraphePrecedenceConsole(&graph);

    // Initialiser les opérations triées
    for (int i = 0; i < graph.nbOperations; ++i) {
        graph.operationsTriees[i] = i;
    }
    trierOperations(&graph); // Trier les opérations en fonction du nombre de prédécesseurs
    triTopologique(&graph); // Tri topologique des opérations
    //getchar();
    fflush(stdin);

    int choix =0;
    do{
        choix =menu();
        switch(choix) {
            case 1:
                regrouperActions(&assemblage, &graph);
                affichageStationsOptimisees(&assemblage, &graph);
                break;
            case 2:
                lireTempsDesOpe(&graph);
                float sommeTemps = calculerSommeTemps(&graph);
                printf("Somme des temps : %.2f\n", sommeTemps);
                // Répartir les opérations en stations en respectant le temps de cycle
                repartirDansStations(&graph);
                break;
            case 3:
                preced_cycles(&graph);
                /*printf("\nAffichage trie : ");
                for(int u=0; u<graph.nbOperations; u++){
                    printf("%d ", graph.operationsTriees[u]);
                }*/
                break;
            case 4:
                precedExclusion();
                break;
            case 5:
                //preced_exclu_cycles();
                break;
            case 6:
                regrouperActions(&assemblage, &graph);
                affichageStationsOptimisees(&assemblage, &graph);
                lireTempsDesOpe(&graph);
                repartirDansStationsMODIF(&graph);
                preced_cycles(&graph);
                break;
            case 7:
                exit(0);
                break;
        }
        getchar();
        fflush(stdin);
    }while(choix !=7);

    return 0;
}

int menu(){
    system("cls");
    Color(2,0);//Vert
    printf("====== Bienvenue dans votre programme d'optimisation de ligne d'assemblage ======\n");
    Color(1,0);//Bleu
    printf("Choix :\n");
    printf("1. Exclusions\n");
    printf("2. Temps de cycle\n");
    printf("3. Precedences et Temps de cycle\n");
    printf("4. Precedences et Exclusions\n");
    printf("5. Precedences, Exclusions et Temps de cycle\n");
    printf("6. Comparaison entre la 1/2/3\n");
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



int preced_cycles(t_precedences *graph){  //Sous-programme qui gère les précédences et le temps de cycle - Appelé depuis le menu

    /*printf("\nOrdre trie des operations : ");
    for (int i = 0; i < graph->nbOperations; ++i) {
        printf("%d ", graph->operationsTriees[i] + 1);
    }
    printf("\n");*/

    lireTempsOperations(graph);
    float sommeTemps = calculerSommeTemps(graph);
    printf("\n\nSomme des temps : %.2f\n", sommeTemps);

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

    printf("Temps de cycle : %.2f\n", tempsCycle);

    // Répartir les opérations en stations en respectant le temps de cycle
    repartirEnStations(graph, tempsCycle);

    return 0;
}


//Fonction color de la biliothèque windows.h pour changer la couleur de la console
void Color(int couleurDuTexte,int couleurDeFond){ // fonction d'affichage de couleurs
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}
