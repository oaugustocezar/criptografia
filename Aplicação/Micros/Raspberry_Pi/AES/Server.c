#include "crypto_rasp.h"






/*
    Servidor aguarda por mensagem do cliente, imprime na tela
    e depois envia resposta e finaliza processo
*/
void socketServer (int * socket_desc, int *conexao)
{
    int c;
    struct sockaddr_in servidor, cliente;
        //Criando um socket
    *socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (*socket_desc == -1)
    {
        printf("Nao foi possivel criar o socket\n");
       
    }

    int reuso = 1;
    if (setsockopt(*socket_desc, SOL_SOCKET, SO_REUSEADDR, (const char *)&reuso, sizeof(reuso)) < 0)
    {
        perror("Não foi possível reusar endereço");
        
    }
#ifdef SO_REUSEPORT
    if (setsockopt(*socket_desc, SOL_SOCKET, SO_REUSEPORT, (const char *)&reuso, sizeof(reuso)) < 0)
    {
        perror("Não foi possível reusar portas");
        
    }
    
#endif

    char *cliente_ip;
    int cliente_port;

    /*********************************************************/
    

    //Preparando a struct do socket
    servidor.sin_family = AF_INET;
    servidor.sin_addr.s_addr = INADDR_ANY; // Obtem IP do S.O.
    servidor.sin_port = htons(1234);

    //Associando o socket a porta e endereco
    if (bind(*socket_desc, (struct sockaddr *)&servidor, sizeof(servidor)) < 0)
    {
        perror("Erro ao fazer bind\n");
        
    }
    if(DEBUG)
        puts("\nBind efetuado com sucesso\n");

    // Ouvindo por conexoes
    listen(*socket_desc, 3);
    /*********************************************************/

    //Aceitando e tratando conexoes
    if(DEBUG){
        puts("Aguardando por conexoes...");

    }
    
    c = sizeof(struct sockaddr_in);
    *conexao = accept(*socket_desc, (struct sockaddr *)&cliente, (socklen_t *)&c);
    if (conexao < 0)
    {
        perror("Erro ao receber conexao\n");
        
    }
    /*********************************************************/

    /*********comunicao entre cliente/servidor****************/

    // pegando IP e porta do cliente
    cliente_ip = inet_ntoa(cliente.sin_addr);
    cliente_port = ntohs(cliente.sin_port);
    if(DEBUG){
         printf("cliente conectou\nIP:PORTA -> %s:%d\n", cliente_ip, cliente_port);

    }
   
        
}

void leMsg(int * conexao, estrutura *dados)
{
    int tamanho;
    // lendo dados enviados pelo cliente
          
    
    if ((tamanho = read(*conexao, dados, MAX_MSG)) < 0)
    {
        
            perror(RED"Erro ao receber dados do cliente: "RESET);
        
    }

    
    
    
    }
    



void enviaMsgClient(estrutura * dados, int * conexao)
{
    
    if (write(*conexao, &dados->crypto, MAX_MSG)< 0){
        printf(RED"Erro ao enviar"RESET);
        exit(1);
    }
    else {
        if(DEBUG){
            printf("Enviado com sucesso\n");

        }
        
    }


}

int main(int argc, char *argv[ ])
{
    setlocale(LC_ALL,"Portuguese"); 
    
    
    //variaveis
    
    FILE *pont_arq, *fp3;    
    
    
    int socket_desc, conexao,in_len;
    int out_len = MAX_MSG;
    
    uint8_t mensagem[MAX_MSG];
    estrutura dados;

   if(atoi(argv[1]) == 0){

        
    }else{
        printf(MAG"\nExp no %s iniciado\n"RESET,argv[1]);
    }
    
    

    
    
    
    

    
    if(strcmp(argv[1],"0") == 0){
        if(strcmp(argv[2],"-f") == 0){
            pont_arq = fopen("tempos_exec_Server_Imagem.csv", "a");
        }else{
            pont_arq = fopen("tempos_exec_Server_String.csv", "a");
      }
        
        if(EXP == 0)
            if(fprintf(pont_arq, "%s", "\n\n\nPC-PC,") < 0)
                printf("Erro de gravação no arquivo\n");
        if(EXP == 1)
            if (fprintf(pont_arq, "%s", "\n\n\nPC-Placa,") < 0)
                printf("Erro de gravação no arquivo\n");
        if(EXP == 2)
            if (fprintf(pont_arq, "%s", "\n\n\nPlaca-Placa,") < 0 )
                printf("Erro de gravação no arquivo\n");
        if(KEY_LEN == 16){
            if(fprintf(pont_arq, "%s", "CHAVE 128 bits,") < 0 )
                printf("Erro de gravação no arquivo\n");
        }else if(KEY_LEN == 24){
            if (fprintf(pont_arq, "%s", "CHAVE 192 bits,") < 0)
                printf("Erro de gravação no arquivo\n");
        }else if(KEY_LEN == 32){
            if (fprintf(pont_arq, "%s", "CHAVE 256 bits,") < 0)
                printf("Erro de gravação no arquivo\n");
        }
        if (strcmp(argv[2],"-f") == 0){
            if (fprintf(pont_arq, "%s", "Imagem\n") < 0)
                printf("Erro de gravação no arquivo\n");
        }else{
            if (fprintf(pont_arq, "%s", "String\n") < 0)
                printf("Erro de gravação no arquivo\n");
        }
         if (fprintf(pont_arq, "%s", "No Exp.,") < 0)
            printf("Erro de gravação no arquivo\n");
        if (fprintf(pont_arq, "%s", "Tempo decriptografia server em ms:,") < 0)
            printf("Erro de gravação no arquivo\n");
        if (fprintf(pont_arq, "%s", "Tempo criptografia server em ms:\n") < 0)
            printf("Erro de gravação no arquivo\n");
        fclose(pont_arq);

      

    }else {
        
        socketServer(&socket_desc,&conexao); // cria e inicializa o socket, atribui endereços e escuta conexões  
    
        leMsg(&conexao,&dados); // lê mensagens enviadas pelo cliente

        dados.tamanho_in = dados.buffer;

       


        if (ret_Val = gettimeofday(&utime, NULL) != 0){

                errnum = errno;
                printf("Value of errno: %d\n", errno);
                perror("Error printed by perror");
                printf("Error opening file: %s\n", strerror( errnum ));
            }else{
                T2 = utime.tv_sec + ( utime.tv_usec / 1000000.0 );

            }           
        
        dec(&dados); // descriptografa mensagens recebidas e exibe o texto 
        
        if (ret_Val = gettimeofday(&utime, NULL) != 0){

                errnum = errno;
                printf("Value of errno: %d\n", errno);
                perror("Error printed by perror");
                printf("Error opening file: %s\n", strerror( errnum ));
            }else{
                T3 = utime.tv_sec + ( utime.tv_usec / 1000000.0 );

            } 



             if (strcmp(argv[2],"-f") == 0){
                //printf("tamanho buffer %ld", sizeof(dados.decryptedtext));

                fp3 = fopen("confirmacaoServer.jpg","wb+"); 

                fwrite (&dados.decryptedtext,1,MAX_MSG,fp3);

                fclose(fp3);
            }




           
            
            



        dados.tamanho_in = dados.buffer;
       

           
        //printf("Insira uma resposta para enviar ao cliente:\n\n");
        //fgets(mensagem,MAX_MSG,stdin); 
        
        if (ret_Val = gettimeofday(&utime, NULL) != 0){

                errnum = errno;
                printf("Value of errno: %d\n", errno);
                perror("Error printed by perror");
                printf("Error opening file: %s\n", strerror( errnum ));
            }else{
                T4 = utime.tv_sec + ( utime.tv_usec / 1000000.0 );

            }           
        
        enc(&dados,dados.decryptedtext);     // criptografa mensagem 
        
        if (ret_Val = gettimeofday(&utime, NULL) != 0){

                errnum = errno;
                printf("Value of errno: %d\n", errno);
                perror("Error printed by perror");
                printf("Error opening file: %s\n", strerror( errnum ));
            }else{
                T5 = utime.tv_sec + ( utime.tv_usec / 1000000.0 );

            }           
        

        dados.DIFF_Server = T5 - T2 ;  
        
        enviaMsgClient(&dados,&conexao); // envia mensagem para o cliente 


         if(strcmp(argv[2],"-f") == 0){
            pont_arq = fopen("tempos_exec_Server_Imagem.csv", "a");
        }else{
            pont_arq = fopen("tempos_exec_Server_String.csv", "a");
        }

        if(fprintf(pont_arq, "%s,", argv[1]) < 0)
            printf("Erro de gravação no arquivo\n");

        if (fprintf(pont_arq, "%.10lf,", T3 - T2) < 0)
            printf("Erro de gravação no arquivo\n");
  
        if (fprintf(pont_arq, "%.10lf\n", T5- T4) < 0)
            printf("Erro de gravação no arquivo\n");
        fclose(pont_arq);
       


    }
    
    

    close(socket_desc);
    shutdown(socket_desc, 2);
    
    if(atoi(argv[1]) == 0){

        
    }else{
        printf(GRN"\nExp nº %s realizado com sucesso!\n"RESET,argv[1]);
    }

    if(DEBUG)
        printf("Servidor finalizado...\n");
    return 0;
}
