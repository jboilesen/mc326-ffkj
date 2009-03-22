/*lib.h*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SEPARATORS ",;!.?():"
#define BLANK " "

#define TRUE 1
#define FALSE 0

#define CHANGECHR '-'
#define CHANGECHR2 '_'

typedef struct tWord{

	char *info;
	int count;
	struct tWord *next;

} Word;

int isAlphaNumeric( char );

/* O 2º parametro é a lista de separadores, no caso de ser vazio a função roda com "not-alfanumericos" */
int toBlank( char*, char* );

int toUpper( char* );

int blankSplit( char*, Word** );

int wordCount( Word** );

int delWord( Word*, Word** );

int printFile( Word*, char* );

int printWord( Word* );

int cCountWord ( Word *, char );

int sCountWord ( Word *, char *);

int cCount ( char *, char );

int sCount ( char *, char * );

int countCharsFile(char *);

/*A funcao retorna um ponteiro para a palavra separada
Parametros:
-char **str: ponteiro a ser alterado para parar no final de cada palavra separada
-char *SEP: string com os separadores;
Feita por: Jonathan Nunes Boilesen
2:11 a.m. 19/03/2009*/
char *sepString (char **, char *);

/*Funcao que busca as informacoes contidas
no arquivo de configuracao ini.conf
Recebe
-char *inf
Contendo uma string com a informacao desejada de retorno
Feita por: Jonathan Nunes Boilesen
23:00 p.m. 20/03/2009*/
char *getConfig(char *)
