#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REG_SIZE 69
#define RA_SIZE 6
#define NOME_SIZE 24
#define CIDADE_SIZE 15
#define TELRES_SIZE 8
#define TELALT_SIZE 8
#define SEXO_SIZE 1
#define CURSO_SIZE 2

#define SEPARADOR '|'
#define BLANK ' '
#define FIMREGISTRO '#'

#define TRUE 1
#define FALSE 0

/* 
 * Estrutura que represanta a entidade Aluno
 * Feita por: Todos
 * */

typedef struct tAluno{
    char *ra;
    char *nome;
	char *cidade;
	char *telres;
	char *telalt;
	char *sexo;
	char *curso;
} Aluno;


/* Funcoes */

Aluno *createAluno(char *reg);

/* A partir do arquivo de tamanho fixo, gera um outro compacto
 * -Parametro 1: local do arquivo de tamanho fixo
 * -Parametro 2: destino do arquivo compacto
 * Retorna TRUE caso a funcao execute com sucesso e FALSE caso contrario
 * Feita por: Felipe Gasparini
 * Revisada: Fernando/Richard
 * */
int gera_arq_compacto (char *fileInPath, char *fileOutPath);

/* A partir do arquivo de tamanho fixo, gera um outro com separadores
 * -Parametro 1: local do arquivo de tamanho fixo
 * -Parametro 2: destino do arquivo com separadores
 * Retorna TRUE caso a funcao execute com sucesso e FALSE caso contrario
 * Feita por: Felipe Gasparini
 * Revisada: Johnatan
 * */
int gera_arq_com_separador(char *fileInPath, char *fileOutPath);

/* Conta o numero de registros de tamanho fixo de um arquivo
 * Parametro 1: Caminho do arquivo
 * Parametro 2: tamanho do registro
 * Retorna a quantidade de registros do arquivo
 * Feita por: Johnatan
 * */
int getNumberOfRecords(char *filePath, int size);

/* Conta o numero de caracteres de um arquivo
 * Parametro 1: Nome do aquivo
 * Retorna a quantidade de caracteres do arquivo
 * Feita por: Fernando
 * */
int countCharsFile(char *filePath);


