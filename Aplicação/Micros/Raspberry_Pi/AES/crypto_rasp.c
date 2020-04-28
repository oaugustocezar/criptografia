#include "crypto_rasp.h"



 void enc (estrutura * dados, uint8_t *mensagem)
 {

 	uint8_t *key, *iv;

 	if(KEY_LEN == 16){
 		key = "0123456789012345"; /* A 128 bit key */
		iv = "0123456789012345"; /* A 128 bit IV */

 	}else if(KEY_LEN == 24){
 		key = "012345678901234567890123"; /* A 192 bit key */
		iv = "012345678901234567890123"; /* A 192 bit IV */

 	}else if(KEY_LEN == 32){
 		key = "01234567890123450123456789012345"; /* A 256 bit key */
		iv = "01234567890123450123456789012345"; /* A 256 bit IV */

 	}else {

 		printf("Chave inválida");

 	}


	int out_len = MAX_MSG;
	int in_len;
	 
	in_len = dados->tamanho_in;

	//printf("\ntamanho do texto a ser criptografado %d\n",in_len);
	 
	 if(bc_aes_cbc_enc(dados->crypto,&out_len,mensagem,in_len,key,KEY_LEN,iv)) /* o texto é passado em mensagem e seu tamanho em in_len
	 o texto criptografado é armazenado em dados->crypto e o tamanho da saida em out_len*/
	{

		printf(RED"ERRO NA CRIPTOGRAFIA\n"RESET);
		exit(1);

	}
	
	else
	{
		dados->buffer = out_len;
		if(DEBUG) 
			printf("\n\nCriptografado com sucesso\n\n");

	}

	//printf("\nSaida dos dados na criptografia %d",out_len);
	
	 
	
		 		 
}

void dec (estrutura * dados)
{

	uint8_t *key, *iv;

	if(KEY_LEN == 16){

		key = "0123456789012345"; /* A 128 bit key */
		iv = "0123456789012345"; /* A 128 bit IV */

 	}else if(KEY_LEN == 24){

 		key = "012345678901234567890123"; /* A 192 bit key */
		iv = "012345678901234567890123"; /* A 192 bit IV */

 	}else if(KEY_LEN == 32){
 		key = "01234567890123450123456789012345"; /* A 256 bit key */
		iv = "01234567890123450123456789012345"; /* A 256 bit IV */


 	}else {

 		printf("Chave inválida");

 	}

	
	

   
    int out_len = MAX_MSG;
    int in_len = dados->tamanho_in;

    //printf("\nentrada dos dados na decriptografia %d\n",in_len);
    
    if(bc_aes_cbc_dec(dados->decryptedtext,&out_len,dados->crypto,in_len,key,KEY_LEN,iv)) /*  descriptografa, passando o texto cifrado
    em dados->buffer e o tamanho em dados->buffer, armazena o texto puro em decryptedtext e o seu tamanho em out_len */
    {	
    	if(DEBUG)
			printf(RED"ERRO NA DECRIPTOGRAFIA\n"RESET);
		exit(1);
	

	}
	else
	{
		dados->buffer = out_len;
		//printf("buffer %d",dados->buffer);
		if(DEBUG)
			printf("\n\nDescriptografado com sucesso\n\n");

	}

	
    
    if(DEBUG)
    	printf("O cliente falou: %s\n", dados->decryptedtext); 
        
 }      