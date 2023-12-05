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
#define MAX_OPERATIONS 200

typedef struct precedences {
    int precedences[MAX_OPERATIONS][2]; //Matrice de precedences comme dans le fichier txt donc le sommet et sa colonne
    int tabSommets[MAX_OPERATIONS]; //Tableau de tous les sommets UNIQUES qui existent
    int existe[MAX_OPERATIONS]; //Tableau avec à la case du numéro du sommet soit 1 si le sommet existe, 0 sinon
    //Exemple pour le sommet 6 on est donc à la case 6-1 du tableau et on a 1 car ce sommet existe vraiment
    int nbOperations;

    int nbSommets; //Le nombre de sommets maximum qui existe dans le graphe (donc le plus grand numéro de sommet)

    int operationsTriees[MAX_OPERATIONS];
    int nbPredecesseurs[MAX_OPERATIONS];
    float temps[MAX_OPERATIONS];
} t_precedences;

///Structure spécifique pour l'exclusion ///Faite par Kimi'
// Structure spécifique pour les exclusions
typedef struct {
    int exclusions[MAX_OPERATIONS][2]; //Stocke les données comme dans le fihier txt, 2 sommets sur une ligne //Le 2 symbolise les 2 colonnes
    int tabSommetsExclus[MAX_OPERATIONS]; //Stocke la liste de tous les sommets UNIQUES qui ont au moins une exclusion
    int nbExclusions; //le nombre de lignes des exclusions donc pour avoir le nombre réel d'exclusions on fait nbExclusions*2
    int stations[MAX_OPERATIONS][MAX_OPERATIONS]; //Matrice des stations avec en 1ere valeur le numéro de la station et en 2e tous les sommets dans cette station.
    int nbStations; //Nombre de stations finales

    int sommetsNonExclus[MAX_OPERATIONS]; //Tab des sommets qui n'ont pas d'exclusion et qu'on ajoutera donc à la première station
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


//Temps de cycle
void lireTempsDesOpe(t_precedences *graph);
int repartirDansStations(t_precedences *graph);

void precedExclusion();
int repartirDansStationsMODIF(t_precedences *graph);


//Exclusions
void chargerExclusions(t_assemblage *assemblage, t_precedences *graph);
int regrouperActions(t_assemblage *assemblage, t_precedences *precedence);
void ajouterAStation(t_assemblage *assemblage, int sommet, int station);
void fusionnerStations(t_assemblage *assemblage, int station1, int station2);
void afficherStationsOptimisees(t_assemblage *assemblage);
void affichageStationsOptimisees(t_assemblage *assemblage, t_precedences *graph);

//Precedence + Temps cycle
void initialiserMatrice(t_precedences *graph);
void lireContraintePrecedence(t_precedences *graph);
void lireTempsOperations(t_precedences *graph);
void afficherGraphePrecedenceConsole(t_precedences *graph);
void trierOperations(t_precedences *graph);
void triTopologique(t_precedences *graph);
float calculerSommeTemps(t_precedences *graph);
void repartirEnStations(t_precedences *graph, float tempsCycle);



//Divers
void echanger(int *a, int *b);
void triBulle(int tableau[], int taille);


#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_6_97_GIT_HEADER_H
