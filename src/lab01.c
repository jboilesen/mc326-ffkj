/*lab01.c */

#include "lib.h"

int main(){

	char string[]="O HC ! 8654 eh uma BiXo232Na $ e g1os1ta de D2AR o CU3!!!",
	     separators[]="?$";

	printf("%s\n\n", string);

	toUpper(string);

	printf("%s\n\n", string);

	toBlank(string, separators);

	printf("%s\n\n", string);

	return 0;
}



