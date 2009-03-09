/*lib.c*/

#include "lib.h"

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
	int dif=0, cont=0;

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

	printf("Apagando %s\n\n", (*t)->info);

	while( begin->next != *t ) begin = begin->next;

	*t = (*t)->next;
	free(begin->next->info);
	free(begin->next);
	begin->next = *t;

	return 0;
}

int printWord( Word *list ){

	while( list ){
		printf("info: %s\n count: %d\n\n", list->info, list->count);
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
		fprintf(p,"%s : %d\n",aux->info,aux->count);
		aux = aux->next;
	}
	fclose(p);
	return TRUE;
}

int cCount ( Word *iniWord, char C){
	char *auxStr,*auxPointer,control;
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
		free(auxStr);/*pelo q eu me lembro do free, acho q ta certo*/
	}
	return counter;
}

int sCount( Word *iniWord, char *Pal ){
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
