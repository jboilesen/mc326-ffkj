#include <stdio.h>
#define RA_size 7
#define NOME_size 25
#define CIDADE_size 16
#define TELRES_size 9
#define TELALT_size 9
#define SEXO_size 1
#define CURSO_size 3
void GERA_ARQ_COM_SEPARADOR(FILE* file, FILE* novo)
{
        char ra[RA_size], nome[NOME_size], cidade[CIDADE_size];
        char telres[TELRES_size], telalt[TELALT_size],sexo,curso[CURSO_size], aux;
        int i, size =0;
              for(i=0;i<RA_size-1;i++){
                  ra[i] = fgetc(file);
              }
              ra[i]='\0';
              printf("string ra:%s\n",ra);
              
              aux = fgetc(file);
              
              for(i=0;i<NOME_size-1;i++){
                  nome[i] = fgetc(file);
              }
              nome[i]='\0';
              printf("string nome:%s\n",nome);
              
              for(i=0;i<CIDADE_size-1;i++){
                  cidade[i] = fgetc(file);
              }
              cidade[i]='\0';
              printf("string cidade:%s\n",cidade);
              
              for(i=0;i<TELRES_size-1;i++){
                  telres[i] = fgetc(file);
              }
              telres[i] = '\0';
              printf("string telres:%s\n",telres);
              
              aux = fgetc(file);
              
              for(i=0;i<TELALT_size-1;i++){
                  telalt[i] = fgetc(file);
              }
              telalt[i] = '\0';
              printf("string telalt:%s\n",telalt);
              
              aux = fgetc(file);
              
              sexo = fgetc(file);
              printf("string sexo:%c\n",sexo);
              
              aux = fgetc(file);
              
              for(i=0;i<CURSO_size-1;i++){
                  curso[i] = fgetc(file);
              }
              curso[i]='\0';
              printf("string curso:%s\n",curso);
              
              aux = fgetc(file);
              printf("aux:%c\n",aux);
              
}

int main(int argc, char *argv[]){

        FILE* file;
        FILE* file1;
        FILE* new;
        file = fopen(argv[1],"r");
        new = fopen(argv[2],"w");
        if(file){
              GERA_ARQ_COM_SEPARADOR(file, new);
        }
        else
            return 1;
        
	return 0;
}
