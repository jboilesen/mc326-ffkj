/*lib.h*/

// Definicioes de bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definicioes de constantes
#define SEPARATORS ",;!.?():"
#define BLANK " "

#define TRUE 1
#define FALSE 0

#define CHANGECHR '-'
#define CHANGECHR2 '_'

/* Estrutura da lista de palavras
 * char *info : string com conteudo da palavra
 * int count : quantidade de vezes que a palavra eh repetida
 * struct tWord *next : apontador para proximo elemento da lista 
 * responsavel: Felipe/Fernando
 */
typedef struct tWord{

	char *info;
	int count;
	struct tWord *next;

} Word;


/* Verifica se o caracter eh alfanumerico
 * paramentro 1: caracter a ser verificado
 * retorna TRUE caso afirmativo; retorna FALSE caso negativo
 * responsavel Fernando
 */
int isAlphaNumeric( char );

/* Converte os caracteres do segundo argumento de uma string para espacos em branco
 * parametro 1: string a ter os separadores convertidos para espacos em branco
 * parametro 2: lista de separadores, no caso de ser vazio a funcao roda com "not-alfanumeric"
 * responsavel Fernando
 * */
void toBlank( char*, char* );

/* Converte os caracteres de uma string para maiusculos
 * parametro 1: string a ser masculinizada =)
 * retorna quantidade de caracteres convertidos
 * responsavel Fernando
 */
int toUpper( char* );

/* Separa uma string em uma lista de Words a partir dos espacos em branco
 * parametro 1: string a ser separada
 * parametro 2: lista de Words
 * retorna quantidade total de elementos finais da lista de Words
 * responsavel Felipe
 */
int blankSplit( char*, Word** );


/* A partir da lista de Words, conta o total de palavras diferentes que ela possui, "agrupando" as repetidas em elementos Word da lista
 * paramentro 1: lista de Words
 * retorna o total de palavras diferentes
 * responsavel Fernando
 */
int wordCount( Word** );

/* Imprime o arquivo de palavras da lista de Word
 * parametro 1: Lista de Word
 * parametro 2: nome do arquivo a ser gerado
 * retorna TRUE caso o arquivo seja gerado com sucesso ou FALSE caso nao seja gerado o arquivo.
 * responsavel Jonathan
 */
int printFile( Word*, char* );

/* Imprime a lista de Word na saida padrao
 * parametro 1: Lista de Word
 * responsavel Felipe
 */
void printWord( Word* );

/* Conta a quantidade de vezes que um caracter se repete  numa lista de Word
 * parametro 1: Lista de Word
 * parametro 2: caracter a ser contado
 * retorna a quantidade de vezes que o caracter se repete
 * responsavel: Jonathan
 */
int cCountWord ( Word *, char );

/* Conta a quantidade de vezes que uma palavra se repete numa lista de Word
 * parametro 1: Lista de Word
 * parametro 2: palavra a ser contada
 * retorna a quantidade de vezes que a palavra se repete
 * responsavel: Jonathan
 */
int sCountWord ( Word *, char *);

/* Conta a quantidade de vezes que um caracter se repete numa string
 * parametro 1: string
 * parametro 2: palavra a ser contada
 * retorna a quantidade de vezes que o caracter se repete
 * responsavel: Felipe
 */
int cCount ( char *, char );

/* Conta a quantidade de vezes que uma palavra se repete numa lista de Word
 * parametro 1: Lista de Word
 * parametro 2: palavra a ser contada
 * retorna a quantidade de vezes que a palavra se repete
 * responsavel: Felipe
 */
int sCount ( char *, char * );
