#include "../lib/lib.h"


/* Realiza os testes dos argumentos da chamada do programa
 * Parametros: argc e argv
 * Retorna TRUE caso parametros estejam corretos, FALSE caso contrario
 * Feita por: Richard
 * */
int testArgs(int argc, char *argv[]){
    // argumentos insuficientes
    if(argc != 4)
        return FALSE;
    // verifica se arquivo de entrada existe
    FILE *file = fopen(argv[1],"r");
    if (!file)
        return FALSE;
    fclose(file);

    // verificacoes ok
    return TRUE;
}


/* Funcao main
 * Feita por: Richard/Felipe Gasparini
 * */
int main(int argc, char *argv[]){
    
    if(testArgs(argc, argv)!= TRUE)
        return 1;

    char *fileInPath = malloc(strlen(argv[1])*sizeof(char)); 
    strcpy(fileInPath, argv[1]);

    char *new1 = malloc(strlen(argv[2])*sizeof(char)); 
    strcpy(new1, argv[2]);

    char *new2 = malloc(strlen(argv[3])*sizeof(char)); 
    strcpy(new2, argv[3]);

    if(gera_arq_com_separador(fileInPath, new1) == FALSE){
        return 1;
    }

    if(gera_arq_compacto(fileInPath, new2) == FALSE){
        return 1;
    }

    printf("Numero de registros do arquivo: %d\n", getNumberOfRecords(fileInPath, REG_SIZE));
    printf("Numero de caracteres do arquivo de entrada: %d\n", countCharsFile(fileInPath));
    printf("Numero de caracteres do arquivo de saida com separador: %d\n", countCharsFile(new1));
    printf("Numero de caracteres do arquivo de saida compacto: %d\n\n", countCharsFile(new2));

    free(fileInPath);
    free(new1);
    free(new2);

    return 1;
}
