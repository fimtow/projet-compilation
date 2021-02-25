typedef enum
{
    ERR_CAR_INC,
    ERR_FIC_VIDE,
    ERR_IDF_LONG,
    ERR_CON_LONG,
    ID_ERROR,
    NUMBER_ERROR,
    STRING_ERROR,
    ERREUR_ERROR,
    IS_ERROR,
    FOR_ERROR,
    IF_ERROR,
    ELSEIF_ERROR,
    DO_ERROR,
    ELSE_ERROR,
    WHILE_ERROR,
    FROM_ERROR,
    TO_ERROR,
    WITH_ERROR,
    NUM_ERROR,
    STR_ERROR,
    BOOL_ERROR,
    TRUE_ERROR,
    FALSE_ERROR,
    PT_ERROR,
    PLUS_ERROR,
    MOINS_ERROR,
    MULT_ERROR,
    DIV_ERROR,
    VIR_ERROR,
    AFF_ERROR,
    INF_ERROR,
    INFEG_ERROR,
    SUP_ERROR,
    SUPEG_ERROR,
    DIFF_ERROR,
    PO_ERROR,
    PF_ERROR,
    FIN_ERROR,
    EG_ERROR,
    NEWLINE_ERROR,
    INDENT_ERROR,
    DEDENT_ERROR
} codesErr;

void erreur(codesErr err);
