#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "lexer.h"
#include "common.h"
#include "parser.h"

void Check_Token(codesLex nametoken)
{	
	
	if(symCour.code == nametoken )
	{	
		symSuiv();
	}
	else
	{
        
		erreur( (codesErr) nametoken + 4);
	}
}

void PORGRAM()
{
    COMPONENT();
    C();
}

void C()
{   
    switch(symCour.code)
    {   
        case ID_TOKEN : COMPONENT(); C(); break;
        case FIN_TOKEN : break; 
        default : erreur(C_ERROR);
    }
}

void COMPONENT()
{
    Check_Token(ID_TOKEN);
    ISCOMPONENT();
    Check_Token(NEWLINE_TOKEN);
    Check_Token(INDENT_TOKEN);
    PROCEDURE();
    P();
    Check_Token(DEDENT_TOKEN);
}

void P()
{
    switch(symCour.code)
    {
        case ID_TOKEN :  PROCEDURE(); P(); break;
        case DEDENT_TOKEN : break;
        default : erreur(P_ERROR);                 
    }
}

void ISCOMPONENT()
{   
    switch(symCour.code)
    {
        case IS_TOKEN : symSuiv(); Check_Token(ID_TOKEN); break;
        case NEWLINE_TOKEN : break;
        default : erreur(ISCOMP_ERROR);
    }
}

void PROCEDURE()
{
    Check_Token(ID_TOKEN);
    Check_Token(PO_TOKEN);
    TYPE();
    Check_Token(ID_TOKEN);
    T();
    Check_Token(PF_TOKEN);
    INSTRUCTIONS();
}

void T()
{   
    switch(symCour.code)
    {   
        case VIR_TOKEN :  symSuiv(); TYPE(); Check_Token(ID_TOKEN); T(); break;
        case PF_TOKEN : break;
        default : erreur(T_ERROR);
    }
}

void INSTRUCTIONS()
{
    Check_Token(NEWLINE_TOKEN);
    Check_Token(INDENT_TOKEN);
    INSTRUCTION();
    I();
    Check_Token(DEDENT_TOKEN);
}

void I()
{
    if(symCour.code == ID_TOKEN 
        || symCour.code == ID_TOKEN 
        || symCour.code == IF_TOKEN 
        || symCour.code == WHILE_TOKEN 
        || symCour.code == FOR_TOKEN 
        || symCour.code == NUMBER_TOKEN 
        || symCour.code == STR_TOKEN
        || symCour.code == BOOL_TOKEN )
    {
        INSTRUCTION();
        I();
    }
    else if (symCour.code == DEDENT_TOKEN)
    {}
    else
    {
        erreur(I_ERROR);
    }
}

void INSTRUCTION()
{
    switch(symCour.code)
    {
        case ID_TOKEN  :    symSuiv();
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
        default : erreur(INST_ERROR);
    }
}

void INST()
{
    switch(symCour.code)
    {
        case AFF_TOKEN : AFFEC();
                        break;

        case PO_TOKEN :  APPEL();
                       break;

        case PT_TOKEN: OBJ() ;    
                    break;
        default : erreur(INS_ERROR);    
    }
}

void OBJ()
{
    Check_Token(PT_TOKEN);
    Check_Token(ID_TOKEN);
    APPEL();
}

void AFFEC()
{
    
    EXPR(AFF_TOKEN);
    EXPR();
}

void APPEL()
{
    Check_Token(PO_TOKEN);
    K();
}

void K()
{
    switch(symCour.code)
    {
        case PF_TOKEN :   symSuiv();
                        break;
        case ID_TOKEN:   symSuiv();
                        Z();
                        Check_Token(PF_TOKEN);
                        break;
        default : erreur(K_ERROR);
    }
}

void Z()
{
    switch(symCour.code)
    {
        case VIR_TOKEN:   symSuiv();
                        Check_Token(ID_TOKEN);
                        Z();
                        break;
        case PF_TOKEN :   break;
        default : erreur(Z_ERROR);
    }
}

void DECLARATION()
{
    TYPE();
    Check_Token(ID_TOKEN);
    X();
    Check_Token(NEWLINE_TOKEN);
}

void X()
{
    switch(symCour.code)
    {
        case AFF_TOKEN:   AFFEC();
                            break;
        case NEWLINE_TOKEN : break;
        default:   erreur(X_ERROR);
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
    switch(symCour.code)
    {
        case ELSEIF_TOKEN : symSuiv();
                            CONDITION();
                            Check_Token(DO_TOKEN);
                            INSTRUCTIONS();
                            ELSEIF();
                            break;
        case ELSE_TOKEN : break;
        default: erreur(ELSEIFCOMP_ERROR);
    }
}

void ELSE()
{
    switch(symCour.code)
    {
        case ELSE_TOKEN :   symSuiv();
                            INSTRUCTIONS();
                            break;
        case DEDENT_TOKEN: break;
        case ID_TOKEN: break;
        case IF_TOKEN: break;
        case WHILE_TOKEN: break;
        case FOR_TOKEN: break;
        case NUM_TOKEN: break;
        case STR_TOKEN: break;
        case BOOL_TOKEN: break;
        default:  erreur(ELSECOMP_ERROR);
                            
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
    Check_Token(ID_TOKEN);
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
    switch(symCour.code)
    {
        case WITH_TOKEN :   symSuiv();
                            EXPR(); 
                            break;
        case DO_TOKEN : break;
        default:  erreur(STEP_ERROR);
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
    switch(symCour.code)
    {
        case EG_TOKEN :  symSuiv();
                        break;
        case INF_TOKEN :     Check_Token(INF_TOKEN);
                            break;
        case SUP_TOKEN:      Check_Token(SUP_TOKEN);
                            break;
        case INFEG_TOKEN :  Check_Token(INFEG_TOKEN);
                            break;
        case SUPEG_TOKEN :  Check_Token(SUPEG_TOKEN);
                            break;    
        case DIFF_TOKEN:    Check_Token(DIFF_TOKEN);   
                            break;
        default:  erreur(OP_ERROR);
    }                   
}

void EXPR()
{
    TERM();
    M();
}

void M()
{   
    if(symCour.code == PLUS_TOKEN || symCour.code == MOINS_TOKEN  )
    {
            MP();
            TERM();
            M();
    }
    else if (symCour.code == EG_TOKEN || symCour.code == DIFF_TOKEN || symCour.code == SUP_TOKEN || symCour.code == INF_TOKEN || symCour.code == SUPEG_TOKEN || symCour.code == INFEG_TOKEN || symCour.code == WITH_TOKEN || symCour.code == DO_TOKEN)
    {}
    else{
        erreur(M_ERROR);
    }

}

void MP()
{
    switch(symCour.code)
    {
        case PLUS_TOKEN:    Check_Token(PLUS_TOKEN);
                            break;
        case MOINS_TOKEN:   Check_Token(MOINS_TOKEN);
                            break;
        default:  erreur(MP_ERROR);
    }
}

void TERM()
{
    FACT();
    R();
}

void R()
{
    if(symCour.code == DIV_TOKEN || symCour.code == MULT_TOKEN  )
    {
            MD();
            FACT();
            R();
    }
    else if (symCour.code == EG_TOKEN || symCour.code == DIFF_TOKEN || symCour.code == SUP_TOKEN || symCour.code == INF_TOKEN || symCour.code == SUPEG_TOKEN || symCour.code == INFEG_TOKEN || symCour.code == WITH_TOKEN || symCour.code == DO_TOKEN || symCour.code == PLUS_TOKEN || symCour.code == MOINS_TOKEN)
    {}
    else{
        erreur(R_ERROR);
    }
}

void MD()
{
    switch(symCour.code )
    {
        case DIV_TOKEN:    Check_Token(DIV_TOKEN);
                            break;
        case MULT_TOKEN:    Check_Token(MULT_TOKEN);
                            break;
        default:  erreur(MD_ERROR);
    }
}

void FACT()
{
    switch(symCour.code)
    {
        case ID_TOKEN :    Check_Token(ID_TOKEN);
                            break;
        case NUMBER_TOKEN : Check_Token(NUMBER_TOKEN);
                            break;
        case PO_TOKEN : symSuiv();
                        EXPR();
                        Check_Token(PF_TOKEN);
                        break;
        default:  erreur(FACT_ERROR);
    }
}

void TYPE()
{
    switch(symCour.code)
    {
        case NUM_TOKEN:     Check_Token(NUM_TOKEN);
                            break;
        case STR_TOKEN:     Check_Token(STR_TOKEN);
                            break;
        case BOOL_TOKEN:    Check_Token(BOOL_TOKEN);
                            break;
        default:    erreur(TYPE_ERROR);
    }
}