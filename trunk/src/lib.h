/*lib.h*/

#include <stdio.h>
#include <stdlib.h>
#include "strings.h"

#define SEPARATORS ",;!.?():"
#define FILENAME "palavras.txt"

typedef struct tWord{

char *info;
int count;
struct tWord *next;

} Word;

int isAlphaNumeric( char );

/* O 2º parametro é a lista de separadores, no caso de ser vazio a função roda com "not-alfanumericos" */
int toBlank( char*, char* );

int toUpper( char* );

int blankSplit( char*, Word* );

int wordCount( Word** );

int printFile( Word*, char* );
