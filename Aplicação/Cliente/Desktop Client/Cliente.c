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


     /*
     * Set up the key and iv. Do I need to say to not hard code these in a
     * real application? :-)
     */

    /* A 256 bit key */
    unsigned char *key = (unsigned char *)"01234567890123456789012345678901";

    /* A 128 bit IV */
    unsigned char *iv = (unsigned char *)"0123456789012345";

       /*
     * Buffer for ciphertext. Ensure the buffer is long enough for the
     * ciphertext which may be longer than the plaintext, depending on the
     * algorithm and mode.
     */

    unsigned char ciphertext[128];

    /* Buffer for the decrypted text */
    unsigned char decryptedtext[128];

    int decryptedtext_len, ciphertext_len;




    while (1){

        //printf("Escreva a mensagem para enviar:\n");
        mensagem = vetorAleatorio(mensagem); // insere mensagem

        
        
        
            

        unsigned char *plaintext = (unsigned char *)mensagem; // coloca no formato adequado para criptografar

         
        

            printf(YEL"\nCriptografando texto para enviar\n\n"RESET);
            ciphertext_len = encrypt (plaintext, strlen((char *)plaintext), key, iv, ciphertext); // encrypt retorna o tamanho do texto criptografado (inteiro), passa o texto puro
        // o tamanho do texto puro, a chave, tamanho do bloco e o vetor onde o texto criptografado é armazenado
            BIO_dump_fp (stdout, ciphertext, ciphertext_len); // exibe o texto cifrado

            //Enviando uma mensagem
    
        if (send(socket_desc, (char *)ciphertext,ciphertext_len , 0) < 0) // enviando mensagem criptografada, passa o socket, o texto criptografado, o tamanho do texto criptografado

            {
                printf(RED"Erro ao enviar mensagem\n"RESET);
                return -1;
            }
            puts(GRN"---Dados enviados---\n"RESET);
            printf("\n\n-------------------------------------\n\n");

            sleep(1);

            //Recebendo resposta do servidor
        if ((tamanho = recv(socket_desc, resposta_servidor, MAX_MSG, 0)) < 0)
            {
                 printf(RED"\nFalha ao receber resposta\n"RESET);
                return -1;
            }
        printf(GRN"\n---Resposta criptografada recebida---\n"RESET);
        resposta_servidor[tamanho] = '\0'; // adicionando fim de linha na string

        BIO_dump_fp (stdout, resposta_servidor, tamanho);

        sleep(1);

        printf(YEL"---Decriptografando o texto da resposta---\n"RESET);

        sleep(3);

        decryptedtext_len = decrypt(resposta_servidor, tamanho, key, iv, decryptedtext); // decrypt retorna o tamanho do texto descriptografado. armazena o texto legível em decryptedtext

        // entrada a resposta cifrada, o tamanho da resposta lida pelo socket, a chave, o tamanho do bloco

        /* Add a NULL terminator. We are expecting printable text */
        decryptedtext[decryptedtext_len] = '\0';

        /* Show the decrypted text */
        printf(GRN"\n---Texto recebido decriptografado---\n"RESET);
        printf(MAG"%s\n"RESET, decryptedtext); // exibe texto decriptografado 
        printf("\n\n-------------------------------------\n\n");







    }

    close(socket_desc); // fechando o socket

    printf("Cliente finalizado com sucesso!\n");

    

 


   
  
    




    /* Decrypt the ciphertext 
    decryptedtext_len = decrypt(ciphertext, ciphertext_len, key, iv, decryptedtext);

    /* Add a NULL terminator. We are expecting printable text 
    decryptedtext[decryptedtext_len] = '\0';

    Show the decrypted text 
    printf("Decrypted text is:\n");
    printf("%s\n", decryptedtext);   */

    


    

    

    /*****************************************/
    

    



return 0;
 
}
