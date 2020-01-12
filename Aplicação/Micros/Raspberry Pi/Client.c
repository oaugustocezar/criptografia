#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define MAX_MSG 1024


int main(int argc, char *argv[])
{
	// variaveis
	int socket_desc;
	struct sockaddr_in servidor;
	char *mensagem;
	char resposta_servidor[MAX_MSG];
	int tamanho;

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
	if (send(socket_desc, mensagem, strlen(mensagem), 0) < 0)
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
