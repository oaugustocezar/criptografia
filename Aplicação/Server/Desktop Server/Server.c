#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define MAG   "\x1B[35m"
#define RESET "\x1B[0m"


#define MAX_MSG 1024

int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,
            unsigned char *iv, unsigned char *plaintext)
{
    EVP_CIPHER_CTX *ctx;

    int len;

    int plaintext_len;

    /* Create and initialise the context */
    if(!(ctx = EVP_CIPHER_CTX_new()))
        handleErrors();

    /*
     * Initialise the decryption operation. IMPORTANT - ensure you use a key
     * and IV size appropriate for your cipher
     * In this example we are using 256 bit AES (i.e. a 256 bit key). The
     * IV size for *most* modes is the same as the block size. For AES this
     * is 128 bits
     */
    if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
        handleErrors();

    /*
     * Provide the message to be decrypted, and obtain the plaintext output.
     * EVP_DecryptUpdate can be called multiple times if necessary.
     */
    if(1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
        handleErrors();
    plaintext_len = len;

    /*
     * Finalise the decryption. Further plaintext bytes may be written at
     * this stage.
     */
    if(1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len))
        handleErrors();
    plaintext_len += len;

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);

    return plaintext_len;
}

int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
            unsigned char *iv, unsigned char *ciphertext)
{
    EVP_CIPHER_CTX *ctx;

    int len;

    int ciphertext_len;

    /* Create and initialise the context */
    if(!(ctx = EVP_CIPHER_CTX_new()))
        handleErrors();

    /*
     * Initialise the encryption operation. IMPORTANT - ensure you use a key
     * and IV size appropriate for your cipher
     * In this example we are using 256 bit AES (i.e. a 256 bit key). The
     * IV size for *most* modes is the same as the block size. For AES this
     * is 128 bits
     */
    if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
        handleErrors();

    /*
     * Provide the message to be encrypted, and obtain the encrypted output.
     * EVP_EncryptUpdate can be called multiple times if necessary
     */
    if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
        handleErrors();
    ciphertext_len = len;

    /*
     * Finalise the encryption. Further ciphertext bytes may be written at
     * this stage.
     */
    if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len))
        handleErrors();
    ciphertext_len += len;

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);

    return ciphertext_len;
}

void handleErrors(void)
{
    ERR_print_errors_fp(stderr);
    abort();
}

/*
    Experimento 01

    Servidor aguarda por mensagem do cliente, imprime na tela
    e depois envia resposta e finaliza processo
*/

char * vetorAleatorio ( char * mensagem) {
	int min = 1; //1 byte -- 8bits
	int max = 16;// 16 -- 128 bits
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
int main(void)
{


	/* A 256 bit key */
    unsigned char *key = (unsigned char *)"01234567890123456789012345678901";

    /* A 128 bit IV */
    unsigned char *iv = (unsigned char *)"0123456789012345";

     /* Buffer for the decrypted text */
    unsigned char decryptedtext[128];
    unsigned char ciphertext[128];
    int decryptedtext_len, ciphertext_len;
    //variaveis
    int socket_desc, conexao, c;
    struct sockaddr_in servidor, cliente;
    char *mensagem;
    char resposta[MAX_MSG];
    int tamanho, count;

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
        perror("Não foi possível reusar endereço");
        return -1;
    }
#ifdef SO_REUSEPORT
    if (setsockopt(socket_desc, SOL_SOCKET, SO_REUSEPORT, (const char *)&reuso, sizeof(reuso)) < 0)
    {
        perror("Não foi possível reusar porta");
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
    printf("cliente conectou\nIP:PORTA -> %s:%d\n", cliente_ip, cliente_port);

    while (1)
    {
		// lendo dados enviados pelo cliente
		if ((tamanho = read(conexao, resposta, MAX_MSG)) < 0)
		{
			perror("Erro ao receber dados do cliente: ");
			return -1;
		}

		// Coloca terminador de string
		//resposta[tamanho] = '\0';
		printf(GRN"\n---Mensagem criptografada recebida---\n"RESET); 

		

		BIO_dump_fp (stdout, resposta, tamanho); // exibe o texto cifrado

		sleep(1);

		printf(YEL"\n\n---Decriptografando o texto---\n\n"RESET);

		sleep(3);




		decryptedtext_len = decrypt(resposta, tamanho, key, iv, decryptedtext); // decrypt retorna o tamanho do texto descriptografado. armazena o texto legível em decryptedtext

		// entrada a resposta cifrada, o tamanho da resposta lida pelo socket, a chave, o tamanho do bloco

		/* Add a NULL terminator. We are expecting printable text */
		decryptedtext[decryptedtext_len] = '\0';

		/* Show the decrypted text */
		printf(GRN"---Texto recebido decriptografado---:\n"RESET);
		printf(MAG"%s\n"RESET, decryptedtext); // exibe texto decriptografado 

		sleep(1);   

		printf("\n\n-------------------------------------\n\n");

		// Enviando resposta para o cliente
		
		
		mensagem = vetorAleatorio(mensagem);

		 printf(YEL"\nCriptografando texto de resposta\n\n"RESET);

		unsigned char *plaintext = (unsigned char *)mensagem;

		ciphertext_len = encrypt (plaintext, strlen((char *)plaintext), key, iv, ciphertext);

		sleep(3);
		
		
		write(conexao, ciphertext, ciphertext_len);

		puts(GRN"\n---Dados enviados---\n"RESET);
		printf("\n\n-------------------------------------\n\n");


		

    }
    

    close(socket_desc);
    shutdown(socket_desc, 2);

    printf("Servidor finalizado...\n");
    return 0;
}
