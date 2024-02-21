// Ecrivez un programme principal calculette.c qui appelle la procedure analyser() ;
#include <stdio.h>
#include <stdlib.h>
#include "analyse_syntaxique.h"


int main (int argc, char *argv[]) {
    int *resultat = malloc(sizeof(int));
    switch (argc) {
            case 1:
            // demarre l'analyse lexicale sur stdin
            analyser ("", resultat); 
                    break ;
            case 2:
            // demarre l'analyse lexicale sur le fichier transmis en argument
            analyser (argv[1], resultat); 
                    break ;
            default:
                    printf("nombre d'arguments incorrects !\n");
                    exit(1) ;
    } ;
        printf("Resultat de calcul : %d\n", *resultat);
        return 0 ;
}
