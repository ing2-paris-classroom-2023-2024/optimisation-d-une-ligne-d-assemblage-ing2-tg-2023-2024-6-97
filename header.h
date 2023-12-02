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


/// ██████╗ ██████╗  ██████╗ ████████╗ ██████╗ ████████╗██╗   ██╗██████╗ ███████╗███████╗
/// ██╔══██╗██╔══██╗██╔═══██╗╚══██╔══╝██╔═══██╗╚══██╔══╝╚██╗ ██╔╝██╔══██╗██╔════╝██╔════╝
/// ██████╔╝██████╔╝██║   ██║   ██║   ██║   ██║   ██║    ╚████╔╝ ██████╔╝█████╗  ███████╗
/// ██╔═══╝ ██╔══██╗██║   ██║   ██║   ██║   ██║   ██║     ╚██╔╝  ██╔═══╝ ██╔══╝  ╚════██║
/// ██║     ██║  ██║╚██████╔╝   ██║   ╚██████╔╝   ██║      ██║   ██║     ███████╗███████║
/// ╚═╝     ╚═╝  ╚═╝ ╚═════╝    ╚═╝    ╚═════╝    ╚═╝      ╚═╝   ╚═╝     ╚══════╝╚══════╝

Graphe *chargementGrapheOriente();
Graphe *CreerGraphe(int tailleMax,int ordre, int tab[ordre]);
pSommet *CreerArete(pSommet* sommet,int s1,int s2, int *tabSommetsUniques);

//Precedence + Temps
void initialiserMatrice();
void lireContraintePrecedence();
void lireTempsOperations();
void afficherGraphePrecedenceConsole();
void trierOperations();
void triTopologique();
float calculerSommeTemps();
void repartirEnStations(float tempsCycle);


#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_6_97_GIT_HEADER_H
