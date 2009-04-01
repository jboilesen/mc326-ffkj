#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LANGFILEPATHSIZE 100

#define MSG 0
#define ERR 1

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
char *getConfig(char *);

/*Funcao que busca as mensagens de erro e comuns do programa nos arquivos contidos na pasta lang
Recebe
-char *lang
Contendo uma string com a informacao da linguagem utilizada palo programa
Feita por: Jonathan Nunes Boilesen
18:30 p.m. 22/03/2009*/
char ***loadMessages(char *);

/*Funcao que anda ate o final de uma string em um arquivo e retorna o numero de caracteres que ela tem
Recebe o valor do arquivo file e do separador desejado
ex: p = fopen(...);
    fileStringSize( *p, ...);
Feita por: Fernando Thiers
19:30 p.m. 22/03/2009    */
int fileStringSize( FILE *, char );

/*Funcao que recebe o vetor com as msgs, o tipo (ERR,MSG) e o indice da msg desejada
Feita por: Jonathan Nunes Boilesen
20:32 p.m. 22/03/2009*/
void printMsg(char*** , int, int);
