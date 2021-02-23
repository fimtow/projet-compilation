#include "lexer.h"

char* messagesErr[] = {
    "Erreur lexicale : caractere inconnu",
    "Erreur lexicale : fichier vide",
    "Erreur lexicale : indentifiant tres long",
    "Erreur lexicale : constante numerique tres longue",
    "Erreur de syntaxe : on expectait un identificateur",
    "Erreur de syntaxe : on expectait le symbole d'egalite",
    "Erreur de syntaxe : on expectait un nombre",
    "Erreur de syntaxe : on expectait un point virgule",
    "Erreur de syntaxe : on expectait une constante",
    "Erreur de syntaxe : on expectait un programme",
    "Erreur de syntaxe : on expectait un point",
    "Erreur de syntaxe : on expectait une variable",
    "Erreur de syntaxe : on expectait le mot cle BEGIN",
    "Erreur de syntaxe : on expectait le mot cle END",
    "Erreur de syntaxe : on expectait une affectation",
    "Erreur de syntaxe : on expectait un IF",
    "Erreur de syntaxe : on expectait le mot cle THEN",
    "Erreur de syntaxe : on expectait le mot cle WHILE",
    "Erreur de syntaxe : on expectait le mot cle DO",
    "Erreur de syntaxe : on expectait le mot WRITE",
    "Erreur de syntaxe : on expectait une parenthese ouverte",
    "Erreur de syntaxe : on expectait une parenthese ferme",
    "Erreur de syntaxe : on expectait le mot cle READ",
    "Erreur de syntaxe : on expectait une condition",
    "Erreur de syntaxe : on expectait un facteur",
    "Erreur de syntaxe : on expectait une instruction",
    "Erreur semantique : double declaration",
    "Erreur semantique : on ne peut affecter une valeur qu'a une variable",
    "Erreur semantique : le nom du programme est non autorise",
    "Erreur semantique : identificateur non declare",
    "Commande errone : utiliser comme suit : parser nomprogramme"
};

void erreur(codesErr err)
{
    printf("[ligne %d] %s",line,messagesErr[err]);
    getchar();
    exit(1);
}