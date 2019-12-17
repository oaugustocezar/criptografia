
// random_string.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>



char * vetorAleatorio ( char * mensagem, int min, int max) {
	min = 1; //1 byte -- 8bits
	max = 16;// 16 -- 128 bits
	char *validchars = "abcdefghijklmnopqrstuvwxyz";
	
	register int i;
	int str_len;
	
	// inicia o contador aleatório
	srand ( time(NULL ));

	// novo tamanho
	str_len = (rand() % max );

	// checa tamanho
	str_len += ( str_len < min ) ? min : 0;

	// aloca memoria
	mensagem = ( char * ) malloc ( (str_len + 1) * sizeof(char));
	if ( !mensagem ){
		printf("[*] Erro ao alocar memoria.\n" );
		exit ( EXIT_FAILURE );
	}
	
	// gera string aleatória
	for ( i = 0; i < str_len; i++ ) {
		mensagem[i] = validchars[ rand() % strlen(validchars) ];
		mensagem[i + 1] = 0x0;
	}

	

	return mensagem;
}

int main()
{
	char * mensagem;

	mensagem = vetorAleatorio(mensagem);

	puts(mensagem);
}

	

  	

	