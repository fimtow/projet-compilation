#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "lexer.h"


int main()
{
    ouvrirFichier("test.txt");
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