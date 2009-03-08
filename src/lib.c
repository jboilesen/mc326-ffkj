//lib.c

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
