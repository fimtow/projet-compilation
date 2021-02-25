#include "lexer.h"
#include "common.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define MOTSCLEFS 15

int rester = 1;
int line = 1;
int lastIndent = 0;
int currentIndent = 0;
char carCour;
tSymCour symCour;
FILE* fichier;
char* motsClefs[] = {"is","for","if","elseif","do","else","while","from","to","with","num","str","bool","true","false"};


void ouvrirFichier(char* file)
{
    fichier = fopen(file,"r");
    symCour.code = FICHIER_VIDE;
}

void lireCaractere()
{
    carCour = fgetc(fichier);
}

void passeSepa()
{
    int commentaire = 0;
    int commentaireOneline = 0;
    while(commentaire || carCour==' ' || carCour=='/')
    {
        if(carCour=='/')
        {
            lireCaractere();
            if(carCour == '/')
            {
                commentaireOneline = 1;
            }
            else if(carCour != '*')
            {
                fseek(fichier,-1,SEEK_CUR);
                carCour = '/';
                break;
            }
            commentaire = 1;
        }
        if(carCour=='*' && commentaire)
        {
            lireCaractere();
            if(carCour == '/')
                commentaire = 0;
        }
        if(commentaireOneline && carCour=='\n')
        {
            commentaire = 0;
            commentaireOneline =0;
        }
        if(carCour == '\n')
        {
            line++;
        }
        lireCaractere();
    }
}

void symSuiv()
{
    if(currentIndent != 0)
    {
        if(currentIndent < 0)
        {
            if(carCour == '\t')
            {
                symCour.code = INDENT_TOKEN;
                lastIndent++;
                lireCar();
            }
            else
            {
                currentIndent = 0;
                symSuiv();
            }
        }
        else
        {
            symCour.code = DEDENT_TOKEN;
            currentIndent--;
            lastIndent--;
            lireCar();
        }
    }
    else
    {
        passeSepa();
        if(isalpha(carCour))
        {
            lireMot();
        }
        else if(isdigit(carCour))
        {
            lireNombre();
        }
        else
        {
            switch(carCour)
            {
                case '+' : symCour.code = PLUS_TOKEN; lireCar(); break;
                case '.' : symCour.code = PT_TOKEN; lireCar(); break;
                case '-' : symCour.code = MOINS_TOKEN; lireCar(); break;
                case '*' : symCour.code = MULT_TOKEN; lireCar(); break;
                case '/' : symCour.code = DIV_TOKEN; lireCar(); break;
                case ',' : symCour.code = VIR_TOKEN; lireCar(); break;
                case '=' : symCour.code = AFF_TOKEN; lireCar(); break;
                case '<' : symCour.code = INF_TOKEN; lireCar(); break;
                case '>' : symCour.code = SUP_TOKEN; lireCar(); break;
                case '(' : symCour.code = PO_TOKEN; lireCar(); break;
                case ')' : symCour.code = PF_TOKEN; lireCar(); break;
                case '"' : symCour.code = STRING_TOKEN; lireCar(); readString(); break;
                case '\n' : symCour.code = NEWLINE_TOKEN; line++; lireCar(); indentCalculator(); break;
                case EOF : rester = 0; lireCar(); break;
                default : symCour.code = ERREUR_TOKEN; erreur(ERR_CAR_INC);
            }
        }
    }
}

void afficherToken()
{
    switch (symCour.code)
    {
        case ID_TOKEN:printf("ID_TOKEN\n");break;
        case NUMBER_TOKEN:printf("NUMBER_TOKEN\n");break;
        case STRING_TOKEN:printf("STRING_TOKEN\n");break;
        case ERREUR_TOKEN:printf("ERREUR_TOKEN\n");break;
        case IS_TOKEN:printf("IS_TOKEN\n");break;
        case FOR_TOKEN:printf("FOR_TOKEN\n");break;
        case IF_TOKEN:printf("IF_TOKEN\n");break;
        case ELSEIF_TOKEN:printf("ELSEIF_TOKEN\n");break;
        case DO_TOKEN:printf("DO_TOKEN\n");break;
        case ELSE_TOKEN:printf("ELSE_TOKEN\n");break;
        case WHILE_TOKEN:printf("WHILE_TOKEN\n");break;
        case FROM_TOKEN:printf("FROM_TOKEN\n");break;
        case TO_TOKEN:printf("TO_TOKEN\n");break;
        case WITH_TOKEN:printf("WITH_TOKEN\n");break;
        case NUM_TOKEN:printf("NUM_TOKEN\n");break;
        case STR_TOKEN:printf("STR_TOKEN\n");break;
        case BOOL_TOKEN:printf("BOOL_TOKEN\n");break;
        case TRUE_TOKEN:printf("TRUE_TOKEN\n");break;
        case FALSE_TOKEN:printf("FALSE_TOKEN\n");break;
        case PT_TOKEN:printf("PT_TOKEN\n");break;
        case PLUS_TOKEN:printf("PLUS_TOKEN\n");break;
        case MOINS_TOKEN:printf("MOINS_TOKEN\n");break;
        case MULT_TOKEN:printf("MULT_TOKEN\n");break;
        case DIV_TOKEN:printf("DIV_TOKEN\n");break;
        case VIR_TOKEN:printf("VIR_TOKEN\n");break;
        case AFF_TOKEN:printf("AFF_TOKEN\n");break;
        case INF_TOKEN:printf("INF_TOKEN\n");break;
        case INFEG_TOKEN:printf("INFEG_TOKEN\n");break;
        case SUP_TOKEN:printf("SUP_TOKEN\n");break;
        case SUPEG_TOKEN:printf("SUPEG_TOKEN\n");break;
        case DIFF_TOKEN:printf("DIFF_TOKEN\n");break;
        case PO_TOKEN:printf("PO_TOKEN\n");break;
        case PF_TOKEN:printf("PF_TOKEN\n");break;
        case FIN_TOKEN:printf("FIN_TOKEN\n");break;
        case EG_TOKEN:printf("EG_TOKEN\n");break;
        case NEWLINE_TOKEN:printf("NEWLINE_TOKEN\n");break;
        case INDENT_TOKEN:printf("INDENT_TOKEN\n");break;
        case DEDENT_TOKEN:printf("DEDENT_TOKEN\n");break;
    default:
        break;
    }
}

void lireNombre()
{
    int i = 0;
    do
    {
        i++;
        lireCaractere();
    } while (isdigit(carCour));
    if(i>=11)
        erreur(ERR_CON_LONG);
    symCour.code = NUMBER_TOKEN;
}

void lireMot()
{
    int i=0;
    do
    {
        if(i>=20)
            erreur(ERR_IDF_LONG);
        symCour.nom[i] = carCour;
        i++;
        lireCaractere();
    } while (isalpha(carCour) || isdigit(carCour));
    symCour.nom[i] = '\0';
    for(int j=0;j<MOTSCLEFS;j++)
    {
        if(strcasecmp(motsClefs[j], symCour.nom) == 0)
        {
            symCour.code = j+4;
            return;
        }
    }
    symCour.code = ID_TOKEN;
}

void lireCar()
{
    switch (carCour)
    {
        case '=': 
            lireCaractere();
            if(carCour == '=')
                symCour.code = EG_TOKEN;
            break;
        case '<': 
            lireCaractere();
            if(carCour == '=')
                symCour.code = INFEG_TOKEN;
            else if(carCour == '>')
                symCour.code = DIFF_TOKEN;
            break;
        case '>': 
            lireCaractere();
            if(carCour == '=')
                symCour.code = SUPEG_TOKEN;
            break;
        case EOF:
            if(symCour.code == FICHIER_VIDE)
                erreur(ERR_FIC_VIDE);
            else
                symCour.code = FIN_TOKEN;
            break;
        default:
            break;
    }
    lireCaractere();
}

void indentCalculator()
{
    currentIndent = lastIndent;
    while(carCour == '\t' && currentIndent != 0)
    {
        currentIndent--;
        lireCar();
    }
    if(currentIndent == 0)
        currentIndent = -1;
}

void readString()
{
    while(carCour != '"')
    {
        lireCar();
    }
    lireCar();
}