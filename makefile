lexer: lexer.h lexer.c lexertest.c common.c common.h
	gcc lexer.c lexertest.c common.c -o lexer
parser: lexer.h lexer.c common.c common.h parser.h parser.c parsertest.c
	gcc lexer.c parser.c common.c parsertest.c -o parser