#include <stdio.h>
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
    while(rester)
    {
        symSuiv();
        afficherToken();
    }
    getchar();
    return 1;
}