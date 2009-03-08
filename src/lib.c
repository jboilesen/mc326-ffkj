/*lib.c*/

int isAlphaNumeric( char c ){

	if( (c>='A' && c<='Z') || (c>='0' && c<='9') ) return 1;
	return 0;

}

int toBlank( char *string, char *separators ){

	char *str, *sep;

	str = string;
	sep = separators;

	/*Se houver separadores*/
	if( *separators != '\0' ){

		while(1){
			str += strcspn( str, sep );
			if( *str != '\0' ) *str = ' ';
			else return 1;
		}
	}

	/*Se não houver separadores*/
	else{

		while( str != '\0' ){
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
