#include "lib.h"

/*Funcao que verifica o tamanho real da string, nao conta os  espacos a direita da ultima letra.
  -Parametro 1: string a ser verificada
  Feita por: Richard Keller
18:30 p.m. 29/03/2009*/
int verificaTamanho(char * word){
    int i;
    for(i = strlen(word); i>0 && word[i-1] == BLANK ; i--);
    return i;
}

Aluno *createAluno(char *reg){
    
    Aluno *ret = (Aluno*) malloc(sizeof(Aluno));
    
    ret->ra = (char*) malloc((RA_SIZE+1)*sizeof(char));
    memcpy(ret->ra, reg, RA_SIZE);
    reg += RA_SIZE+1;

    
    ret->nome = (char*) malloc((NOME_SIZE+1)*sizeof(char));
    memcpy(ret->nome, reg, NOME_SIZE);
    ret->nome[verificaTamanho(ret->nome)] = '\0';
    reg += NOME_SIZE;
    
    ret->cidade = (char*) malloc((CIDADE_SIZE+1)*sizeof(char));
    memcpy(ret->cidade, reg, CIDADE_SIZE);
    ret->cidade[verificaTamanho(ret->cidade)] = '\0';
    reg += CIDADE_SIZE;

    ret->telres = (char*) malloc((TELRES_SIZE+1)*sizeof(char));
    memcpy(ret->telres, reg, TELRES_SIZE);
    ret->telres[ verificaTamanho( ret->telres ) ] = '\0';
    reg += TELRES_SIZE+1;

    ret->telalt = (char*) malloc((TELALT_SIZE+1)*sizeof(char));
    memcpy(ret->telalt, reg, TELALT_SIZE);
    ret->telalt[ verificaTamanho( ret->telalt ) ] = '\0';
    reg += TELALT_SIZE+1;

    ret->sexo = (char*) malloc(SEXO_SIZE*sizeof(char));
    ret->sexo[0] = reg[0];
    reg += SEXO_SIZE+1;

    ret->curso = (char*) malloc((CURSO_SIZE+1)*sizeof(char));
    memcpy(ret->curso, reg, CURSO_SIZE);
    reg += CURSO_SIZE;
    
    return ret;
}

void freeAluno(Aluno *aluno){
    free(aluno->ra);
    free(aluno->nome);
    free(aluno->cidade);
    free(aluno->telres);
    free(aluno->telalt);
    free(aluno->sexo);
    free(aluno->curso);
    free(aluno);
}

int gera_arq_compacto (char *fileInPath, char *fileOutPath){

    Aluno *aluno;
    char reg[70];

    int n = getNumberOfRecords(fileInPath, REG_SIZE);

    int i;

    FILE *file = fopen(fileInPath, "r");
    FILE *novo = fopen(fileOutPath, "w");    

    for(i=1; i <= n; i++){
        //Parte 1 - Leitura
        fgets(reg, REG_SIZE+2, file);
        aluno = createAluno(reg);
        
        //Parte 2 - Escrita
        fprintf(novo, "%c%c%s", RA_SIZE+2, 1, aluno->ra);
        fprintf(novo, "%c%c%s", NOME_SIZE+2, 2, aluno->nome);
        fprintf(novo, "%c%c%s", CIDADE_SIZE+2, 3, aluno->cidade);
        fprintf(novo, "%c%c%s", TELRES_SIZE+2, 4, aluno->telres);
        fprintf(novo, "%c%c%s", TELALT_SIZE+2, 5, aluno->telalt);
        fprintf(novo, "%c%c%c", SEXO_SIZE+2, 6, aluno->sexo[0]);
        fprintf(novo, "%c%c%s", CURSO_SIZE+2, 7, aluno->curso);
        fprintf(novo, "%c\n", FIMREGISTRO);
        
        //Parte 3 - frees
        freeAluno(aluno);
    }
    fclose(novo);
    fclose(file);
    return TRUE;
}

int gera_arq_com_separador(char *fileInPath, char *fileOutPath){

    Aluno *aluno;
    char reg[70];

    int n = getNumberOfRecords(fileInPath, REG_SIZE);

    int i;

    FILE *file = fopen(fileInPath, "r");
    FILE *novo = fopen(fileOutPath, "w");

    for(i=1; i <= n; i++){
        //Parte 1 - Leitura
        fgets(reg, REG_SIZE+2, file);
        aluno = createAluno(reg);
        
        //Parte 2 - Escrita
        fprintf(novo, "%s%c",aluno->ra, SEPARADOR);
        fprintf(novo, "%s%c",aluno->nome, SEPARADOR);
        fprintf(novo, "%s%c",aluno->cidade, SEPARADOR);
        fprintf(novo, "%s%c",aluno->telres, SEPARADOR);
        fprintf(novo, "%s%c",aluno->telalt, SEPARADOR);
        fprintf(novo, "%c%c",aluno->sexo[0], SEPARADOR);
        fprintf(novo, "%s%c",aluno->curso, SEPARADOR);
        fprintf(novo, "%c\n", FIMREGISTRO);
        
        //Parte 3 - frees
        freeAluno(aluno);
    }
    fclose(novo);
    fclose(file);
    
    return TRUE;
}

int getNumberOfRecords(char *filePath, int size){
    FILE *file = fopen(filePath, "r");
    long l=-1;
    if(file != NULL){
        fseek(file, 0, SEEK_END);
        l = ftell(file);
        fclose(file);
        l/=size;
    }
    return l;
}

int countCharsFile(char *filePath){
    char auxChar;
    int count;
    count = 0;
    FILE *p;
    p = fopen(filePath,"r");
    if (!p){
        return -1;
    }
    while ((auxChar = getc(p)) != EOF){
        count++;
    }
    fclose(p);
    return count;
}
