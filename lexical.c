#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define IDFSIZE 50 // taille maximal d'un identificateur
#define NUMBERSIZE 32 // talle maximal d'un nombre
#define VARCHARSIZE 225 // taille maximal d'un variable texte

#include "scanner.h"

int keyword_token_size = sizeof(keyword_token)/sizeof(keyword_token[0]); // le nombre de cases de la table keyword_token
int symbole_token_size = sizeof(symbole_token)/sizeof(symbole_token[0]); // le nombre de cases de la table symbole_token
int indent=0;
int dedent=0;
int ind_deind[100];

boolean isNumber = FALSE;
//----- Les prototypes des fonctions :
boolean isAlphabetic(char c);
boolean isNumeric(char c);
int caractereSpecial(char c);
numberToken getNumber(char digit, boolean isNegative);
token getToken();

//----- Les fonctions -------------- :

// savoir si un caractère est une alphabet
boolean isAlphabetic(char c){
     if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_'){
        return TRUE;
     }
     return FALSE;
}
// savoir si un caractère est un chiffre
boolean isNumeric(char c){
     if(c >= '0' && c <= '9'){
         return TRUE;
     }
     return FALSE;
}
// savoir si un caractère est un symbole simple
// retourne son numéro dans nameToken si caractère est un symbole simple, -1 sinon
int caractereSpecial(char c){
    int i = 0;
    int symbole = (int) STAR_TOKEN; // STAR_TOKEN est le premier symbole simple dans nameToken
    while(i < symbole_token_size){
          if(c == symbole_token[i]){
               symbole = symbole + i;
               return symbole;
          }
          i++;
    }
    return -1;
}
numberToken getNumber(char digit, boolean isNegative){
     int i=0;
     // variable qui indique s'il s'agit d'un entier ou un flottant
     boolean isInt = TRUE;
     // Allocation de la mémoire
     char* memory = (char *)malloc(NUMBERSIZE*sizeof(char));
     numberToken A;
     // Lire tout le chiffre
     do{
         memory[i] = digit;
         digit = fgetc(fileSrc); // caractère suivant
         i++;
         if(digit == '.'){ // si on arrive à une virgule (un nombre flottant
              isInt = FALSE;
              memory[i] = '.';
              digit = fgetc(fileSrc); // Lire le caractère suivant
              i++;
         }
     }while(isNumeric(digit) == TRUE);
     memory[i] = '\0';
     /*
       on sort de doo..while Lorsqu'on lit un caractère non numérique
       il faut retourner le curseur pour que cette caractère ne soit perdu
     */
     ungetc(digit, fileSrc);
     A.isInt = isInt;
     if(isInt == TRUE){ // un nombre entier
          // transformer le nombre dans la chaine de caractère memory en int et le stoker dans A.value.n
          A.value.n = atoi(memory);
          if(isNegative == TRUE){
               A.value.n = - A.value.n;
          }
     }else{ // un nombre flottant
          // transformer le nombre dans la chaine de caractère memory en float et le stoker dans A.value.x
          A.value.x = atof(memory);
          if(isNegative == TRUE){
               A.value.x = - A.value.x;
          }
     }
     return A;
}
token getToken(){
      // Lire le caractère suivant
      char character = fgetc(fileSrc);
      token A;
      int i = 0;
      boolean previousIsNumer = isNumber;
      isNumber = FALSE;
      // Eliminer les blancs
      if(character == ' ' || character == '\t' ){
           return getToken();
      }
      // Reconnaissance des mots-clé et des identificateurs
       else if(isAlphabetic(character) == TRUE){
           // Allocation de la mémoire pour sauvegarder le mot
           A.properties.idf.name = (char *)malloc(IDFSIZE*sizeof(char));
           // Lire tout le mot
           do{
              A.properties.idf.name[i] = character;
              character = fgetc(fileSrc); // Lire le caractère suivant
              i++;
           }while(isAlphabetic(character) == TRUE || isNumeric(character) == TRUE);
           A.properties.idf.name[i] = '\0'; // il faut poser \0 à la fin du mot
           /*
            La fonction do..while sort Lorsqu'elle lit un non alpha-numérique caractère
            il faut retourner en arrière le curseur par la fonction ungetc()
            pour que ce caractère ne soit perdu, et il va être analyser
            dans le prochain appelle de la fonction getToken()
           */
           ungetc(character, fileSrc);
           i = 0;
            printf("%s ",A.properties.idf.name);
           // vérifier si lo mot obtenue est un mot-clé :
           while(i < keyword_token_size){
                if(strcmp(A.properties.idf.name, keyword_token[i]) == 0){ // Le mot est un mot-clé
                    // Le nom token c'est (nameToken) i
                    A.name = (nameToken) i;
                    // Libérer la case mémoire A.properties.idf.name
                    // On a besoin du nom de token seulement dans ce cas (et pas sa valeur)
                    free(A.properties.idf.name);
                    return A; // retourner le token 
                }
                i++;
           }
           //on cherche si c'est une fonction
           
           if(character=fgetc(fileSrc)=='(')
           {
           	 A.name = FUNCTION_TOKEN;
           	  
           	 free(A.properties.idf.name);
           	
           return A;
		   }
		   // Si on arrive à cette étape, le mot n'est pas mot-clé et n'est pas un nom de fonction
           // Donc c'est un identificateur, et son nom est stocké dans A.properties.idf.name
           A.name = IDF_TOKEN;
           return A; // retourner le token
      }
      // Reconnaissance des nombres
      else if(isNumeric(character) == TRUE){
           // le token est un nombre ==> isNumber = TRUE;
           isNumber = TRUE;
           A.name = NUMBER_TOKEN;
           // récupérer le nombre et le stocker dans A.properties.number
           A.properties.number = getNumber(character, FALSE);
           return A;
      }
      else if(character == '+' || character == '-'){
           nameToken symboleToken = (character == '+' ? PLUS_TOKEN : MINUS_TOKEN);
           boolean isNegative = (character == '-' ? TRUE : FALSE);
           
           // Si le caractère suivant de +/- est un chiffre
           if(isNumeric(character) == TRUE){
                // le token précédant est un nombre, exemple de cette situation : "5 - 3"
                if(previousIsNumer == TRUE){
                     ungetc(character, fileSrc);
                     A.name = symboleToken;
                     return A;
                }else{ // le token précédant n'est pas un nombre, exemple cette situation : "= - 3"
                     isNumber = TRUE;
                     A.name = NUMBER_TOKEN;
                     A.properties.number = getNumber(character, isNegative);
                     return A;
                }
           }else{ // Le caractère suivant de +/- n'est pas un chiffre
                ungetc(character, fileSrc);
                A.name = symboleToken;
                return A;
           }
      }
      // Reconnaissance des variables textes
      else if(character == '"' || character == '\''){
           i = 0;
           // type de délimiteure de texte : ' ou "
           char d = character;
           // caractère precédant de character, valeur initiale : tout caractère différent de '\'
           char previousC = ' ';
           // Lire le caractère suivant
           character = fgetc(fileSrc);
           // Allocation mémoire pour sauvegarder le texte
           A.properties.varchar.value = (char *)malloc(VARCHARSIZE*sizeof(char));
           // Lire le texte
           while((character != d || (character == d && previousC == '\\')) && character != EOF){
               A.properties.varchar.value[i] = character;
               character = fgetc(fileSrc);
               i++;
               previousC = A.properties.varchar.value[i-1];
           }
           A.properties.varchar.value[i] = '\0';
           A.name = VARCHAR_TOKEN;
           A.properties.varchar.c = d;
           return A;
      }
      // Elimination des commentaires
      else if(character == '/'){
           // Lire le caractère suivant
           character = fgetc(fileSrc);
           if(character == '/'){ // un commentaire ligne
                // dépasser tous les caractères jusqu'on arrive à \n
    			do{
    				character = fgetc(fileSrc);
    			}while(character != '\n' && character != EOF);
    			return getToken(); // rappeler la fonction
           }
           else if(character == '*'){ // un commentaire bloque
                // dépasser tous les caractères jusqu'on arrive à */
    			do{
    				character = fgetc(fileSrc);
    			}while(character != '*');
    			// Lire le caractère suivant
    			character = fgetc(fileSrc);
    			if(character == '/'){ // Fin du commentaire bloque
                      return getToken(); // rappeler la fonction
                }
           }
           // Le caractère suivant de / n'est ni / ni *
           else{
                // symbole division
                A.name = DIV_TOKEN;
                ungetc(character, fileSrc);
                return A;
           }
      }
       
      // Reconaissance des symoboles simples
      else if((i = caractereSpecial(character)) > -1){
           A.name = (nameToken) i;
           return A;
      }
      // Reconnaissance de =, ==
      else if(character == '='){
          
                A.name = ASSIGNMENT_TOKEN;
                return A;
           
      }
      // Reconnaissance de >, >=
      else if(character == '>'){
           // Lire le caractère suivant
           character = fgetc(fileSrc);
           if(character == '='){ // On a le symbole >=
                A.name = OP_GE_TOKEN;
                return A;
           }else{ // On a le symbole >
                A.name = GT_TOKEN;
                ungetc(character, fileSrc);
                return A;
           }
      }
      // Reconnaissance de <, <=
      else if(character == '<'){
           // Lire le caractère suivant
           character = fgetc(fileSrc);
           if(character == '='){ // On a le symbole <=
                A.name = OP_LE_TOKEN;
                return A;
           }else{ // On a le symbole <
                A.name = LT_TOKEN;
                ungetc(character, fileSrc);
                return A;
           }
      }
      // La fin de la lecture
      else if(character == EOF){
           A.name = EOF_TOKEN;
           return A;
      }
      
      else if(character == '\n')
      
         {
           A.name =NEWLINE_TOKEN;
           return A;}
      // Si on rencontre d'autre caractères non analysés
      else{
           A.name = ERROR_TOKEN;
           return A;
      }
}
