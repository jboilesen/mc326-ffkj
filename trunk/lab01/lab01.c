/*lab01.c */

#include <stdio.h>
#include "lib.h"


// verifica se a entrada esta no formato correto
int inputTest(int argc, char *argv[]){
    // teste numero de argumentos
    if( argc != 4 ){
        printf("quantidade de argumentos insuficiente\n\n");
        exit(1);    
    }

    // teste 3 argumento - deve ser um caracter
    if( strlen(argv[2]) != 1  ){
        printf("3o argumento deve ser um caracter\n\n");
        exit(1);
    }

    return TRUE;
}

int main(int argc, char *argv[]){

    char *text, c, *pal, *filename;
    Word *word;
    int i;

    inputTest(argc, argv);

    text = (char*)malloc(strlen(argv[1])*sizeof(char));
    strcpy(text, argv[1]);

    c = argv[2][0];

    pal = (char*) malloc(strlen(argv[3])*sizeof(char));
    strcpy(pal, argv[3]);

    printf("\n->Texto\n%s\n\n", text);

    // Imprime a quantidade de vezes que o caracter c e 
    // a string pal se repetem no texto
    printf("->Quantidade de vezes que \"%c\" se repete no texto\n%d\n\n", c, cCount(text, c));
    printf("->Quantidade de vezes que \"%s\" se repete no texto\n%d\n\n", pal, sCount(text, pal));

    toUpper(text);
    printf("->Texto em maiusculo\n%s\n\n", text);

    toBlank(text, NULL);
    printf("->Texto com caracteres especiais transformados em espaco\n%s\n\n", text);
   
    i = blankSplit(text, &word);
    printf("->Numero de palavras do texto\n%d\n\n", i);

    i = wordCount(&word);
    printf("->Numero de palavras diferentes do texto\n%d\n\n",i);
    
    printf("->Impressao da lista de palavras\n");
    printWord(word);
    printf("\n");

    printf("->Gerando arquivo com lista de palavras...");
    //  pal.txt
    filename = (char*) malloc((strlen(pal)+3)*sizeof(char));
    filename = strcat(filename, pal);
    filename = strcat(filename, ".txt");
    printFile(word, filename);
    printf(" arquivo criado \"%s\"\n\n", filename);

    return 0;
}
