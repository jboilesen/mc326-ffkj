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
