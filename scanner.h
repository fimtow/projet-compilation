// type booléen
typedef enum{FALSE, TRUE} boolean;
// Les mots clés de notre langage
const char* keyword_token[] = {"if", "else", "for", "while", "number", "text","is","bouton","with"};
// Les symboles de notre langage
// "+", "-", "/", "*", ",", ";", "{", "}", "(", ")", "=", ">", ".", ">=", "<="
const char symbole_token[] = {'*', ',', ';', '{', '}', '(', ')'};
// Le monde des tokens
typedef enum{
    // keywrods tokens
    IF_TOKEN, ELSE_TOKEN, FOR_TOKEN, WHILE_TOKEN, NUMBER_TOKEN, STR_TOKEN, IS_TOKEN, BOUTTON_TOKEN, WITH_TOKEN,
    // Symbole tokens
    PLUS_TOKEN, MINUS_TOKEN, DIV_TOKEN, STAR_TOKEN, COMMA_TOKEN, SEMICOLON_TOKEN,
    OPEN_BRACE_TOKEN, CLOSE_BRACE_TOKEN, OPEN_PARENS_TOKEN, CLOSE_PARENS_TOKEN,
    ASSIGNMENT_TOKEN, GT_TOKEN, LT_TOKEN, OP_EQ_TOKEN, OP_GE_TOKEN, OP_LE_TOKEN,
    // Other tokens
	IDF_TOKEN,
	VARCHAR_TOKEN,
	NUM_TOKEN,
	EOF_TOKEN,
	INDENT_TOKEN,
	DEINDENT_TOKEN,
	NEWLINE_TOKEN,
	FUNCTION_TOKEN,METHODE_TOKEN,
	ERROR_TOKEN
} nameToken;

// supprimez cette table après la vérification des tokens
const char* tokens[] = {"IF_TOKEN", "ELSE_TOKEN", "FOR_TOKEN", "WHILE_TOKEN", "NUMBER_TOKEN", "STR_TOKEN","IS_TOKEN","BOUTTON_TOKEN","WITH_TOKEN",
                        "PLUS_TOKEN", "MINUS_TOKEN", "DIV_TOKEN", "STAR_TOKEN", "COMMA_TOKEN", "SEMICOLON_TOKEN", "OPEN_BRACE_TOKEN",
                        "CLOSE_BRACE_TOKEN", "OPEN_PARENS_TOKEN", "CLOSE_PARENS_TOKEN", "ASSIGNMENT_TOKEN", "GT_TOKEN", "LT_TOKEN",
                        "OP_EQ_TOKEN", "OP_GE_TOKEN", "OP_LE_TOKEN",
                        "IDF_TOKEN",
                        "VARCHAR_TOKEN",
                        "NUMBER_TOKEN",
                        "EOF_TOKEN",	"INDENT_TOKEN",
	"DEINDENT_TOKEN",
	"NEWLINE_TOKEN",
	"FUNCTION_TOKEN",
                       "METHODE_TOKEN", "ERROR_TOKEN"};
// structure d'un identificateur
typedef struct{
    char* name;
}idfToken;

// structure d'un variable texte
typedef struct{
    char c; //  " ou '
    char* value;
}varcharToken;

// structure d'un nombre
typedef struct{
    boolean isInt; // entier ou flottant
    union{
       int n;
       float x;
    }value;
}numberToken;

// La structure d'un token
typedef struct{
	nameToken name; // Le nom du token
	union{
       idfToken idf; // les informations de l'identificateur (si le token est IDF_TOKEN)
       numberToken number; // les informations du nombre (si le token est NUMBER_TOKEN)
       varcharToken varchar; // les informations du texte (si le token est VARCHAR_TOKEN)
    }properties;
} token;
