/*lib.c*/

#include "lib.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int isAlphaNumeric( char c ){

	if( (c>='A' && c<='Z') || (c>='0' && c<='9') ) return 1;
	return 0;

}

int toBlank( char *string, char *separators ){

	char *str, *sep;

	str = string;
	sep = separators;

	/*Se houver separadores*/
	if( separators != NULL ){

		while(1){
			str += strcspn( str, sep );
			if( *str != '\0' ) *str = ' ';
			else return 1;
		}
	}

	/*Se não houver separadores*/
	else{

		while( *str != '\0' ){
			if( !isAlphaNumeric(*str) ) *str = ' ';
			str++;
		}
		return 1;
	}

	return 0;
}

int toUpper( char *string ) {

	int cont;

	while( *string != '\0' ){
		if( *string >= 'a' && *string <= 'z' ){
			*string -= 32;
			cont++;
		}
		string++;
	}
	return cont;
}

int blankSplit(char *str, Word **lst){
	char *s;
	int n=0;

	Word *aux;

	aux = *lst;

	s = strtok (str, BLANK);
	aux = malloc(sizeof(Word));
	*lst = aux;
	while( s!=NULL ){
		n++;

		aux->info = malloc(strlen(s)*sizeof(char));
		strcpy(aux->info, s);
		aux->count = 0;

		s = strtok ( NULL, BLANK);

		if( s!=NULL ){
			aux->next = malloc(sizeof(Word));
			aux = aux->next;
		}
		else aux = NULL;
	}

	return n;
}

int wordCount( Word **list ) {

	Word *l1, *l2;
	int dif=0;

	l1 = *list;

	if( l1 == NULL ) return 0;

	while( l1 != NULL ){

		l2 = l1->next;

		while(l2 != NULL){

			if( !(strcmp(l1->info,l2->info)) ){
				l1->count++;
				delWord(l1, &l2);
			}
			else l2 = l2->next;

		}

		l1->count++;
		l1 = l1->next;
		dif++;

	}

	return dif;
}

int delWord( Word *begin, Word **t){

	//DEBUG printf("Apagando %s\n\n", (*t)->info);

	while( begin->next != *t ) begin = begin->next;

	*t = (*t)->next;
	free(begin->next->info);
	free(begin->next);
	begin->next = *t;

	return 0;
}

int printWord( Word *list ){

	while( list ){
		printf("%s : %d\n", list->info, list->count);
		list = list->next;
	}
	return 0;
}

int printFile( Word *iniWord, char *filePath ){
	FILE *p;
	Word *aux;

	p = fopen(filePath,"w");
	if (!p){
		printf("Erro ao criar arquivo de saída!\n");
		return FALSE;
	}

	aux = iniWord;

	while (aux!=NULL){
		fprintf(p,"%s:%d\n",aux->info,aux->count);
		aux = aux->next;
	}
	fclose(p);
	return TRUE;
}

int cCountWord ( Word *iniWord, char C){
	char *auxStr,*auxPointer;
	Word *auxWord;
	int counter,tamStr;

	counter = 0;
	auxWord = iniWord;

	while (auxWord!=NULL){
		auxStr = strdup(auxWord->info);
		tamStr = strlen(auxStr);
		do{
			auxPointer = memchr(auxStr,C,tamStr);
			if (auxPointer!=NULL){
				counter++;
				if (C==CHANGECHR){
					*auxPointer = CHANGECHR2;
				}else{
					*auxPointer = CHANGECHR;
				}
			}
		}while(auxPointer!=NULL);
		auxWord = auxWord->next;
		free(auxStr);
	}
	return counter;
}

int sCountWord( Word *iniWord, char *Pal ){
	Word *auxWord;
	int counter,tamPal,tamInfo;

	auxWord = iniWord;
	counter = 0;
	tamPal = strlen(Pal);

	while (auxWord != NULL){
		tamInfo = strlen(auxWord->info);
		if (tamInfo==tamPal){
			if (memcmp(auxWord->info,Pal,tamInfo)==0){
				counter++;
			}
		}
		auxWord = auxWord->next;
	}
	return counter;
}

int cCount(char *text, char c){
    int n=0;

    char *sub;
    sub  = memchr(text,c, strlen(text));
    while(sub!=NULL){
        sub++;
        n++;
        sub = (char*) memchr(sub, c, strlen(sub));
    }
    
    return n;
}

int sCount(char *text, char *pal){

    int n=0;
    char *sub;

    sub  = memchr(text, pal[0], strlen(text));
    while(sub!=NULL){
        if(memcmp(sub, pal, strlen(pal))==0)
            n++;
        sub++;
        sub = (char*) memchr(sub, pal[0], strlen(sub));
    }
    
    return n;
}

/*A funcao retorna um ponteiro para a palavra separada
Parametros:
-char **str: ponteiro a ser alterado para parar no final de cada palavra separada
-char *SEP: string com os separadores;
Feita por: Jonathan Nunes Boilesen
2:11 a.m. 19/03/2009*/
char *sepString (char **str, char *SEP){
	int sizeSEP,iniPos,endPos,flagIni,flagEnd,sizeReturn;
	char *returnStr;
	sizeSEP = strlen(SEP);
	iniPos = 0;
	endPos = 0;
	flagIni = 0;
	flagEnd = 0;
	returnStr = NULL;
	/*verifica o caso dos parametro serem invalidos*/
	if ((str!=NULL)&&(SEP!=NULL)){
		/*verifica se foi inicializada a str*/
		while (*str!=NULL){ 
			/*busca o caracter na string de separadores*/
			if (memchr(SEP,**str,sizeSEP)==NULL){
				/*no caso de nao encontrar, marca o inicio da palavra com o flagIni = 1*/
				if (flagIni == 0){
					/*inicializa o endPos onde comeca a palavra*/
					endPos = iniPos;
					flagIni = 1;
				}
			}else{
				/*no caso de encotrar um separador marcando o fim da palavra*/
				if (flagIni == 1){
					/*por boas praticas, sinaliza o fim na flagEnd e ja passa o ponteiro para o proximo caracter, afinal este eh separador*/
					flagEnd = 1;
					*str++;
					break;
				}
			}
			/*verifica qual posicao esta marcando, do inicio ou do fim*/
			if (flagIni == 0){
				iniPos++;
			}else{
				endPos++;
			}
			*str++;
		}
		/*calcula o tamanho nescessario para guardar a palavra + o sentinela \0*/
		sizeReturn = (endPos - iniPos)+1;
		/*aloca e depois ja insere o sentinela*/
		returnStr = (char*)malloc(sizeof(char)*sizeReturn);
		returnStr[sizeReturn-1] = '\0';		
	}

	return returnStr;
}
