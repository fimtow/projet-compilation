# Projet Compilation

## Ce langage de programmation est destiné à deux cas d'utilisation :

1. Pour apprendre à programmer aux enfants. En effet, les enfants ont aujourd’hui un avantage considérable puisqu’ils grandissent dans ce monde numérique et donc peuvent dès leur jeune âge commencer à apprendre à programmer. En général, les enfants apprennent rapidement et de façon autonome si une méthode d’apprentissage adaptée leur est proposée. C’est dans cette optique que notre langage de programmation s’est alors intéressé aux enfants qui souhaitent commencer leurs premiers pas en programmation. Il est facilement compréhensible par les enfants et sa syntaxe est assez intuitive (proche du langage humain). Il a l’avantage aussi d’éviter les points virgules et les accolades en les remplaçant par des tabulations et des retours à la ligne, ce qui encourage les enfants aux bonnes pratiques du code propre. En plus, il est orienté vers la création d’interfaces graphiques et des jeux 2D. Les enfants vont alors acquérir rapidement un sentiment de réussite et de satisfaction qui va par la suite les motiver et les pousser pour continuer à apprendre.*
2. Pour créer des prototypes d’interfaces graphiques ou de jeux 2D rapidement en quelques lignes de codes.

## Comment ce langage va permettre t’il cela ?

- Il est destiné  pour la création d’interfaces graphiques. Donc pas de bibliothèques à importer, et pas de structures à initialiser avant de commencer à créer.
- Le programme est constitué de plusieurs objets dits "components". Ça peut être un bouton ou un input dans une interface graphique, ou un ballon dans un jeu 2D. C’est assez facile et intuitif de décomposer une interface en “components”.
- Chaque composant a des procédures ou on peut définir comment on va gérer le comportement de ce composant.
- Il existe des procédures spéciales, comme par exemple la procédure “start” qui est appelée par l’interpréteur une fois le programme démarré. Il existe aussi la procédure “update” qui est appelée par l'interpréteur de façon périodique (idéal pour définir des comportements qui doivent être faitsde façon périodique).

## Grammaire : 
- PROGRAM -> COMPONENT C
- C -> COMPONENT C
- C -> ''
- COMPONENT -> ID ISCOMPONENT newline indent PROCEDURE P dedent
- P -> PROCEDURE P
- P -> ''
- ISCOMPONENT -> is ID
- ISCOMPONENT -> ''
- PROCEDURE -> ID ( TYPE ID T ) INSTRUCTIONS
- T -> , TYPE ID T
- T -> ''
- INSTRUCTIONS -> newline indent INSTRUCTION I dedent
- I -> INSTRUCTION I
- I -> ''
- INSTRUCTION -> ID INST newline
- INSTRUCTION -> IF
- INSTRUCTION -> WHILE
- INSTRUCTION -> FOR
- INSTRUCTION -> DECLARATION
- INST -> AFFEC
- INST -> APPEL
- INST -> OBJ
- OBJ -> . ID APPEL
- AFFEC -> = EXPR
- APPEL -> ( K
- K -> )
- K -> ID Z )
- Z -> , ID Z
- Z -> ''
- DECLARATION -> TYPE ID X newline
- X -> AFFEC
- X -> ''
- IF -> if CONDITION do INSTRUCTIONS ELSEIF ELSE
- ELSEIF -> elseif CONDITION do INSTRUCTIONS ELSEIF
- ELSEIF -> ''
- ELSE -> else INSTRUCTIONS
- ELSE -> ''
- WHILE -> while CONDITION do INSTRUCTIONS
- FOR -> for ID from EXPR to EXPR STEP do INSTRUCTIONS
- STEP -> with EXPR
- STEP -> ''
- CONDITION -> EXPR OP EXPR
- OP -> =
- OP -> <>
- OP -> <
- OP -> >
- OP -> <=
- OP -> >=
- EXPR -> TERM M
- M -> MP TERM M
- M -> ''
- MP -> +
- MP -> -
- TERM -> FACT R
- R -> MD FACT R
- R -> ''
- MD -> *
- MD -> /
- FACT -> ID
- FACT -> NUM
- FACT -> ( EXPR )
- TYPE -> num
- TYPE -> str
- TYPE -> bool

