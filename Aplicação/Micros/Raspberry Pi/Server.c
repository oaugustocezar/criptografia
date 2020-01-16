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
#define BC_len 16





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
		printf("Criptografado com sucesso\n");
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

/*
    Experimento 01

    Servidor aguarda por mensagem do cliente, imprime na tela
    e depois envia resposta e finaliza processo
*/

int main(void)
{
    //variaveis
    int socket_desc, conexao, c;
    struct sockaddr_in servidor, cliente;
    uint8_t *mensagem;
    char resposta[MAX_MSG];
    int tamanho, count;
    uint8_t *decryptedtext;

    // para pegar o IP e porta do cliente
    char *cliente_ip;
    int cliente_port;

    /*********************************************************/
    //Criando um socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1)
    {
        printf("Nao foi possivel criar o socket\n");
        return -1;
    }

    int reuso = 1;
    if (setsockopt(socket_desc, SOL_SOCKET, SO_REUSEADDR, (const char *)&reuso, sizeof(reuso)) < 0)
    {
        perror("NÃ£o foi possÃ­vel reusar endereÃ§o");
        return -1;
    }
#ifdef SO_REUSEPORT
    if (setsockopt(socket_desc, SOL_SOCKET, SO_REUSEPORT, (const char *)&reuso, sizeof(reuso)) < 0)
    {
        perror("NÃ£o foi possÃ­vel reusar porta");
        return -1;
    }
#endif

    //Preparando a struct do socket
    servidor.sin_family = AF_INET;
    servidor.sin_addr.s_addr = INADDR_ANY; // Obtem IP do S.O.
    servidor.sin_port = htons(1234);

    //Associando o socket a porta e endereco
    if (bind(socket_desc, (struct sockaddr *)&servidor, sizeof(servidor)) < 0)
    {
        perror("Erro ao fazer bind\n");
        return -1;
    }
    puts("Bind efetuado com sucesso\n");

    // Ouvindo por conexoes
    listen(socket_desc, 3);
    /*********************************************************/

    //Aceitando e tratando conexoes
    puts("Aguardando por conexoes...");
    c = sizeof(struct sockaddr_in);
    conexao = accept(socket_desc, (struct sockaddr *)&cliente, (socklen_t *)&c);
    if (conexao < 0)
    {
        perror("Erro ao receber conexao\n");
        return -1;
    }
    /*********************************************************/

    /*********comunicao entre cliente/servidor****************/

    // pegando IP e porta do cliente
    cliente_ip = inet_ntoa(cliente.sin_addr);
    cliente_port = ntohs(cliente.sin_port);
    printf("\nCliente conectou\nIP:PORTA -> %s:%d\n", cliente_ip, cliente_port);

    // lendo dados enviados pelo cliente
    if ((tamanho = read(conexao, resposta,BC_len*2 )) < 0)
    {
        perror("Erro ao receber dados do cliente: ");
        return -1;
    }
    
    decryptedtext = dec((uint8_t*)resposta);
    

    // Coloca terminador de string
    decryptedtext[tamanho] = '\0';
    printf("\nO cliente falou: %s\n\n", decryptedtext);

    // Enviando resposta para o cliente
    mensagem = "Ola de volta!";
    
    uint8_t *ciphertext = enc(mensagem);
    write(conexao, ciphertext, strlen(ciphertext));
    
    printf("\nDados enviados\n");

    /*********************************************************/

    close(socket_desc);
    shutdown(socket_desc, 2);

    printf("Servidor finalizado...\n");
    return 0;
}
