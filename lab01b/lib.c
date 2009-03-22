/*lib.c*/

#include "lib.h"

int isAlphaNumeric( char c ){

	if( (c>='A' && c<='Z') || (c>='0' && c<='9') ) return TRUE;
	return FALSE;

}

void toBlank( char *string, char *separators ){

	char *str, *sep;

	str = string;
	sep = separators;

	/*Se houver separadores*/
	if( separators != NULL ){
		while(TRUE){
			str += strcspn( str, sep );
			if( *str != '\0' ) *str = ' ';
		}
	}

	/*Se nÃ£o houver separadores*/
	else{
		while( *str != '\0' ){
			if( !isAlphaNumeric(*str) ) *str = ' ';
			str++;
		}
	}
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

	while( begin->next != *t ) begin = begin->next;

	*t = (*t)->next;
	free(begin->next->info);
	free(begin->next);
	begin->next = *t;

	return 0;
}

void printWord( Word *list ){

	while( list ){
		printf("%s : %d\n", list->info, list->count);
		list = list->next;
	}
}

int printFile( Word *iniWord, char *filePath ){
	FILE *p;
	Word *aux;

	p = fopen(filePath,"w");
	if (!p){
		printf("Erro ao criar arquivo de saÃ­da!\n");
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

int countCharsFile(char *filePath){
	char auxChar;
	int count;
	count = 0;
	FILE *p;
	p = fopen(filePath,"r");
	if (!p){
		return -1;
	}
	while ((auxChar = getc(p)) != EOF){
		count++;
	}
	fclose(p);
	return count;
}

char *sepString (char **str, char *SEP){
	int sizeSEP,iniPos,endPos,flagIni,sizeReturn,i,j;
	char *returnStr;
	sizeSEP = strlen(SEP);
	iniPos = 0;
	endPos = 0;
	flagIni = 0;
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
					(*str)++;
					break;
				}
			}
			/*verifica qual posicao esta marcando, do inicio ou do fim*/
			if (flagIni == 0){
				iniPos++;
			}else{
				endPos++;
			}
			(*str)++;
		}
		/*calcula o tamanho nescessario para guardar a palavra + o sentinela \0*/
		sizeReturn = (endPos - iniPos)+1;
		/*aloca e depois ja insere o sentinela*/
		returnStr = (char*)malloc(sizeof(char)*sizeReturn);
		returnStr[sizeReturn-1] = '\0';
		for (i=0,j=iniPos;i<sizeReturn;i++,j++){
			returnStr[i] = *str[j];
		}
	}

	return returnStr;
}

char *getConfig(char *inf){
     char *auxStr,*auxInf;
     int numChars;
     char auxChar,auxSep;
     auxSep = '|';
     FILE *p;
     p = fopen("ini.conf","r");
     if (!p){
        return NULL;
     }
     numChars = countCharsFile("ini.conf");
     auxStr = (char*)malloc(sizeof(char)*(numChars+1));
     auxStr[0] = '\0';
     while ((auxChar = getc(p)) != EOF){
           if ((auxChar!='\n') && (auxChar!=' ')){
              strcat(auxStr,&auxChar);
           }else{
                 strcat(auxStr,&auxSep);
           }
     }
     auxInf = NULL;
     do{
        if (auxInf != NULL){
           free(auxInf);
        }
        auxInf = sepString(&auxStr,&auxSep);
     }while (strcmp(inf,auxInf)!=0);
     free(auxInf);
     return sepString(&auxStr,&auxSep);

}

char ***loadMessages(char *lang){
     char ***allMessages,*filePath,auxChar;
     int sizeLangStr,numMessages,numErrors,i,j;
     FILE *p;
     /*verifica se o parametro passado eh valido*/
     if (sizeLangStr!=4){
        return NULL;
     }
     /*monta o caminho do arquivo*/
     filePath = (char*)malloc(sizeof(char)*LANGFILEPATHSIZE);
     strcat(filePath,"./lang/");
     strcat(filePath,lang);
     strcat(filePath,".txt");

     p = fopen(filePath,"r");
     if (!p){
        return NULL;
     }
     /*verifica o numero de mensagens contido no texto segundo o cabecalho*/
     fscanf(p,"%d",&numMessages);
     if (numMessages<=0){
        return NULL;
     }
     /*caminha até o final da linha*/
     /*verifica o numero de mensagens de erro segundo o cabecalho*/
     while (getc(p)!='\n');
     fscanf(p,"%d",&numErrors);
     if (numErrors<=0){
        return NULL;
     }
     /*caminha até o final da linha*/
     while (getc(p)!='\n');
     /*agora comeca a leitura, entao ja reserva o espaco para os dois vetores de vetores de caracteres*/
     allMessages = (char***)malloc(sizeof(char**)*2);
     /*reserva o espaço para cada vetor de vetores de caracteres*/
     allMessages[MSG] = (char**)malloc(sizeof(char*)*(numMessages+1));
     allMessages[ERR] = (char**)malloc(sizeof(char*)*(numErrors+1));
     allMessages[MSG][numMessages] = NULL;
     allMessages[ERR][numErrors] = NULL;
     for (i=0;i<numMessages;i++){
         allMessages[MSG][i] = (char*)malloc(sizeof(char)*fileStringSize(*p,'\n'));
         j = 0;
         while ((auxChar = getc(p))!='\n'){
               allMessages[MSG][i][j] = auxChar;
         }
         
     }
     for (i=0;i<numErrors;i++){
         allMessages[ERR][i] = (char*)malloc(sizeof(char)*fileStringSize(*p,'\n'));
         j = 0;
         while ((auxChar = getc(p))!='\n'){
               allMessages[ERR][i][j] = auxChar;
         }
     }
     return allMessages;
}


