# Projet Compilation

## Ce langage de programmation est destiné à deux cas d'utilisation :

1. Pour apprendre à programmer aux enfants. En effet, les enfants ont aujourd’hui un avantage considérable puisqu’ils grandissent dans ce monde numérique et donc peuvent dès leur jeune âge commencer à apprendre à programmer. En général, les enfants apprennent rapidement et de façon autonome si une méthode d’apprentissage adaptée leur est proposée. C’est dans cette optique que notre langage de programmation s’est alors intéressé aux enfants qui souhaitent commencer leurs premiers pas en programmation. Il est facilement compréhensible par les enfants et sa syntaxe est assez intuitive (proche du langage humain). Il a l’avantage aussi d’éviter les points virgules et les accolades en les remplaçant par des tabulations et des retours à la ligne, ce qui encourage les enfants aux bonnes pratiques du code propre. En plus, il est orienté vers la création d’interfaces graphiques et des jeux 2D. Les enfants vont alors acquérir rapidement un sentiment de réussite et de satisfaction qui va par la suite les motiver et les pousser pour continuer à apprendre.*
2. Pour créer des prototypes d’interfaces graphiques ou de jeux 2D rapidement en quelques lignes de codes.

## Comment ce langage va permettre t’il cela ?

- Il est destiné  pour la création d’interfaces graphiques. Donc pas de bibliothèques à importer, et pas de structures à initialiser avant de commencer à créer.
- Le programme est constitué de plusieurs objets dits "components". Ça peut être un bouton ou un input dans une interface graphique, ou un ballon dans un jeu 2D. C’est assez facile et intuitif de décomposer une interface en “components”.
- Chaque composant a des procédures ou on peut définir comment on va gérer le comportement de ce composant.
- Il existe des procédures spéciales, comme par exemple la procédure “start” qui est appelée par l’interpréteur une fois le programme démarré. Il existe aussi la procédure “update” qui est appelée par l'interpréteur de façon périodique (idéal pour définir des comportements qui doivent être faitsde façon périodique).

- ## Grammaire : 
- PROGRAM -> COMPONENT COMPONENTS
- COMPONENTS -> COMPONENT COMPONENTS
- COMPONENTS -> ''
- COMPONENT -> ID ISCOMPONENT newline CONTENU
- CONTENU -> indent PROCEDURE PROCEDURES dedent
- CONTENU -> ''
- PROCEDURES -> PROCEDURE PROCEDURES
- PROCEDURES -> ''
- ISCOMPONENT -> is ID 
- ISCOMPONENT -> ''
- PROCEDURE -> ID ( PARAMS ) INSTRUCTIONS
- PARAMS -> TYPE ID SUITEPARAMS
- PARAMS -> ''
- SUITEPARAMS -> , TYPE ID SUITEPARAMS
- SUITEPARAMS -> ''
- INSTRUCTIONS -> newline indent INSTRUCTION SUITEINSTRUCTIONS dedent
- SUITEINSTRUCTIONS -> INSTRUCTION SUITEINSTRUCTIONS
- SUITEINSTRUCTIONS -> ''
- INSTRUCTION -> ID INST newline
- INSTRUCTION -> IF
- INSTRUCTION -> WHILE
- INSTRUCTION -> FOR
- INSTRUCTION -> DECLARATION
- INST -> AFFEC
- INST -> APPEL
- INST -> OBJ
- OBJ -> . ID APPEL
- AFFEC -> = CONTAFFEC
- CONTAFFEC -> EXPRESSION
- CONTAFFEC -> string
- APPEL -> ( VALEURS
- VALEURS -> )
- VALEURS -> CONTAFFEC SUITEVALEURS )
- SUITEVALEURS -> , CONTAFFEC SUITEVALEURS
- SUITEVALEURS -> ''
- DECLARATION -> TYPE ID AVECAFFEC newline
- AVECAFFEC -> AFFEC
- AVECAFFEC -> ''
- IF -> if EXPRESSION do INSTRUCTIONS ELSEIF ELSE
- ELSEIF -> elseif EXPRESSION do INSTRUCTIONS ELSEIF
- ELSEIF -> ''
- ELSE -> else INSTRUCTIONS
- ELSE -> ''
- WHILE -> while EXPRESSION do INSTRUCTIONS
- FOR -> for ID from EXPRESSION to EXPRESSION PAS do INSTRUCTIONS
- PAS -> with EXPRESSION
- PAS -> ''
- EXPRESSION -> CONJONCTION DISJONCTION
- DISJONCTION -> or CONJONCTION DISJONCTION
- DISJONCTION -> ''
- CONJONCTION -> NEGATION SUITECONJONCTION
- SUITECONJONCTION -> and NEGATION SUITECONJONCTION
- SUITECONJONCTION -> ''
- NEGATION -> not NEGATION
- NEGATION -> COMPARAISON
- COMPARAISON -> EXPR COMP
- COMP -> OP EXPR
- COMP -> ''
- OP -> ==
- OP -> <>
- OP -> <
- OP -> >
- OP -> <=
- OP -> >=
- EXPR -> TERM SUITEEXPR
- SUITEEXPR -> MP TERM SUITEEXPR
- SUITEEXPR -> ''
- MP -> +
- MP -> -
- TERM -> FACT SUITETERM
- SUITETERM -> MD FACT SUITETERM
- SUITETERM -> ''
- MD -> *
- MD -> /
- FACT -> ID
- FACT -> number
- FACT -> true
- FACT -> false
- FACT -> ( EXPRESSION )
- TYPE -> num
- TYPE -> str
- TYPE -> bool