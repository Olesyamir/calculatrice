#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#include "analyse_syntaxique.h"
#include "lecture_caracteres.h"
#include "analyse_lexicale.h"


void aff_lex(){
    afficher(lexeme_courant());
    printf("\n");
}

// Rec_op =
// selon LC().nature
// cas PLUS, MUL, MOINS : Avancer
// autre : Erreur
// fin

void rec_op(){
    Lexeme LC = lexeme_courant();

    switch (LC.nature){
        // avancer();
    case PLUS:
    case MUL:
    case MOINS:
    case DIV:
        aff_lex();
        avancer();
        break;
    default:
        aff_lex();
        printf("Erreur syntaxique - op");
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

void rec_eaep(){
    Lexeme LC = lexeme_courant();

    switch (LC.nature){
        case ENTIER:
            aff_lex();
            avancer();
            break;

        case PARO_lex:
            aff_lex();

            avancer(); //
            rec_eaep();
            rec_op();
            rec_eaep();

            Lexeme LC = lexeme_courant();

            if (LC.nature == PARF_lex){
                aff_lex();
                avancer();
            }
            else {
                printf("Erreur syntaxique - par pas ferme");
                exit(0);
            }

            break;
        // autre : Erreur
        default:
            printf("Erreur syntaxique - def");
            exit(0);
        }
}



void analyser(char *nom_fichier) {
    demarrer(nom_fichier);
    rec_eaep();
    if (lexeme_courant().nature != FIN_SEQUENCE) {
        printf("Erreur syntaxique ???");
        exit(0);
    }
    arreter();
}


// void analyser(char *nom_fichier) {
    
// }