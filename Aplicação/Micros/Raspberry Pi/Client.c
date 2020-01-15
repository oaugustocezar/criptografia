#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <relic_bc.h>

#define BC_len 16

#define MAX_MSG 1024

uint8_t * enc (uint8_t * mensagem){
	int outputsize = 32;
	int out_len = 32;
	/* A 128 bit key */
	uint8_t  *key = "0123456789012345";

    /* A 128 bit IV */
	uint8_t *iv = "0123456789012345";

     /* Buffer for the encrypted text */
    
	uint8_t *ciphertext = (uint8_t*) malloc(32 * sizeof(uint8_t));
	
	
    // criptografando mensagem

	if(bc_aes_cbc_enc(ciphertext,&outputsize,mensagem,16,key,BC_len,iv)){
		printf("ERRO\n");

	}else{
		printf("\n\nCriptografado com sucesso\n\n");
	}
	
	//printf("texto cifrado %s",ciphertext);

	//printf("Outputsize %d\n", outputsize);
	
	return ciphertext;
    
    
	}
	
uint8_t * dec (uint8_t * ciphertext){
	
	
	int outputsize = 32;
	int out_len = 32;
	/* A 128 bit key */
	uint8_t  *key = "0123456789012345";

    /* A 128 bit IV */
	uint8_t *iv = "0123456789012345";

     /* Buffer for the decrypted text */
    
    
	uint8_t *decryptedtext = (uint8_t*) malloc(32 * sizeof(uint8_t));
    
    
    // decriptografando texto
	if(bc_aes_cbc_dec(decryptedtext,&out_len,ciphertext,outputsize,key,BC_len,iv)){

		printf("ERRO\n");

	}else{
		printf("\n\nDescriptografado com sucesso\n\n");
	}

	//printf("Decryptedtext: %s\n",decryptedtext);
	
	
	return decryptedtext;
	
	
	}


int main(int argc, char *argv[])
{
	// variaveis
	int socket_desc;
	struct sockaddr_in servidor;
	uint8_t *mensagem;
	char resposta_servidor[MAX_MSG];
	int tamanho;
	uint8_t * ciphertext, *decryptedtext; 

	/*****************************************/
	/* Criando um socket */
	// AF_INET = ARPA INTERNET PROTOCOLS
	// SOCK_STREAM = orientado a conexao
	// 0 = protocolo padrao para o tipo escolhido -- TCP
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);

	/* Informacoes para conectar no servidor */
	// IP do servidor
	// familia ARPANET
	// Porta - hton = host to network short (2bytes)
	servidor.sin_addr.s_addr = inet_addr("127.0.0.1");
	servidor.sin_family = AF_INET;
	servidor.sin_port = htons(1234);

	//Conectando no servidor remoto
	if (connect(socket_desc, (struct sockaddr *)&servidor, sizeof(servidor)) < 0)
	{
		printf("Nao foi possivel conectar\n");
		return -1;
	}
	printf("Conectado no servidor\n");
	/*****************************************/

	/*******COMUNICAO - TROCA DE MENSAGENS **************/

	// Protocolo definido para essa aplicacao
	// 1 - Cliente conecta
	// 2 - Cliente envia mensagem
	// 3 - Servidor envia resposta


	//Enviando uma mensagem
	mensagem = "Oi servidor"; 
	//criptografando a mensagem
	ciphertext=enc (mensagem);
	
	
	
	if (send(socket_desc, ciphertext, strlen(ciphertext), 0) < 0)
	{
		printf("Erro ao enviar mensagem\n");
		return -1;
	}
	puts("Dados enviados\n");

	//Recebendo resposta do servidor
	if ((tamanho = recv(socket_desc, resposta_servidor, BC_len*2, 0)) < 0)
	{
		printf("Falha ao receber resposta\n");
		return -1;
	}
	printf("\nResposta recebida: ");
	
	
	
	decryptedtext = dec((uint8_t*)resposta_servidor);
	
	decryptedtext[tamanho] = '\0'; // adicionando fim de linha na string
	printf("\nReposta do Servidor: ");
	puts(decryptedtext);

	/*****************************************/
	close(socket_desc); // fechando o socket

	printf("Cliente finalizado com sucesso!\n");
	return 0;
}
