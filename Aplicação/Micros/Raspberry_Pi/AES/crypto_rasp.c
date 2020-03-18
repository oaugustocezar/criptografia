#include "crypto_rasp.h"

#define key_len 32

 void enc (estrutura * dados, uint8_t *mensagem)
 {

 	uint8_t *key, *iv;

 	if(key_len == 16){
 		key = "0123456789012345"; /* A 128 bit key */
		iv = "0123456789012345"; /* A 128 bit IV */

 	}else if(key_len == 24){
 		key = "012345678901234567890123"; /* A 192 bit key */
		iv = "012345678901234567890123"; /* A 192 bit IV */

 	}else if(key_len == 32){
 		key = "01234567890123450123456789012345"; /* A 256 bit key */
		iv = "01234567890123450123456789012345"; /* A 256 bit IV */

 	}else {

 		printf("Chave inválida");

 	}


	int out_len = MAX_MSG;
	int in_len;
	 
	in_len = strlen(mensagem);
	 
	 if(bc_aes_cbc_enc(dados->crypto,&out_len,mensagem,in_len,key,key_len,iv)) /* o texto é passado em mensagem e seu tamanho em in_len
	 o texto criptografado é armazenado em dados->crypto e o tamanho da saida em out_len*/
	{

		printf("ERRO\n");
		exit(1);

	}
	
	else
	{
		dados->buffer = out_len;
		if(DEBUG) 
			printf("\n\nCriptografado com sucesso\n\n");

	}
	
	 
	
		 		 
}

void dec (estrutura * dados)
{

	uint8_t *key, *iv;

	if(key_len == 16){

		key = "0123456789012345"; /* A 128 bit key */
		iv = "0123456789012345"; /* A 128 bit IV */

 	}else if(key_len == 24){

 		key = "012345678901234567890123"; /* A 192 bit key */
		iv = "012345678901234567890123"; /* A 192 bit IV */

 	}else if(key_len == 32){
 		key = "01234567890123450123456789012345"; /* A 256 bit key */
		iv = "01234567890123450123456789012345"; /* A 256 bit IV */


 	}else {

 		printf("Chave inválida");

 	}

	
	

   
    int out_len = MAX_MSG;
    
    if(bc_aes_cbc_dec(dados->decryptedtext,&out_len,dados->crypto,dados->buffer,key,key_len,iv)) /*  descriptografa, passando o texto cifrado
    em dados->buffer e o tamanho em dados->buffer, armazena o texto puro em decryptedtext e o seu tamanho em out_len */
    {	
    	if(DEBUG)
			printf("ERRO\n");
	

	}
	else
	{
		if(DEBUG)
			printf("\n\nDescriptografado com sucesso\n\n");
	}


    dados->decryptedtext[out_len] = '\0'; // Coloca terminador de string
    if(DEBUG)
    	printf("O cliente falou: %s\n", dados->decryptedtext); 
        
 }      
