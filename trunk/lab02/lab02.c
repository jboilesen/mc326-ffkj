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


void GERA_ARQ_COM_SEPARADOR(FILE* file, FILE* novo, int* Nregistro, int* Ncaracteres1)
{
        char ra[RA_size], nome[NOME_size], cidade[CIDADE_size];
        char telres[TELRES_size], telalt[TELALT_size],sexo,curso[CURSO_size], aux;
        int i, size =0;
        while(1){//Captura todos os dados dos campos do arquivo 'file' e grava no arquivo 'novo'
        
              //Parte 1 - Leitura
              for(i=0;i<RA_size-1;i++){
                  ra[i] = fgetc(file);
              }
              ra[i]='\0';
              //printf("string ra:%s\n",ra);
              
              aux = fgetc(file);
              
              for(i=0;i<NOME_size-1;i++){
                  nome[i] = fgetc(file);
              }
              nome[i]='\0';
              //printf("size of nome:%d\n",size);
              //printf("string nome:%s\n",nome);
              
              for(i=0;i<CIDADE_size-1;i++){
                  cidade[i] = fgetc(file);
              }
              cidade[i]='\0';
              //printf("string cidade:%s\n",cidade);
              
              for(i=0;i<TELRES_size-1;i++){
                  telres[i] = fgetc(file);
              }
              telres[i] = '\0';
              //printf("string telres:%s\n",telres);
              
              aux = fgetc(file);
              
              for(i=0;i<TELALT_size-1;i++){
                  telalt[i] = fgetc(file);
              }
              telalt[i] = '\0';
              //printf("string telalt:%s\n",telalt);
              
              aux = fgetc(file);
              
              sexo = fgetc(file);
              //printf("string sexo:%c\n",sexo);
              
              aux = fgetc(file);
              
              for(i=0;i<CURSO_size-1;i++){
                  curso[i] = fgetc(file);
              }
              curso[i]='\0';
              //printf("string curso:%s\n",curso);
              
              aux = fgetc(file);
              //printf("aux:%c\n",aux);
              
              aux = fgetc(file);//Verifica se chegou a um '\n' ou a fim do arquivo
              
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
        FILE* file;
        FILE* file1;
        FILE* new;
        file = fopen(argv[1],"r");
        new = fopen(argv[2],"w");
        if(file){
              GERA_ARQ_COM_SEPARADOR(file, new, &Nregistro, &Ncaracteres1);
              fclose(file);
              fclose(new);
              printf("Numero de registros do arquivo 1: %d\n",Nregistro);
              printf("Numero de caracteres do arquivo de saida 1: %d\n",Ncaracteres1);
        }
        else
            return 1;
        
	return 0;
}
