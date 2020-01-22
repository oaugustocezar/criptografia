#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <relic_bc.h>


#define MAX_MSG 1024
#define key_len 16
/*
	
	Cliente envia mensagem ao servidor e imprime resposta
	recebida do Servidor
	
*/

	typedef struct {
		
		int16_t buffer; 
		uint8_t crypto[MAX_MSG];
		clock_t tempo;
		
		}estrutura;

int main()
{
	// variaveis
	int socket_desc;
	struct sockaddr_in servidor;
	uint8_t mensagem[MAX_MSG];
	char resposta_servidor[MAX_MSG];
	int tamanho;
	estrutura dados;
	uint8_t ip[15];
	
	/* A 128 bit key */
	uint8_t  *key = "0123456789012345";

    /* A 128 bit IV */
	uint8_t *iv = "0123456789012345";
	
	int out_len = MAX_MSG;
	int in_len;
	
	uint8_t ciphertext[MAX_MSG], decryptedtext[MAX_MSG];
	
	

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
	
	printf("\nInsira o IP do nó servidor:\n");
	fgets(ip,15,stdin);
	fflush(stdin);
	servidor.sin_addr.s_addr = inet_addr(ip);
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
	
	
	
	
	
	printf("Insira uma mensagem para enviar ao servidor:\n\n");
	fgets(mensagem,MAX_MSG,stdin);
	
	
	
	in_len = strlen(mensagem);
	
	printf("\nTamanho da mensagem %d\n", in_len);
	
	
	
	if(bc_aes_cbc_enc(dados.crypto,&out_len,mensagem,in_len,key,key_len,iv)){
		printf("ERRO\n");
		

	}else{
		printf("\n\nCriptografado com sucesso\n\n");
	}
	
	 
	dados.buffer = out_len; 
	
	
	//printf("Tamanho do buffer %d %d", out_len, dados.buffer);	
	

	//if (send(socket_desc, &out_len, strlen(mensagem), 0) < 0) // envia o tamanho do buffer para descriptografar no server
	//{
		//printf("Erro ao enviar mensagem\n");
		//return -1;
	//}
	//puts("Tamanho do buffer enviado\n");
	
	
	if (send(socket_desc, &dados, MAX_MSG, 0) < 0)  // envia o texto cifrado para  server
	{
		printf("Erro ao enviar mensagem\n");
		return -1;
	}
	puts("Dados enviados\n");
	
	

	//Recebendo resposta do servidor
	if ((tamanho = recv(socket_desc, resposta_servidor, MAX_MSG, 0)) < 0)
	{
		printf("Falha ao receber resposta\n");
		return -1;
	}
	printf("Resposta recebida: ");
	resposta_servidor[tamanho] = '\0'; // adicionando fim de linha na string
	puts(resposta_servidor);

	/*****************************************/
	close(socket_desc); // fechando o socket

	printf("Cliente finalizado com sucesso!\n");
	return 0;
}
