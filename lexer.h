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
    FICHIER_VIDE
} codesLex;
typedef enum
{
    ERR_CAR_INC,
    ERR_FIC_VIDE,
    ERR_IDF_LONG,
    ERR_CON_LONG,
    ID_ERROR,
    EG_ERROR,
    NUM_ERROR,
    PV_ERROR,
    CONST_VAR_BEGIN_ERROR,
    PROGRAM_ERROR,
    PT_ERROR,
    VAR_BEGIN_ERROR,
    BEGIN_ERROR,
    END_ERROR,
    AFF_ERROR,
    IF_ERROR,
    THEN_ERROR,
    WHILE_ERROR,
    DO_ERROR,
    WRITE_ERROR,
    PO_ERROR,
    PF_ERROR,
    READ_ERROR,
    COND_ERROR,
    FACT_ERROR,
    INST_ERROR,
    DOU_DEC,
    NON_VAR,
    IDF_PRO,
    NON_DEC,
    ARG_ERR
} codesErr;
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
void erreur(codesErr err);