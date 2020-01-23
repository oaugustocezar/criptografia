#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <relic_bc.h>
#include <time.h> 
#include <locale.h>


#define MAX_MSG 102400
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
		

 void socketClient (int * socket_desc){
	 
	 uint8_t ip[15];
	 
	 struct sockaddr_in servidor;
	 /* Criando um socket */
	// AF_INET = ARPA INTERNET PROTOCOLS
	// SOCK_STREAM = orientado a conexao
	// 0 = protocolo padrao para o tipo escolhido -- TCP
	*socket_desc = socket(AF_INET, SOCK_STREAM, 0);

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
	if (connect(*socket_desc, (struct sockaddr *)&servidor, sizeof(servidor)) < 0)
	{
		printf("Nao foi possivel conectar\n");
		exit(1);
		
	}
	printf("Conectado no servidor\n");
	
	 }	
	 
	 void enviaMsgServer (int * socket_desc, estrutura *dados){
		 
	if (send(*socket_desc, dados, MAX_MSG, 0) < 0)  // envia o texto cifrado para  server
	{
		printf("Erro ao enviar mensagem\n");
		exit(1);
	}
	puts("Dados enviados\n");
		 }
	 
	 void enc (estrutura * dados, uint8_t *mensagem, uint8_t *key, uint8_t *iv)
	 {
		 int out_len = MAX_MSG;
		int in_len;
		 
		 in_len = strlen(mensagem);
		 
		 if(bc_aes_cbc_enc(dados->crypto,&out_len,mensagem,in_len,key,key_len,iv)){
		printf("ERRO\n");
		exit(1);
		

		}else{
		printf("\n\nCriptografado com sucesso\n\n");
	}
	
	 
		dados->buffer = out_len; 
		 
		
		 
		}
		
void recebeMsg(int * socket_desc, estrutura *dados){
			
	int tamanho;
	
					
	if ((tamanho = recv(*socket_desc, dados->crypto, MAX_MSG, 0)) < 0)
	{
		printf("Falha ao receber resposta\n");
		exit(1);
		
		
	}
	printf("Resposta recebida:");
	dados->buffer = strlen(dados->crypto);
	
	
	
	
			
			
			}
			
 void fechaSocket (int * socket_desc)
 {
	 close(*socket_desc); // fechando o socket

		printf("Cliente finalizado com sucesso!\n");
	 }

 void dec (estrutura * dados, uint8_t *iv, uint8_t *key)
    {
        uint8_t decryptedtext[MAX_MSG]; 
        int out_len = MAX_MSG;
        
        if(bc_aes_cbc_dec(decryptedtext,&out_len,dados->crypto,dados->buffer,key,key_len,iv)){
		printf("ERRO\n");
		

	}else{
		printf("\n\nDescriptografado com sucesso\n\n");
	}
    
    

    // Coloca terminador de string
    decryptedtext[out_len] = '\0';
    printf("O cliente falou: %s\n", decryptedtext);
        
        }
        
        

int main()
{
	setlocale(LC_ALL,"Portuguese");
	
	
	// variaveis
	int socket_desc;	
	uint8_t mensagem[MAX_MSG];
	estrutura dados;
	
	
	uint8_t  *key = "0123456789012345"; /* A 128 bit key */

    
	uint8_t *iv = "0123456789012345"; /* A 128 bit IV */
	

	socketClient(&socket_desc); // cria socket e conecta ao servidor	
	
	
	printf("Insira uma mensagem para enviar ao servidor:\n\n");
	fgets(mensagem,MAX_MSG,stdin);
	
	enc(&dados,mensagem,key,iv); // criptografa mensagem 
	
	enviaMsgServer(&socket_desc,&dados); // envia mensagem para o servidor
		
	
	recebeMsg(&socket_desc,&dados); //Recebendo resposta do servidor
	dec(&dados, iv, key);
	
	fechaSocket(&socket_desc); // encerra a comunicação	

	
	return 0;
}
