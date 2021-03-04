#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

void Check_Token(codesLex nametoken);
void PROGRAM();
void COMPONENTS();
void COMPONENT();
void CONTENU();
void PROCEDURES();
void ISCOMPONENT();
void PROCEDURE();
void PARAMS();
void SUITEPARAMS();
void INSTRUCTIONS();
void SUITEINSTRUCTIONS();
void INSTRUCTION();
void INST();
void OBJ();
void AFFEC();
void CONTAFFEC();
void APPEL();
void VALEURS();
void SUITEVALEURS();
void DECLARATION();
void AVECAFFEC();
void IF();
void ELSEIF();
void ELSE();
void WHILE();
void FOR();
void PAS();
void EXPRESSION();
void DISJONCTION();
void CONJONCTION();
void SUITECONJONCTION();
void NEGATION();
void COMPARAISON();
void COMP();
void OP();
void EXPR();
void SUITEEXPR();
void MP();
void TERM();
void SUITETERM();
void MD();
void FACT();
void TYPE();

#endif