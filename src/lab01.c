/*lab01.c */

#include "lib.h"

int main(){

	Word *word;
	char string[200],
	     separators[]="?$!";

    while(1){
	gets(string);

	printf("%s\n\n", string);

	toUpper(string);
	printf("toUpper\n%s\n\n", string);

	toBlank(string, NULL);
	printf("toBlank\n%s\n\n", string);

	printf("blankSplit\nnumero de palavras %d\n\n", blankSplit(string, &word));
	printWord(word);

	printf("wordCount\npalavra diferentes %d\n\n",wordCount(&word));
	printWord(word);

    }

return 0;
}



