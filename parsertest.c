#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "lexer.h"


int main(int argc, char *argv[])
{
    if(argc > 2)
    {
        printf("Veuillez entrer le nom d'un seul fichier \n");
        return 1;
    }
    if(argc < 2)
    {
        printf("Veuillez entrer le nom fichier en prametre \n");
        return 1;
    }
    if(ouvrirFichier(argv[1]) == 0)
    {
        printf("Fichier inexistant \n");
        return 1;
    }
    lireCaractere();
    symSuiv();
    PROGRAM();
    if(symCour.code == FIN_TOKEN)
        printf("Le programme est correct");
    else
        printf("La fin du programme est erronee");
    getchar();
    return 1;
}