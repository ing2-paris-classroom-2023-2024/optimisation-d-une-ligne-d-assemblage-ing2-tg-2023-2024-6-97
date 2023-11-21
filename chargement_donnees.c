#include "header.h"

void chargementGrapheOriente() {
    FILE* precedences = fopen("precedences.txt", "r");
    FILE* durees = fopen("operations.txt", "r");

    if (precedences == NULL || durees == NULL) {
        printf("Erreur lors de l'ouverture des fichiers.\n");
        exit(1);
    }

}