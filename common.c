#include "common.h"
#include "lexer.h"
#include <stdlib.h>
#include <stdio.h>

char* messagesErr[] = {
    "Erreur lexicale : caractere inconnu",
    "Erreur lexicale : fichier vide",
    "Erreur lexicale : indentifiant tres long",
    "Erreur lexicale : constante numerique tres longue",
    "Erreur de syntaxe : on expectait un identificateur",
    "Erreur de syntaxe : on expectait un nombre",
    "Erreur de syntaxe : on expectait une chaine de caractere",
    "Erreur de syntaxe : on expectait une erreur",
    "Erreur de syntaxe : on expectait le mot cle is",
    "Erreur de syntaxe : on expectait le mot cle for",
    "Erreur de syntaxe : on expectait le mot cle if",
    "Erreur de syntaxe : on expectait le mot cle elseif",
    "Erreur de syntaxe : on expectait le mot cle do",
    "Erreur de syntaxe : on expectait le mot cle else",
    "Erreur de syntaxe : on expectait le mot cle while",
    "Erreur de syntaxe : on expectait le mot cle from",
    "Erreur de syntaxe : on expectait le mot cle to",
    "Erreur de syntaxe : on expectait le mot cle with",
    "Erreur de syntaxe : on expectait le mot cle num",
    "Erreur de syntaxe : on expectait le mot cle str",
    "Erreur de syntaxe : on expectait le mot cle bool",
    "Erreur de syntaxe : on expectait le mot cle true",
    "Erreur de syntaxe : on expectait le mot cle false",
    "Erreur de syntaxe : on expectait un point",
    "Erreur de syntaxe : on expectait un plus",
    "Erreur de syntaxe : on expectait un moin",
    "Erreur de syntaxe : on expectait une multiplication",
    "Erreur de syntaxe : on expectait une division",
    "Erreur de syntaxe : on expectait une virgule",
    "Erreur de syntaxe : on expectait une affectation",
    "Erreur de syntaxe : on expectait un symbole inferieur",
    "Erreur de syntaxe : on expectait un symbole inferieur ou egal",
    "Erreur de syntaxe : on expectait un symbole superieur",
    "Erreur de syntaxe : on expectait un symbole superieur ou egal",
    "Erreur de syntaxe : on expectait un symbole different",
    "Erreur de syntaxe : on expectait une parenthese ouvrante",
    "Erreur de syntaxe : on expectait une parenthese fermante",
    "Erreur de syntaxe : on expectait la fin du programme",
    "Erreur de syntaxe : on expectait un symbole d'egalite",
    "Erreur de syntaxe : on expectait une nouvelle ligne",
    "Erreur de syntaxe : on expectait une indentation",
    "Erreur de syntaxe : on expectait une deindentation",
    "Erreur de syntaxe : on expectait C",
    "Erreur de syntaxe : on expectait P",
    "Erreur de syntaxe : on expectait IS",
    "Erreur de syntaxe : on expectait T",
    "Erreur de syntaxe : on expectait I",
    "Erreur de syntaxe : on expectait INST",
    "Erreur de syntaxe : on expectait INS",
    "Erreur de syntaxe : on expectait K",
    "Erreur de syntaxe : on expectait Z",
    "Erreur de syntaxe : on expectait X",
    "Erreur de syntaxe : on expectait ELSEIFCOMP",
    "Erreur de syntaxe : on expectait ELSECOMP",
    "Erreur de syntaxe : on expectait STEP",
    "Erreur de syntaxe : on expectait OP",
    "Erreur de syntaxe : on expectait M",
    "Erreur de syntaxe : on expectait MP",
    "Erreur de syntaxe : on expectait R",
    "Erreur de syntaxe : on expectait MD",
    "Erreur de syntaxe : on expectait FACT",
    "Erreur de syntaxe : on expectait TYPE",
};

void erreur(codesErr err)
{
    printf("[ligne %d] %s",line,messagesErr[err]);
    getchar();
    exit(1);
}