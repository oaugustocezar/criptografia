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
        if(DEBUG)
            perror("Erro ao receber dados do cliente: ");
        
    }
    
    
    }
    



void enviaMsgClient(estrutura * dados, int * conexao)
{
    
    if (write(*conexao, &dados->crypto, strlen(dados->crypto))< 0){
        printf("Erro ao enviar");
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
    
    FILE *pont_arq;    
    
    
    int socket_desc, conexao,in_len;
    int out_len = MAX_MSG;
    
    uint8_t mensagem[MAX_MSG];
    estrutura dados;

   if(atoi(argv[1]) == 0){

        
    }else{
        printf(MAG"\nExp no %s iniciado\n"RESET,argv[1]);
    }
    
    

    
    
    
    

    
    if(strcmp(argv[1],"0") == 0){
        pont_arq = fopen("tempos_exec_Server.csv", "a");
        if(EXP == 0)
            fprintf(pont_arq, "%s", "\n\n\nPC-PC,");
        if(EXP == 1)
            fprintf(pont_arq, "%s", "\n\n\nPC-Placa,");
        if(EXP == 2)
            fprintf(pont_arq, "%s", "\n\n\nPlaca-Placa,");
        if(KEY_LEN == 16){
            fprintf(pont_arq, "%s", "CHAVE 128 bits,");
        }else if(KEY_LEN == 24){
            fprintf(pont_arq, "%s", "CHAVE 192 bits,");
        }else if(KEY_LEN == 32){
            fprintf(pont_arq, "%s", "CHAVE 256 bits,");
        }
        if (strcmp(argv[2],"-f") == 0){
            fprintf(pont_arq, "%s", "Imagem\n");
        }else{
            fprintf(pont_arq, "%s", "String\n");
        }
        fprintf(pont_arq, "%s", "No Exp.,");
        fprintf(pont_arq, "%s", "Tempo decriptografia server em ms:,");
        fprintf(pont_arq, "%s", "Tempo criptografia server em ms:\n");
        fclose(pont_arq);

      

    }else {
        
        socketServer(&socket_desc,&conexao); // cria e inicializa o socket, atribui endereços e escuta conexões  
    
        leMsg(&conexao,&dados); // lê mensagens enviadas pelo cliente
        
        gettimeofday(&utime, NULL);
        T2 = utime.tv_sec + ( utime.tv_usec / 1000000.0 );
        
        dec(&dados); // descriptografa mensagens recebidas e exibe o texto 
        
        gettimeofday(&utime, NULL);

        T3 = utime.tv_sec + ( utime.tv_usec / 1000000.0 );
       

           
        //printf("Insira uma resposta para enviar ao cliente:\n\n");
        //fgets(mensagem,MAX_MSG,stdin); 
        
        gettimeofday(&utime, NULL);
        T4 = utime.tv_sec + ( utime.tv_usec / 1000000.0 );
        
        enc(&dados,dados.decryptedtext);     // criptografa mensagem 
        
        gettimeofday(&utime, NULL);

        T5 = utime.tv_sec + ( utime.tv_usec / 1000000.0 );
        

        dados.DIFF_Server = T5 - T2 ;  
        
        enviaMsgClient(&dados,&conexao); // envia mensagem para o cliente 


        pont_arq = fopen("tempos_exec_Server.csv", "a");

        fprintf(pont_arq, "%s,", argv[1]);

        fprintf(pont_arq, "%.10lf,", T3 - T2);
  
        fprintf(pont_arq, "%.10lf\n", T5- T4);
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
