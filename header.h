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

/* Structure d'un arc*/
struct Arc {
    int sommet; // numéro de sommet d'un arc adjacent au sommet initial
    struct Arc* arc_suivant;
};
typedef struct Arc* pArc; /* Alias de pointeur sur un Arc */

/* Structure d'un sommet*/
struct Sommet {
    struct Arc* arc;
    int *exclu; ///Stocke les id des sommets exclus
    int poids; //Poids du sommet (représente le temps d'exécution d'une machine)
    int visite;
    int id;     //ID du sommet
};
typedef struct Sommet* pSommet; /* Alias de pointeur sur un Sommet */

/* Structure d'un graphe*/
typedef struct Graphe {
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

Graphe chargementGrapheOriente();


#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_6_97_GIT_HEADER_H
