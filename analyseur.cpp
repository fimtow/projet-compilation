#include<stdio.h>
#include<stdlib.h>

// Lire le fichier source
const char* fileName = "testf.txt";
FILE *fileSrc = fopen(fileName, "r");

#include "functions.c"

int main(){
    int k;
    token currentToken = getToken();
    do{
         k = (int) currentToken.name;
        
         printf("%s\n ", tokens[k]);
         currentToken = getToken(); 
    }while(currentToken.name != EOF_TOKEN);
    printf("\n\n");
    system("pause");
    return 0;
}
