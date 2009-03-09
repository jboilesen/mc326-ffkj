/*lib.h*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SEPARATORS ",;!.?():"
#define FILENAME "palavras.txt"
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

int cCount ( Word *, char );

int sCount( Word*, char* );

