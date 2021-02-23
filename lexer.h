typedef enum
{
    ID_TOKEN,
    NUM_TOKEN,
    ERREUR_TOKEN,
    PROGRAM_TOKEN,
    CONST_TOKEN,
    VAR_TOKEN,
    BEGIN_TOKEN,
    END_TOKEN,
    IF_TOKEN,
    THEN_TOKEN,
    WHILE_TOKEN,
    DO_TOKEN,
    READ_TOKEN,
    WRITE_TOKEN,
    PV_TOKEN,
    PT_TOKEN,
    PLUS_TOKEN,
    MOINS_TOKEN,
    MULT_TOKEN,
    DIV_TOKEN,
    VIR_TOKEN,
    AFF_TOKEN,
    INF_TOKEN,
    INFEG_TOKEN,
    SUP_TOKEN,
    SUPEG_TOKEN,
    DIFF_TOKEN,
    PO_TOKEN,
    PF_TOKEN,
    FIN_TOKEN,
    EG_TOKEN,
    NEWLINE_TOKEN,
    INDENT_TOKEN,
    DEDENT_TOKEN,
    FICHIER_VIDE
} codesLex;

typedef struct tSymCour
{
    codesLex code;
    char nom[20];
} tSymCour;

extern char carCour;
extern tSymCour symCour;
extern int rester;
extern int line;
void ouvrirFichier(char* file);
void lireCaractere();
void symSuiv();
void afficherToken();
void lireNombre();
void lireMot();
void lireCar();
