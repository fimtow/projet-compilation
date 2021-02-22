#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "lexical.c"




// Fonction de l'analyseur Syntaxique 
void Check_Token(nameToken nametoken);
void Erreur(CODES_ERR erreur);
void PROGRAM();
void C();
void COMPONENT();
void P();
void ISCOMPONENET();
void PROCEDURE();
void T();
void INSTRUCTIONS();
void I();
void INSTRUCTION();
void INST();
void OBJ();
void AFFEC();
void APPEL();
void K();
void Z();
void DECLARATION();
void X();
void IF();
void ELSEIF();
void ELSE();
void WHILE();
void FOR();
void STEP();
void CONDITION();
void OP();
void EXPR();
void M();
void MP();
void TERM();
void R();
void MD();
void FACT();
void TYPE();


int main()
{   
    PROGRAM();
    return 1;

}

void Check_Token(nameToken nametoken)
{	
	
	if(currentToken.name == nametoken )
	{	
		
		currentToken = getToken();
		
	}
	else
	{
		// Erreur(erreur); a ajouter plus tard
		
	}
}
/*
void Erreur(CODES_ERR erreur)
{	
	
	switch(erreur)
	{
		printf("erreur ")
	}
	printf("\n");
	return;	
}
*/

void PORGRAM()
{
    COMPONENT();
    C();
}

void C()
{   
    switch(currentToken.name)
    {   
        case IDF_TOKEN : COMPONENT();
                         C();  
        default : // Erreur 
    }
}

void COMPONENT()
{
    Check_Token(IDF_TOKEN);
    ISCOMPONENET();
    Check_Token(NEWLINE_TOKEN);
    Check_Token(INDENT_TOKEN);
    PROCEDURE();
    P();
    Check_Token(DEINDENT_TOKEN);
}

void P()
{
    switch(currentToken.name)
    {
        case IDF_TOKEN :  PROCEDURE();
                          P();
        default : // Erreur                  
    }
}

void ISCOMPONENET()
{   
    switch(currentToken.name)
    {
        case IS_TOKEN : currentToken = getToken();
                        Check_Token(IDF_TOKEN);
        default : // Erreur
    }
}

void PROCEDURE()
{
    Check_Token(IDF_TOKEN);
    Check_Token(OPEN_PARENS_TOKEN);
    TYPE();
    Check_Token(IDF_TOKEN);
    T();
    Check_Token(CLOSE_PARENS_TOKEN);
    INSTRUCTIONS();
}
void T()
{   
    switch(currentToken.name)
    {   
        case COMMA_TOKEN :  currentToken = getToken();
                            TYPE();
                            Check_Token(IDF_TOKEN);
                            T();
        default : // Erreur 
    }
}
void INSTRUCTIONS()
{
    Check_Token(NEWLINE_TOKEN);
    Check_Token(INDENT_TOKEN);
    INSTRUCTION();
    I();
    Check_Token(DEINDENT_TOKEN);

}
void I()
{
    if(currentToken.name = IDF_TOKEN 
        || currentToken.name = IDF_TOKEN 
        || currentToken.name = IF_TOKEN 
        || currentToken.name = WHILE_TOKEN 
        || currentToken.name = NUMBER_TOKEN 
        || currentToken.name = STR_TOKEN
        || currentToken.name = BOOL_TOKEN )
    {
        currentToken = getToken();
        I();
    }
    else
    {
        // Erreur 
    }
}
void INSTRUCTION()
{
    switch(currentToken.name)
    {
        case IDF_TOKEN  :   currentToken = getToken();
                            INST();
                            Check_Token(NEWLINE_TOKEN);
                            break;

        case IF_TOKEN   :   IF();
                            break;

        case WHILE_TOKEN:   WHILE();
                            break;

        case FOR_TOKEN  :   FOR();
                            break;

        case NUM_TOKEN:    DECLARATION();
                            break;
        case STR_TOKEN:   DECLARATION();
                            break;
        case BOOL_TOKEN:  DECLARATION();
                            break;
        default : // Erreur
    }
}
void INST()
{
    switch(currentToken.name)
    {
        case OP_EQ_TOKEN:           APPEL();
                                    break;

        case OPEN_PARENS_TOKEN :    APPEL();
                                    break;

        case COMMA_TOKEN:           OBJ() ;    
                                    break;
        default : //ERREUR                
    }
}
void OBJ()
{
    Check_Token(COMMA_TOKEN);
    Check_Token(IDF_TOKEN);
    APPEL();
}
void AFFEC()
{
    
    EXPR(OP_EQ_TOKEN);
    EXPR();
}
void APPEL()
{
    Check_Token(OPEN_PARENS_TOKEN);
    K();
}
void K()
{
    switch(currentToken.name)
    {
        case CLOSE_PARENS_TOKEN :   currentToken = getToken();
                                    break;
        case IDF_TOKEN:             currentToken = getToken();
                                    Z();
                                    Check_Token(CLOSE_PARENS_TOKEN);
        default : // Erreur
    }
}

void Z()
{
    switch(currentToken.name)
    {
        case COMMA_TOKEN:   currrentToken = getToken();
                            Check_Token(IDF_TOKEN);
                            Z();
        default :           // Erreur
    }
}

void DECLARATION()
{
    TYPE();
    Check_Token(IDF_TOKEN);
    X();
    Check_Token(NEWLINE_TOKEN);
}

void X()
{
    switch(currentToken.name)
    {
        case OP_EQ_TOKEN:   AFFEC();
                            break;
        default:            //Erreur
    }
}
void IF()
{
    Check_Token(IF_TOKEN);
    CONDITION();
    Check_Token(DO_TOKEN);
    INSTRUCTIONS();
    ELSEIF();
    ELSE();
}
void ELSEIF()
{   
    switch(currentToken.name)
    {
        case ELSEIF_TOKEN : currentToken = getToken();
                            CONDITION();
                            Check_Token(DO_TOKEN);
                            INSTRUCTIONS();
                            ELSEIF();
        default:            //erreur
    }
}
void ELSE()
{
    switch(currentToken.name)
    {
        case ELSE_TOKEN :   currentToken = getToken();
                            INSTRUCTIONS();
        default:            //erreur;
                            
    }
}
void WHILE()
{
    Check_Token(WHILE_TOKEN);
    CONDITION();
    Check_Token(DO_TOKEN);
    INSTRUCTIONS();
}
void FOR()
{
    Check_Token(FOR_TOKEN);
    Check_Token(IDF_TOKEN);
    Check_Token(FROM_TOKEN);
    EXPR();
    Check_Token(TO_TOKEN);
    EXPR();
    STEP();
    Check_Token(DO_TOKEN);
    INSTRUCTIONS();
}
void STEP()
{   
    switch(currentToken.name)
    {
        case WITH_TOKEN :   currentToken = getToken();
                            EXPR(); 
        default:            //Erreur 
    }

}
void CONDITION()
{
    EXPR();
    OP();
    EXPR();
}
void OP()
{
    switch(currentToken.name)
    {
        case OP_EQ_TOKEN :  Check_Token(OP_EQ_TOKEN);
                            break;
        case LT_TOKEN :     Check_Token(LT_TOKEN);
                            break;
        case GT_TOKEN:      Check_Token(GT_TOKEN);
                            break;
        case OP_GE_TOKEN :  Check_Token(OP_GE_TOKEN);
                            break;
        case OP_LE_TOKEN :  Check_Token(OP_LE_TOKEN);
                            break;    
        case DIFF_TOKEN:    Check_Token(DIFF_TOKEN);   
                            break;
        default:            //Erreur
    }                   
}
void EXPR()
{
    TERM();
    M();
}
void M()
{   
    if(currentToken.name == PLUS_TOKEN || currentToken.name == MINUS_TOKEN  )
    {
            MP();
            TERM();
            M();
    }
    else{
        //erreur;
    }

}
void MP()
{
    switch(currentToken.name )
    {
        case PLUS_TOKEN:    Check_Token(PLUS_TOKEN);
                            break;
        case MINUS_TOKEN:   Check_Token(MINUS_TOKEN);
                            break;
        default:        //erreur
    }
}
void TERM()
{
    FACT();
    R();
}
void R()
{
    if(currentToken.name == DIV_TOKEN || currentToken.name == STAR_TOKEN  )
    {
            MD();
            FACT();
            R();
    }
    else{
        //Erreur
    }
}
void MD()
{
    switch(currentToken.name )
    {
        case DIV_TOKEN:    Check_Token(DIV_TOKEN);
                            break;
        case STAR_TOKEN:    Check_Token(STAR_TOKEN);
                            break;
        default:            //Erreur
    }
}
void FACT()
{
    switch(currentToken.name)
    {
        case IDF_TOKEN :    Check_Token(IDF_TOKEN);
                            break;
        case NUM_TOKEN :    Check_Token(NUM_TOKEN);
                            break;
        case OPEN_PARENS_TOKEN :    currentToken = getToken();
                                    EXPR();
                                    Check_Token(CLOSE_PARENS_TOKEN);
                                    break;
        default:            //Erreur
    }
}
void TYPE()
{
     switch(currentToken.name )
    {
        case NUM_TOKEN:     Check_Token(NUM_TOKEN);
                            break;
        case STR_TOKEN:     Check_Token(STR_TOKEN);
                            break;
        case BOOL_TOKEN:    Check_Token(BOOL_TOKEN);
                            break;
        default:    //Erreur
    }
    
}
