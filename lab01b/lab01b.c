/*lab01.c */

#include <stdio.h>
#include "lib.h"

typedef enum { ERROR , file , text_c_pal } Input;

// Verifica o tipo de entrada
Input inputTest(int argc, char *argv[]){ 

	// Testa o numero de argumentos
	if( argc == 2 ){ // Caso em que é passado apenas 1 arquivo como argumento
		if( file=fopen(argv[1],"r") == NULL ){
			printf("Arquivo não encontrado.\n");
			return ERROR;
		}
		else return file;
	}
	if( argc == 4 ){
		// Testa se o 3 argumento é um caracter
		if( strlen(argv[2]) != 1  ){
			printf("3o argumento deve ser um caracter.\n");
			return ERROR;
		}
		else return text_c_pal;
	}
	return ERROR;
}

int read_file( FILE file, char *sep, char **text, char *c, char **pal ){

	char *string, *cp_string, *caracter;
	int i, stringsize;

	// Le conteúdo do arquivo e armazena em string
	stringsize = fileStringSize( file, '\n' );
	string = (char *) malloc( ( stringsize  + 1 ) * sizeof(char) );
	for( i=0; i<stringsize; i++) string[i] = getc(&file);
	string[i+1] = '\0';
	cp_string = string;

	// Armazena text, c, pal usando a função sepString(
	if( (*text = sepString( &cp_string, sep )) == NULL ) exit(1);
	
	if( (caracter = sepString( &cp_string, sep )) == NULL ) exit(1);
	else{ 
		*c = *caracter;
		free( caracter );
	}

	if( (*pal = sepString( &cp_string, sep )) == NULL ) exit(1);

	free(string);

	return 0;
}

int fileStringSize( FILE file, char sep ){

	int count=0;
	char aux;

	while( ((aux = getc(&file)) != sep ) && ( aux != EOF ) ) count++;

	return count;
}


int main(int argc, char *argv[]){

	Input input; // Recebe o tipo da entrada
	char *text, c, *pal, *filename, *sep, *lang, ***messages;
	Word *word;
	int i;
	FILE *file;

	// Verificação da entrada
	if( (input = inputTest(argc, argv)) == 0 ) exit(1); 

	// Le string de separadores do arquivo de configuração, getConfig aloca,     	 		LEMBRAR DE DAR O FREE
	if( sep = getConfig( "SEP" ) == NULL ) exit(1);

	// Le idioma do arquivo de configuração, getConfig aloca,                   		 	LEMBRAR DE DAR O FREE
	if( lang = getConfig( "LANG" ) == NULL ) exit(1);	
	
	// Carrega mensagens do idioma, loadMessages aloca,						FREE!
	if( messages = loadMessages( lang ) == NULL ) exit(1);

	// Entrada do tipo texto+caracter+palavra
	if( input == text_c_pal ){
		// Armazena o texto
		text = (char*)malloc( strlen(argv[1]) * sizeof(char));               			//FREE!
		strcpy( text, argv[1] );
		// Armazena o caracter
		c = argv[2][0];
		// Armazena a palavra
		pal = (char*) malloc( strlen(argv[3]) * sizeof(char));                 			//FREE!
		strcpy( pal, argv[3] );
	}

	// Entrada do tipo arquivo
	if( input == 1_file ){
		// Abre o arquivo, le entrada, fecha o arquivo
		file = fopen( argv[1], "r" );
		if( read_1_file( file, sep, &text, &c, &pal ) == 0 ) exit(1);
		fclose( file );
	}

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
