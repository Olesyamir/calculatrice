#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#include "analyse_syntaxique.h"
#include "lecture_caracteres.h"
#include "analyse_lexicale.h"


int evaluer(int vald, Nature_Lexeme op, int valg){
    switch (op){
    case PLUS:
        return vald + valg;
    case MOINS:
        return vald - valg;
    case MUL:
        return vald * valg;
    case DIV:
        return vald / valg;
    default:
        printf("Erreur operateur");
        exit(0);
        break;
    }
}

// Rec_op =
// selon LC().nature
// cas PLUS, MUL, MOINS : Avancer
// autre : Erreur
// fin

void rec_op(Nature_Lexeme *op){
    Lexeme LC = lexeme_courant();

    switch (LC.nature){
    case PLUS:
    case MUL:
    case MOINS:
    case DIV:
        *op = LC.nature;
        avancer();
        break;
    default:
        printf("Erreur syntaxique");
        exit(0);
    }

}


// Rec_eaep =
// selon LC().nature // LC est le lexeme_courant()
// cas ENTIER : Avancer
// cas PARO : Avancer ; Rec_eaep ; Rec_op ; Rec_eaep ;
// si LC().nature = PARF alors Avancer sinon Erreur
// autre : Erreur
// fin

void rec_eaep(int *valeur){
    Lexeme LC = lexeme_courant();
	int valg, vald;
    Nature_Lexeme op;

    switch (LC.nature){
        case ENTIER:
            *valeur = LC.valeur;
            avancer();
            break;

        case PARO_lex:
            avancer(); 
            rec_eaep(&valg);
            rec_op(&op);
            rec_eaep(&vald);
            *valeur = evaluer(valg, op, vald);
            Lexeme LC = lexeme_courant();

            if (LC.nature == PARF_lex){
                avancer();
            }
            else {
                printf("Erreur syntaxique - par pas ferme");
                exit(0);
            }

            break;
        // autre : Erreur
        default:
            printf("Erreur syntaxique");
            exit(0);
        }
}


void analyser(char *nom_fichier, int *resultat) {
    demarrer(nom_fichier);
    rec_eaep(resultat);
    if (lexeme_courant().nature != FIN_SEQUENCE) {
        printf("Erreur syntaxique");
        exit(0);
    }
    arreter();
}
