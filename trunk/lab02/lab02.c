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

/*Funcao que le um campo de registro(tamanho fixo) a partir de um arquivo
-Parametro 1: string a ser preenchida
-Parametro 2: tamanho da string a ser lida
-Parametro 3: Contador de numero de caracteres
-Parametro 4: Arquivo a ser lido
Contendo uma string com a informacao da linguagem utilizada palo programa
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

/*Funcao que le um arquivo de registro de tamanho fixo e grava em outro arquivo usando separador
-Parametro 1: arquivo a ser lido
-Parametro 2: arquivo a ser gravado
-Parametro 3: Contador de numero de registros
-Parametro 4: Contador de numero de registros da entrada
-Parametro 5: Contador de numero de caracteres da saida
Contendo uma string com a informacao da linguagem utilizada palo programa
Feita por: Richard Keller
16:56 p.m. 29/03/2009*/
void GERA_ARQ_COM_SEPARADOR(FILE* file, FILE* novo, int* Nregistro, int* NcaracteresEntrada1, int* Ncaracteres1)
{
        char ra[RA_size], nome[NOME_size], cidade[CIDADE_size];
        char telres[TELRES_size], telalt[TELALT_size],sexo,curso[CURSO_size], aux;
        int i, size =0;
        while(1){//Captura todos os dados dos campos do arquivo 'file' e grava no arquivo 'novo'
        
              //Parte 1 - Leitura
              
              strcpy(ra,leituraCampoFixo(ra,RA_size,NcaracteresEntrada1, file));
              //printf("string ra:%s\n",ra);
              
              aux = fgetc(file);
              *NcaracteresEntrada1 +=1;
              
              strcpy(nome,leituraCampoFixo(nome,NOME_size,NcaracteresEntrada1, file));

              //printf("size of nome:%d\n",size);
              //printf("string nome:%s\n",nome);
              
              strcpy(cidade,leituraCampoFixo(cidade,CIDADE_size,NcaracteresEntrada1, file));

              //printf("string cidade:%s\n",cidade);
              
              strcpy(telres,leituraCampoFixo(telres,TELRES_size,NcaracteresEntrada1, file));

              //printf("string telres:%s\n",telres);
              
              aux = fgetc(file);
              
              strcpy(telalt,leituraCampoFixo(telalt,TELALT_size,NcaracteresEntrada1, file));

              //printf("string telalt:%s\n",telalt);
              
              aux = fgetc(file);
              *NcaracteresEntrada1 +=1;
              
              sexo = fgetc(file);
              *NcaracteresEntrada1 +=1;
              //printf("string sexo:%c\n",sexo);
              
              aux = fgetc(file);
              *NcaracteresEntrada1 +=1;
              
              strcpy(curso,leituraCampoFixo(curso,CURSO_size,NcaracteresEntrada1, file));

              //printf("string curso:%s\n",curso);
              
              aux = fgetc(file);
              *NcaracteresEntrada1 +=1;
              //printf("aux:%c\n",aux);
              
              aux = fgetc(file);//Verifica se chegou a um '\n' ou a fim do arquivo
              *NcaracteresEntrada1 +=1;
              
              //Parte 2 - Escrita
              for(i=0;i<RA_size-1;i++){
                  fputc(ra[i],novo);
                  *Ncaracteres1+=1;
              }
              fputc(separador,novo);
              *Ncaracteres1+=1;
              
               for(i=0;i<NOME_size-1;i++){
                  if(nome[i]==blank && nome[i+1]==blank)// Pensar em solução melhor para isso
                      break;
                  fputc(nome[i],novo);
                  *Ncaracteres1+=1;
              }
              fputc(separador,novo);
              *Ncaracteres1+=1;

              for(i=0;i<CIDADE_size-1;i++){
                  if(cidade[i]==blank && cidade[i+1]==blank)// Pensar em solução melhor para isso
                      break;
                  fputc(cidade[i],novo);
                  *Ncaracteres1+=1;
              }
              fputc(separador,novo);
              *Ncaracteres1+=1;
              
              for(i=0;i<TELRES_size-1;i++){
                   if(telres[i]==blank && telres[i+1]==blank)// Pensar em solução melhor para isso
                      break;
                  fputc(telres[i],novo);
                  *Ncaracteres1+=1;
              }
              fputc(separador,novo);
              *Ncaracteres1+=1;
              
              for(i=0;i<TELALT_size-1;i++){
                   if(telalt[i]==blank && telalt[i+1]==blank)// Pensar em solução melhor para isso
                      break;
                  fputc(telalt[i],novo);
                  *Ncaracteres1+=1;
              }
              fputc(separador,novo);
              *Ncaracteres1+=1;
              
              fputc(sexo,novo);
              *Ncaracteres1+=1;
              
              fputc(separador,novo);
              *Ncaracteres1+=1;
              
              for(i=0;i<CURSO_size-1;i++){
                   if(curso[i]==blank && curso[i+1]==blank)// Pensar em solução melhor para isso
                      break;
                  fputc(curso[i],novo);
                  *Ncaracteres1+=1;
              }
              fputc(separador,novo);
              *Ncaracteres1+=1;
              
              fputc(fimregistro,novo);
              *Ncaracteres1+=1;              
              if(aux==EOF){
                    *Nregistro+=1;
                    break;
              }
              else{
                    fputc('\n',novo);
                    *Ncaracteres1+=1;
                    *Nregistro+=1;
                    }
         }
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
              GERA_ARQ_COM_SEPARADOR(file, new, &Nregistro, &NcaracteresEntrada1, &Ncaracteres1);
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
