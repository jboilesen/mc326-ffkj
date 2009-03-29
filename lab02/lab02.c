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
void gravaCampoComSep(char* word,int size,int* Ncaracteres1, FILE* novo){
        int i;
        for(i=0;i<size-1;i++){
                  if(word[i]==blank && word[i+1]==blank)// Pensar em solução melhor para isso
                      break;
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
Contendo uma string com a informacao da linguagem utilizada palo programa

-Retorna False se número de parametros ou posição dos parametros estiver errada
-Senão retorna True
Feita por: Richard Keller
16:56 p.m. 29/03/2009*/
int GERA_ARQ_COM_SEPARADOR(FILE* file, FILE* novo, int* Nregistro, int* NcaracteresEntrada1, int* Ncaracteres1)
{
        char ra[RA_size], nome[NOME_size], cidade[CIDADE_size];
        char telres[TELRES_size], telalt[TELALT_size],sexo,curso[CURSO_size], aux;
        int i, size =0;
        while(1){//Captura todos os dados dos campos do arquivo 'file' e grava no arquivo 'novo'
        
              //Parte 1 - Leitura
              strcpy(ra,leituraCampoFixo(ra,RA_size,NcaracteresEntrada1, file));
              
              aux = fgetc(file);//leitura de espaço em branco
              *NcaracteresEntrada1 +=1;
              
              strcpy(nome,leituraCampoFixo(nome,NOME_size,NcaracteresEntrada1, file));
              strcpy(cidade,leituraCampoFixo(cidade,CIDADE_size,NcaracteresEntrada1, file));
              strcpy(telres,leituraCampoFixo(telres,TELRES_size,NcaracteresEntrada1, file));
              aux = fgetc(file);//leitura de espaço em branco
              *NcaracteresEntrada1 +=1;
              
              strcpy(telalt,leituraCampoFixo(telalt,TELALT_size,NcaracteresEntrada1, file));
              aux = fgetc(file);//leitura de espaço em branco
              *NcaracteresEntrada1 +=1;
              
              sexo = fgetc(file);
              *NcaracteresEntrada1 +=1;
              
              aux = fgetc(file);//leitura de espaço em branco
              *NcaracteresEntrada1 +=1;
              
              strcpy(curso,leituraCampoFixo(curso,CURSO_size,NcaracteresEntrada1, file));
              
              aux = fgetc(file);
              *NcaracteresEntrada1 +=1;
              
              aux = fgetc(file);
              *NcaracteresEntrada1 +=1;
              
              //Parte 2 - Escrita
              gravaCampoComSep(ra, RA_size, Ncaracteres1, novo);
              gravaCampoComSep(nome, NOME_size, Ncaracteres1, novo);
              gravaCampoComSep(cidade,CIDADE_size,Ncaracteres1, novo);
              gravaCampoComSep(telres,TELRES_size,Ncaracteres1,novo);
              gravaCampoComSep(telalt,TELALT_size,Ncaracteres1,novo);
              
              fputc(sexo,novo);
              printf("i=%d",i);
              *Ncaracteres1+=1;
              fputc(separador,novo);
              *Ncaracteres1+=1;
              
              gravaCampoComSep(curso,CURSO_size,Ncaracteres1,novo);
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
