#include "lexer.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define MOTSCLEFS 11

int rester = 1;
int line = 1;
char carCour;
tSymCour symCour;
FILE* fichier;
char* motsClefs[] = {"program","const","var","begin","end","if","then","while","Do","read","write"};


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
    while(commentaire || carCour==' ' || carCour=='\n' || carCour=='\t' || carCour=='{')
    {
        if(carCour=='{')
        {
            lireCaractere();
            if(carCour != '*')
            {
                fseek(fichier,-1,SEEK_CUR);
                carCour = '{';
                break;
            }
            commentaire = 1;
        }
        if(carCour=='*' && commentaire)
        {
            lireCaractere();
            if(carCour == '}')
                commentaire = 0;
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
            case ';' : symCour.code = PV_TOKEN; lireCar(); break;
            case '.' : symCour.code = PT_TOKEN; lireCar(); break;
            case '-' : symCour.code = MOINS_TOKEN; lireCar(); break;
            case '*' : symCour.code = MULT_TOKEN; lireCar(); break;
            case '/' : symCour.code = DIV_TOKEN; lireCar(); break;
            case ',' : symCour.code = VIR_TOKEN; lireCar(); break;
            case ':' : symCour.code = AFF_TOKEN; lireCar(); break;
            case '<' : symCour.code = INF_TOKEN; lireCar(); break;
            case '>' : symCour.code = SUP_TOKEN; lireCar(); break;
            case '(' : symCour.code = PO_TOKEN; lireCar(); break;
            case ')' : symCour.code = PF_TOKEN; lireCar(); break;
            case '=' : symCour.code = EG_TOKEN; lireCar(); break;
            case EOF : rester = 0; lireCar(); break;
            default : symCour.code = ERREUR_TOKEN; erreur(ERR_CAR_INC);
        }
    }
    
}

void afficherToken()
{
    switch (symCour.code)
    {
        case ID_TOKEN:printf("ID_TOKEN\n");break;
        case NUM_TOKEN:printf("NUM_TOKEN\n");break;
        case ERREUR_TOKEN:printf("ERREUR_TOKEN\n");break;
        case PROGRAM_TOKEN:printf("PROGRAM_TOKEN\n");break;
        case CONST_TOKEN:printf("CONST_TOKEN\n");break;
        case VAR_TOKEN:printf("VAR_TOKEN\n");break;
        case BEGIN_TOKEN:printf("BEGIN_TOKEN\n");break;
        case END_TOKEN:printf("END_TOKEN\n");break;
        case IF_TOKEN:printf("IF_TOKEN\n");break;
        case THEN_TOKEN:printf("THEN_TOKEN\n");break;
        case WHILE_TOKEN:printf("WHILE_TOKEN\n");break;
        case DO_TOKEN:printf("DO_TOKEN\n");break;
        case READ_TOKEN:printf("READ_TOKEN\n");break;
        case WRITE_TOKEN:printf("WRITE_TOKEN\n");break;
        case PV_TOKEN:printf("PV_TOKEN\n");break;
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
    symCour.code = NUM_TOKEN;
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
            symCour.code = j+3;
            return;
        }
    }
    symCour.code = ID_TOKEN;
}

void lireCar()
{
    switch (carCour)
    {
        case ':': 
            lireCaractere();
            if(carCour != '=')
                symCour.code = ERREUR_TOKEN;
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

