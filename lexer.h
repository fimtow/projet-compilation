typedef enum
{
    ID_TOKEN,
    NUMBER_TOKEN,
    STRING_TOKEN,
    ERREUR_TOKEN,
    IS_TOKEN,
    FOR_TOKEN,
    IF_TOKEN,
    ELSEIF_TOKEN,
    DO_TOKEN,
    ELSE_TOKEN,
    WHILE_TOKEN,
    FROM_TOKEN,
    TO_TOKEN,
    WITH_TOKEN,
    NUM_TOKEN,
    STR_TOKEN,
    BOOL_TOKEN,
    TRUE_TOKEN,
    FALSE_TOKEN,
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
void indentCalculator();
void readString();