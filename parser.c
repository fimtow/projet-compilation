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

void PROGRAM()
{
    COMPONENT();
    COMPONENTS();
}

void COMPONENTS()
{   
    switch(symCour.code)
    {   
        case ID_TOKEN : COMPONENT(); COMPONENTS(); break;
        case FIN_TOKEN : break; 
        default : erreur(COMPONENTS_ERROR);
    }
}

void COMPONENT()
{
    Check_Token(ID_TOKEN);
    ISCOMPONENT();
    Check_Token(NEWLINE_TOKEN);
    CONTENU();
}

void CONTENU()
{
    switch (symCour.code)
    {
    case INDENT_TOKEN:
        Check_Token(INDENT_TOKEN);
        PROCEDURE();
        PROCEDURES();
        Check_Token(DEDENT_TOKEN);
        break;
    case ID_TOKEN:
        break;
    case FIN_TOKEN:
        break;
    default:
        erreur(CONTENU_ERROR);
    }
}

void PROCEDURES()
{
    switch(symCour.code)
    {
        case ID_TOKEN :  PROCEDURE(); PROCEDURES(); break;
        case DEDENT_TOKEN : break;
        default : erreur(PROCEDURES_ERROR);                 
    }
}

void ISCOMPONENT()
{   
    switch(symCour.code)
    {
        case IS_TOKEN : Check_Token(IS_TOKEN); Check_Token(ID_TOKEN); break;
        case NEWLINE_TOKEN : break;
        default : erreur(ISCOMP_ERROR);
    }
}

void PROCEDURE()
{
    Check_Token(ID_TOKEN);
    Check_Token(PO_TOKEN);
    PARAMS();
    Check_Token(PF_TOKEN);
    INSTRUCTIONS();
}

void PARAMS()
{
    if(symCour.code == STR_TOKEN || symCour.code == NUM_TOKEN || symCour.code == BOOL_TOKEN)
    {
        TYPE();
        Check_Token(ID_TOKEN);
        SUITEPARAMS();
    }
    else if (symCour.code == PF_TOKEN)
    {
        return;
    }
    else
    {
        erreur(PARAMS_ERROR);
    }
    
}

void SUITEPARAMS()
{   
    switch(symCour.code)
    {   
        case VIR_TOKEN :  symSuiv(); TYPE(); Check_Token(ID_TOKEN); SUITEPARAMS(); break;
        case PF_TOKEN : break;
        default : erreur(SUITEPARAMS_ERROR);
    }
}

void INSTRUCTIONS()
{    
    Check_Token(NEWLINE_TOKEN);
    Check_Token(INDENT_TOKEN);
    INSTRUCTION();
    SUITEINSTRUCTIONS();
    Check_Token(DEDENT_TOKEN);
}

void SUITEINSTRUCTIONS()
{
    if(symCour.code == ID_TOKEN 
        || symCour.code == IF_TOKEN 
        || symCour.code == WHILE_TOKEN 
        || symCour.code == FOR_TOKEN 
        || symCour.code == NUM_TOKEN 
        || symCour.code == STR_TOKEN
        || symCour.code == BOOL_TOKEN )
    {
        INSTRUCTION();
        SUITEINSTRUCTIONS();
    }
    else if (symCour.code == DEDENT_TOKEN)
    {}
    else
    {
        erreur(SUITEINSTRUCTIONS_ERROR);
    }
}

void INSTRUCTION()
{
    switch(symCour.code)
    {
        case ID_TOKEN  :    Check_Token(ID_TOKEN);
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
        default : erreur(INSTRUCTION_ERROR);
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
    Check_Token(AFF_TOKEN);
    CONTAFFEC();
}

void CONTAFFEC()
{
    if(symCour.code == STRING_TOKEN)
        Check_Token(STRING_TOKEN);
    else
        EXPRESSION();
}

void APPEL()
{
    Check_Token(PO_TOKEN);
    VALEURS();
}

void VALEURS()
{
    if(symCour.code == PF_TOKEN)
    {
        Check_Token(PF_TOKEN);
    }
    else
    {
        CONTAFFEC();
        SUITEVALEURS();
        Check_Token(PF_TOKEN);
    }
}

void SUITEVALEURS()
{
    switch(symCour.code)
    {
        case VIR_TOKEN:   Check_Token(VIR_TOKEN);
                        CONTAFFEC();
                        SUITEVALEURS();
                        break;
        case PF_TOKEN :   break;
        default : erreur(SUITEVALEURS_ERROR);
    }
}

void DECLARATION()
{
    TYPE();
    Check_Token(ID_TOKEN);
    AVECAFFEC();
    Check_Token(NEWLINE_TOKEN);
}

void AVECAFFEC()
{
    switch(symCour.code)
    {
        case AFF_TOKEN:   AFFEC();
                            break;
        case NEWLINE_TOKEN : break;
        default:   erreur(AVECAFFEC_ERROR);
    }
}

void IF()
{
    Check_Token(IF_TOKEN);
    EXPRESSION();
    Check_Token(DO_TOKEN);
    INSTRUCTIONS();
    ELSEIF();
    ELSE();
}

void ELSEIF()
{   
    switch(symCour.code)
    {
        case ELSEIF_TOKEN : Check_Token(ELSEIF_TOKEN);
                            EXPRESSION();
                            Check_Token(DO_TOKEN);
                            INSTRUCTIONS();
                            ELSEIF();
                            break;
        case ELSE_TOKEN : break;
        case DEDENT_TOKEN : break;
        case ID_TOKEN : break;
        case IF_TOKEN : break;
        case WHILE_TOKEN : break;
        case FOR_TOKEN : break;
        case STR_TOKEN : break;
        case BOOL_TOKEN : break;
        case NUM_TOKEN : break;
        default: erreur(ELSEIFCOMP_ERROR);
    }
}

void ELSE()
{
    switch(symCour.code)
    {
        case ELSE_TOKEN :   Check_Token(ELSE_TOKEN);
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
    EXPRESSION();
    Check_Token(DO_TOKEN);
    INSTRUCTIONS();
}

void FOR()
{
    Check_Token(FOR_TOKEN);
    Check_Token(ID_TOKEN);
    Check_Token(FROM_TOKEN);
    EXPRESSION();
    Check_Token(TO_TOKEN);
    EXPRESSION();
    PAS();
    Check_Token(DO_TOKEN);
    INSTRUCTIONS();
}

void PAS()
{   
    switch(symCour.code)
    {
        case WITH_TOKEN :   Check_Token(WITH_TOKEN);
                            EXPRESSION(); 
                            break;
        case DO_TOKEN : break;
        default:  erreur(PAS_ERROR);
    }

}

void EXPRESSION()
{
    CONJONCTION();
    DISJONCTION();
}

void DISJONCTION()
{
    switch (symCour.code)
    {
    case OR_TOKEN :
        Check_Token(OR_TOKEN);
        CONJONCTION();
        DISJONCTION();
        break;
    
    default:
        break;
    }
}

void CONJONCTION()
{
    NEGATION();
    SUITECONJONCTION();
}

void SUITECONJONCTION()
{
    switch (symCour.code)
    {
    case AND_TOKEN:
        NEGATION();
        SUITECONJONCTION();
        break;
    
    default:
        break;
    }
}

void NEGATION()
{
    switch (symCour.code)
    {
    case NOT_TOKEN:
        NEGATION();
        break;
    
    default:
        COMPARAISON();
        break;
    }
}

void COMPARAISON()
{
    EXPR();
    COMP();
}

void COMP()
{
   switch (symCour.code)
   {
   case EG_TOKEN:
   case DIFF_TOKEN:
   case INF_TOKEN:
   case INFEG_TOKEN:
   case SUP_TOKEN:
   case SUPEG_TOKEN:
        OP();
        EXPR();
        break;
   default:
       break;
   }
}

void OP()
{
    switch(symCour.code)
    {
        case EG_TOKEN :  Check_Token(EG_TOKEN);
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
    SUITEEXPR();
}

void SUITEEXPR()
{   
    if(symCour.code == PLUS_TOKEN || symCour.code == MOINS_TOKEN  )
    {
            MP();
            TERM();
            SUITEEXPR();
    }
    else if (symCour.code == EG_TOKEN || symCour.code == DIFF_TOKEN || symCour.code == SUP_TOKEN || symCour.code == INF_TOKEN || symCour.code == SUPEG_TOKEN || symCour.code == INFEG_TOKEN || symCour.code == WITH_TOKEN || symCour.code == DO_TOKEN || symCour.code == NEWLINE_TOKEN || symCour.code == TO_TOKEN || symCour.code == AND_TOKEN || symCour.code == OR_TOKEN || symCour.code == PF_TOKEN || symCour.code == VIR_TOKEN)
    {}
    else{
        erreur(SUITEEXPR_ERROR);
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
    SUITETERM();
}

void SUITETERM()
{
    if(symCour.code == DIV_TOKEN || symCour.code == MULT_TOKEN  )
    {
            MD();
            FACT();
            SUITETERM();
    }
    else if (symCour.code == EG_TOKEN || symCour.code == DIFF_TOKEN || symCour.code == SUP_TOKEN || symCour.code == INF_TOKEN || symCour.code == SUPEG_TOKEN || symCour.code == INFEG_TOKEN || symCour.code == WITH_TOKEN || symCour.code == DO_TOKEN || symCour.code == PLUS_TOKEN || symCour.code == MOINS_TOKEN ||  symCour.code == NEWLINE_TOKEN || symCour.code == TO_TOKEN || symCour.code == AND_TOKEN || symCour.code == OR_TOKEN || symCour.code == PF_TOKEN || symCour.code == VIR_TOKEN)
    {}
    else{
        erreur(SUITETERM_ERROR);
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
        case TRUE_TOKEN : Check_Token(TRUE_TOKEN);
                            break;
        case FALSE_TOKEN : Check_Token(FALSE_TOKEN);
                            break;
        case PO_TOKEN : Check_Token(PO_TOKEN);
                        EXPRESSION();
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