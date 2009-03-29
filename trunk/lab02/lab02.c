#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RA_size 7
#define NOME_size 25
#define CIDADE_size 16
#define TELRES_size 9
#define TELALT_size 9
#define SEXO_size 1
#define CURSO_size 3
#define separador '|'
#define blank ' '
#define fimregistro '#'
#define TRUE 1
#define FALSE 0

typedef struct s_register{
	char ra[RA_size];
	char nome[NOME_size];
	char cidade[CIDADE_size];
	char telres[TELRES_size];
	char telalt[TELALT_size];
	char sexo;
	char curso[CURSO_size];
} t_register;
	
/*
int gera_arq_comp (File * file, t_register *register ){
	
	int count;
	
	while(register != NULL){
		count++;
		// RA
		putc('<', file);
		putc( '8', file );
		putc('>', file);
		putc('<', file);
		putc( '1', file );
		putc('>', file);
		fprintf( file, "%d", ra);
		// Nome
		putc(verificaTamanho(register->nome)+2 , file);
		putc('<', file);
		putc('2', file);
		putc('>', file);
		fprintf( file, "%s", register->nome);
		// Cidade
		putc( verificaTamanho(register->cidade)+2, file);
		putc('<', file);
		putc( '3', file);
		putc('>', file);
		fprintf( file, "%s", register->cidade);
		// Tel Residencial
		putc( verificaTamanho(register->telres)+2, file);
		putc('<', file);
		putc( '4', file);
		putc('>', file);
		fprintf( file, "%s", register->telres);
		// Tel alternativo
		putc( verificaTamanho(register->telalt)+2, file);
		putc('<', file);
		putc( '5', file);
		putc('>', file);
		fprintf( file, "%s", register->telalt);
		// Sexo
		putc('<', file);
		putc( '3' , file);
		putc('>', file);
		putc('<', file);
		putc( '6' , file);
		putc('>', file);
		putc( register->sexo, file);
		// Curso
		putc('<', file);
		putc( '4', file);
		putc('>', file);
		putc('<', file);
		putc( '7', file);
		putc('>', file);
		putc( register->curso, file);
		// Fim do registro
		putc( '#', file );

		register = register->next;
	}
	
	fclose(file);
	
	return count;
}
*/
/*Funcao que verifica o tamanho real da string, nao conta os  espacos a direita da ultima letra.
-Parametro 1: string a ser verificada
Feita por: Richard Keller
18:30 p.m. 29/03/2009*/
int verificaTamanho(char* word){
        int i,j;
        i=strlen(word);
        for(j=i-1;i>0;j--){
              if(word[j]!=blank)
                  return j+2;
        }
}

/*Funcao que le um campo de registro(tamanho fixo) a partir de um arquivo
-Parametro 1: string a ser preenchida
-Parametro 2: tamanho da string a ser lida
-Parametro 3: Contador de numero de caracteres
-Parametro 4: Arquivo a ser lido
Feita por: Richard Keller
16:56 p.m. 29/03/2009*/
char* leituraCampoFixo(char* word,int size,int* NcaracteresEntrada1, FILE* file){
        int i;
        for(i=0;i<size-1;i++){
                  word[i] = fgetc(file);
                  *NcaracteresEntrada1 +=1;
              }
        word[i]='\0';
        
        return word;
}

/*Funcao que grava um campo de registro ,retirando o espaços a direita da string, em um arquivo
-Parametro 1: string a ser gravada
-Parametro 2: tamanho da string a ser gravada
-Parametro 3: Contador de numero de caracteres
-Parametro 4: Arquivo a ser escrito
Feita por: Richard Keller
18:15 p.m. 29/03/2009*/
void gravaCampoComSep(char* word,int* Ncaracteres1, FILE* novo){
        int i;
        int size=verificaTamanho(word);
        for(i=0;i<size-1;i++){
                  fputc(word[i],novo);
                  *Ncaracteres1+=1;
        }
        fputc(separador,novo);
        *Ncaracteres1+=1;
}

/*Funcao que le um arquivo de registro de tamanho fixo e grava em outro arquivo usando separador
-Parametro 1: arquivo a ser lido
-Parametro 2: arquivo a ser gravado
-Parametro 3: Contador de numero de registros
-Parametro 4: Contador de numero de registros da entrada
-Parametro 5: Contador de numero de caracteres da saida

-Retorna False se número de parametros ou posição dos parametros estiver errada
-Senão retorna True
Feita por: Richard Keller
16:56 p.m. 29/03/2009*/
int GERA_ARQ_COM_SEPARADOR(FILE* file, FILE* novo, int* Nregistro, int* NcaracteresEntrada1, int* Ncaracteres1)
{
        char aux;
        t_register estrutura;
        int i, size =0;
        
        while(1){//Captura todos os dados dos campos do arquivo 'file' e grava no arquivo 'novo'
        
              //Parte 1 - Leitura
              strcpy(estrutura.ra,leituraCampoFixo(estrutura.ra,RA_size,NcaracteresEntrada1, file));
              
              aux = fgetc(file);//leitura de espaço em branco
              *NcaracteresEntrada1 +=1;
              
              strcpy(estrutura.nome,leituraCampoFixo(estrutura.nome,NOME_size,NcaracteresEntrada1, file));
              strcpy(estrutura.cidade,leituraCampoFixo(estrutura.cidade,CIDADE_size,NcaracteresEntrada1, file));
              strcpy(estrutura.telres,leituraCampoFixo(estrutura.telres,TELRES_size,NcaracteresEntrada1, file));
              aux = fgetc(file);//leitura de espaço em branco
              *NcaracteresEntrada1 +=1;
              
              strcpy(estrutura.telalt,leituraCampoFixo(estrutura.telalt,TELALT_size,NcaracteresEntrada1, file));
              aux = fgetc(file);//leitura de espaço em branco
              *NcaracteresEntrada1 +=1;
              
              estrutura.sexo = fgetc(file);
              *NcaracteresEntrada1 +=1;
              
              aux = fgetc(file);//leitura de espaço em branco
              *NcaracteresEntrada1 +=1;
              
              strcpy(estrutura.curso,leituraCampoFixo(estrutura.curso,CURSO_size,NcaracteresEntrada1, file));
              
              aux = fgetc(file);
              // aux recebe o '#'
              *NcaracteresEntrada1 +=1;
              aux = fgetc(file);
              // aux recebe '\n' ou EOF ou um caracter diferente se o arquivo de entrada estiver com campos mal posicionados 
              *NcaracteresEntrada1 +=1;
              
              //Parte 2 - Escrita
              gravaCampoComSep(estrutura.ra, Ncaracteres1, novo);
              gravaCampoComSep(estrutura.nome, Ncaracteres1, novo);
              gravaCampoComSep(estrutura.cidade,Ncaracteres1, novo);
              gravaCampoComSep(estrutura.telres,Ncaracteres1,novo);
              gravaCampoComSep(estrutura.telalt,Ncaracteres1,novo);
              
              fputc(estrutura.sexo,novo);
              *Ncaracteres1+=1;
              fputc(separador,novo);
              *Ncaracteres1+=1;
              
              gravaCampoComSep(estrutura.curso,Ncaracteres1,novo);
              fputc(fimregistro,novo);
              *Ncaracteres1+=1;      
                      
                      
              if(aux==EOF){//Verifica se chegou a um '\n' ou a fim do arquivo
                    *Nregistro+=1;
                    break;
              }
              else if(aux=='\n'){
                    fputc('\n',novo);
                    *Ncaracteres1+=1;
                    *Nregistro+=1;
              }
              else{
                    //mensagem de ERRO
                    return FALSE;
              }
        }
        return TRUE;
}

int main(int argc, char *argv[]){
        int Nregistro =0;
        int Ncaracteres1 = 0;
        int NcaracteresEntrada1 =0;
        FILE* file;
        FILE* file1;
        FILE* new;
        FILE* new1;
        file = fopen(argv[1],"r");
        new = fopen(argv[2],"w");
        if(file){
              if(GERA_ARQ_COM_SEPARADOR(file, new, &Nregistro, &NcaracteresEntrada1, &Ncaracteres1) == FALSE){
                    //MENSAGEM DE ERRO
                    return 1;
              }
              fclose(file);
              fclose(new);
              printf("Numero de registros do arquivo 1: %d\n",Nregistro);
              printf("Numero de caracteres do arquivo de entrada 1: %d\n",NcaracteresEntrada1);
              printf("Numero de caracteres do arquivo de saida 1: %d\n",Ncaracteres1);
        }
        else{
            //Mensagem de ERRO
            return 1;
        }
        
	return 0;
}
