/*lab01.c */

#include <stdio.h>
#include "lib.h"

typedef enum { ERROR , t_file , text_c_pal } Input;

// Verifica o tipo de entrada
Input inputTest(int argc, char *argv[]){ 

	FILE *file;

	// Testa o numero de argumentos
	if( argc == 2 ){ // Caso em que é passado apenas 1 arquivo como argumento
		if( (file = fopen(argv[1],"r")) == NULL ) return ERROR;
		else return t_file;
	}
	if( argc == 4 ){
		// Testa se o 3 argumento é um caracter
		if( strlen(argv[2]) != 1  ) return ERROR;
		else return text_c_pal;
	}
	return ERROR;
}

int read_file( FILE *file, char *sep, char **text, char *c, char **pal ){

	char *string, *cp_string, *caracter;
	int i, stringsize;

	// Le conteudo do arquivo e armazena em string
	stringsize = fileStringSize( *file, '\n' );
	string = (char *) malloc( ( stringsize  + 1 ) * sizeof(char) );
	for( i=0; i<stringsize; i++) string[i] = getc(file);
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

	aux = getc(&file)
	while( ( aux != sep ) && ( aux != '\n' ) && ( aux != EOF )  ) count++;

	return count;
}


int main(int argc, char *argv[]){

	Input input; // Recebe o tipo da entrada
	char *text, c, *pal, *filename, *sep, *lang, ***messages;
	Word *word;
	FILE *file;
printf("antes do getconfig");
	// Le idioma do arquivo de configuração, getConfig aloca,                   		 	LEMBRAR DE DAR O FREE
	lang = getConfig( "LANG" );
printf("passo do getconfig");
	if( lang == NULL ){
		printf("ERROR! The program could not read the language from the configuration file.\n\n");
		exit(1);
	}
printf("leu idioma\n");
	
	// Carrega mensagens do idioma, loadMessages aloca,						FREE!
	messages = loadMessages( lang );
	if( messages == NULL ){
		printf("ERROR! The program could not read the language file.\n\n");
		exit(1);
	}
	printMsg( messages, MSG, 1 );
printf("carrega mensagens\n");

	// Verificação da entrada
	input = inputTest(argc, argv);
	if( input == 0 ){
		printMsg( messages, ERR, 1 ); // "Arquivo não encontrado ou entrada em formato incompativel"
		exit(1);
	}
printf("verificou entrada\n");

	// Le string de separadores do arquivo de configuração, getConfig aloca,     	 		LEMBRAR DE DAR O FREE
	sep = getConfig( "SEP" );
	if( sep == NULL ){
		printMsg( messages, ERR, 2 ); // "ERRO! Arquivo de configuracao mal formatado.
		exit(1);
	}
printf("leu SEP\n");

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
	if( input == t_file ){
		// Abre o arquivo, le entrada, fecha o arquivo
		file = fopen( argv[1], "r" );
		if( read_file( file, sep, &text, &c, &pal ) == 0 ){
			printMsg( messages, ERR, 3 ); // "Arquivo de entrada mal formatado"
			exit(1);
		}
		fclose( file );
	}
	printMsg( messages, MSG, 2 );

	// Imprime texto original
	printMsg( messages, MSG, 3 );
	printf("%s\n\n", text);

	// Imprime a quantidade de vezes que o caracter c e a string pal se repetem no texto
	printMsg( messages, MSG, 4 );
	printf(" %d\n\n", cCount(text, c));
	printMsg( messages, MSG, 5 );
	printf(" %d\n\n", sCount(text, pal));
	
	// Imprime texto em maiusculo
	toUpper(text);
	printMsg( messages, MSG, 6 );
	printf("%s\n\n", text);

	// Imprime texto com caracteres especiais transformados em espaco
	toBlank(text, NULL);
	printMsg( messages, MSG, 7 );
	printf("%s\n\n", text);

	// Imprime numero de palavras do texto
	printMsg( messages, MSG, 8 );
	printf(" %d\n\n",blankSplit( text, &word));

	// Imprime numero de palavras diferentes do texto
	printMsg( messages, MSG, 9 );
	printf(" %d\n\n",wordCount( &word ));

	// Imprime a lista de palavras
	printMsg( messages, MSG, 10 );
	printWord(word);
	printf("\n");

	// Gera arquivo com a lista de palavras pal.txt
	printMsg( messages, MSG, 11 );
	filename = (char*) malloc((strlen(pal)+3)*sizeof(char));
	filename = strcat(filename, pal);
	filename = strcat(filename, ".txt");
	printFile(word, filename);
	printMsg( messages, MSG, 12 );
	printf(" \"%s\"\n\n", filename);

	return 0;
}
