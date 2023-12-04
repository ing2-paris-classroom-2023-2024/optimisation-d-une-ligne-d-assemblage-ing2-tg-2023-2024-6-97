#ifndef OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_6_97_GIT_HEADER_H
#define OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_6_97_GIT_HEADER_H

/// ██████╗ ██╗██████╗ ██╗     ██╗ ██████╗ ████████╗██╗  ██╗███████╗ ██████╗ ██╗   ██╗███████╗███████╗
/// ██╔══██╗██║██╔══██╗██║     ██║██╔═══██╗╚══██╔══╝██║  ██║██╔════╝██╔═══██╗██║   ██║██╔════╝██╔════╝
/// ██████╔╝██║██████╔╝██║     ██║██║   ██║   ██║   ███████║█████╗  ██║   ██║██║   ██║█████╗  ███████╗
/// ██╔══██╗██║██╔══██╗██║     ██║██║   ██║   ██║   ██╔══██║██╔══╝  ██║▄▄ ██║██║   ██║██╔══╝  ╚════██║
/// ██████╔╝██║██████╔╝███████╗██║╚██████╔╝   ██║   ██║  ██║███████╗╚██████╔╝╚██████╔╝███████╗███████║
/// ╚═════╝ ╚═╝╚═════╝ ╚══════╝╚═╝ ╚═════╝    ╚═╝   ╚═╝  ╚═╝╚══════╝ ╚══▀▀═╝  ╚═════╝ ╚══════╝╚══════╝

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <windows.h>


/// ███████╗████████╗██████╗ ██╗   ██╗ ██████╗████████╗██╗   ██╗██████╗ ███████╗███████╗
/// ██╔════╝╚══██╔══╝██╔══██╗██║   ██║██╔════╝╚══██╔══╝██║   ██║██╔══██╗██╔════╝██╔════╝
/// ███████╗   ██║   ██████╔╝██║   ██║██║        ██║   ██║   ██║██████╔╝█████╗  ███████╗
/// ╚════██║   ██║   ██╔══██╗██║   ██║██║        ██║   ██║   ██║██╔══██╗██╔══╝  ╚════██║
/// ███████║   ██║   ██║  ██║╚██████╔╝╚██████╗   ██║   ╚██████╔╝██║  ██║███████╗███████║
/// ╚══════╝   ╚═╝   ╚═╝  ╚═╝ ╚═════╝  ╚═════╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝╚══════╝╚══════╝

struct Arc { /* Structure d'un arc*/
    int sommet; // numéro de sommet d'un arc adjacent au sommet initial
    struct Arc* arc_suivant;
};
typedef struct Arc* pArc; /* Alias de pointeur sur un Arc */


struct Sommet { /* Structure d'un sommet*/
    struct Arc* arc;
    int *exclu; ///Stocke les id des sommets exclus
    int poids; //Poids du sommet (représente le temps d'exécution d'une machine)
    int visite;
    int id;     //ID du sommet
    int existe; //Booléen qui indique si le sommet existe ou non, car tous les numéros de sommets ne sont pas forcément utilisés
};
typedef struct Sommet* pSommet; /* Alias de pointeur sur un Sommet */


typedef struct Graphe { /* Structure d'un graphe*/
    int ordre;  //Nombre de sommets
    int taille; //Nombre d'arêtes / arcs
    pSommet* pSommet;
} Graphe; /* Alias d'un Graphe */


typedef struct Exclu { //Tableau de structure qui pointe vers tous les sommets exclus
    int id;
    struct Exclu *suiv; //Pointeur vers le prochain élément du tableau
} Exclude;


///Structure spécifique pour la précédence ///Faite par Louis
#define MAX_OPERATIONS 100

typedef struct precedences {
    int precedences[MAX_OPERATIONS][MAX_OPERATIONS];
    int nbOperations;

    int operationsTriees[MAX_OPERATIONS];
    int nbPredecesseurs[MAX_OPERATIONS];
    float temps[MAX_OPERATIONS];
} t_precedences;

///Structure spécifique pour l'exclusion ///Faite par Kimi'
typedef struct {
    int exclusions[MAX_OPERATIONS][2];
    int nbExclusions;
} t_assemblage;




/// ██████╗ ██████╗  ██████╗ ████████╗ ██████╗ ████████╗██╗   ██╗██████╗ ███████╗███████╗
/// ██╔══██╗██╔══██╗██╔═══██╗╚══██╔══╝██╔═══██╗╚══██╔══╝╚██╗ ██╔╝██╔══██╗██╔════╝██╔════╝
/// ██████╔╝██████╔╝██║   ██║   ██║   ██║   ██║   ██║    ╚████╔╝ ██████╔╝█████╗  ███████╗
/// ██╔═══╝ ██╔══██╗██║   ██║   ██║   ██║   ██║   ██║     ╚██╔╝  ██╔═══╝ ██╔══╝  ╚════██║
/// ██║     ██║  ██║╚██████╔╝   ██║   ╚██████╔╝   ██║      ██║   ██║     ███████╗███████║
/// ╚═╝     ╚═╝  ╚═╝ ╚═════╝    ╚═╝    ╚═════╝    ╚═╝      ╚═╝   ╚═╝     ╚══════╝╚══════╝

Graphe *chargementGrapheOriente();
Graphe *CreerGraphe(int tailleMax,int ordre, int tab[ordre]);
pSommet *CreerArete(pSommet* sommet,int s1,int s2, int *tabSommetsUniques);

int menu();
void Color(int couleurDuTexte,int couleurDeFond);
int preced_cycles();  //Sous-programme qui gère les précédences et le temps de cycle - Appelé depuis le menu
t_assemblage initialiserAssemblage();

//Exclusions
void chargerExclusions(t_assemblage *assemblage);
void optimiserLigneAssemblage(t_assemblage *assemblage);
void afficherStationsOptimisees(t_assemblage *assemblage);

//Precedence + Temps cycle
void initialiserMatrice(t_precedences *graph);
void lireContraintePrecedence(t_precedences *graph);
void lireTempsOperations(t_precedences *graph);
void afficherGraphePrecedenceConsole(t_precedences *graph);
void trierOperations(t_precedences *graph);
void triTopologique(t_precedences *graph);
float calculerSommeTemps(t_precedences *graph);
void repartirEnStations(t_precedences *graph, float tempsCycle);


#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_6_97_GIT_HEADER_H
