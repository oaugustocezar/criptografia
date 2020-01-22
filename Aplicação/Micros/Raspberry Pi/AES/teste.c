
#include <stdio.h>
#include <string.h>
#include <relic_bc.h> 
#include <stdlib.h>

#define key_len 16
#define max_msg 1024



int main()
{
	
    /* A 128 bit key */
	uint8_t  *key = "0123456789012345";

    /* A 128 bit IV */
	uint8_t *iv = "0123456789012345";
	
	int out_len, in_len;
	
	uint8_t ciphertext[max_msg], decryptedtext[max_msg];
	
	
  

	uint8_t *mensagem; 
	
	mensagem = "isto e um teste de tamanho de mensagem criptografada e agora eu posso mandar mensagens grandes\n\n";
	
	in_len = strlen(mensagem);
		
	

	if(bc_aes_cbc_enc(ciphertext,&out_len,mensagem,in_len,key,key_len,iv)){
		printf("ERRO\n");
		

	}else{
		printf("\n\nCriptografado com sucesso\n\n");
	}
	
	in_len = out_len;
	
	if(bc_aes_cbc_dec(decryptedtext,&out_len,ciphertext,in_len,key,key_len,iv)){
		printf("ERRO\n");
		

	}else{
		printf("\n\nDescriptografado com sucesso\n\n");
	}
	
	printf("A mensagem eh: %s\n",decryptedtext);	
	
	fflush(stdin);
	
	uint8_t teste[max_msg] = "10";
	
	printf(" teatando %d",atoi(teste));
	

	return 0;
}
