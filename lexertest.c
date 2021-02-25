#include <stdio.h>
#include "lexer.h"

int main()
{
    ouvrirFichier("test.txt");
    lireCaractere();
    while(rester)
    {
        symSuiv();
        afficherToken();
    }
    getchar();
    return 1;
}