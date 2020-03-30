
#include "crypto_rasp.h"



/*
	
	Cliente envia mensagem ao servidor e imprime resposta
	recebida do Servidor
	
*/


	

 void socketClient (int * socket_desc, char *ip )
 {
	 
	 //uint8_t ip[15];
	 
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
	
	//printf("\nInsira o IP do nó servidor:\n");
	//fgets(ip,15,stdin);
	
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
	printf("\nConectado no servidor\n");
	
}	
	 
 void enviaMsgServer (int * socket_desc, estrutura *dados)
{
	 
	if (send(*socket_desc, dados, MAX_MSG, 0) < 0)  // envia o texto cifrado para  server
	{
		printf("Erro ao enviar mensagem\n");
		exit(1);
	}
	if(DEBUG)
		puts("Dados enviados\n");
}
	 

		
void recebeMsg(int * socket_desc, estrutura *dados)
{

	int tamanho;
						
	if ((tamanho = recv(*socket_desc, dados->crypto, MAX_MSG, 0)) < 0) /* envia os bytes em dados->crypto*/
	{
		printf("Falha ao receber resposta\n");
		exit(1);
			
	}
	if(DEBUG)
		printf("Resposta recebida:");

	dados->buffer = strlen(dados->crypto); /*atribui o tamanho do buffer*/
				
}
			
 void fechaSocket (int * socket_desc)

{

	close(*socket_desc); // fechando o socket

	printf("\nCliente finalizado com sucesso!\n");
}



        

int main(int argc, char *argv[ ])
{
	setlocale(LC_ALL,"Portuguese");
	
	
	// variaveis
	int socket_desc;	
	estrutura dados; 
	FILE *pont_arq, *fp3;

	

	char ip [15];

	if (strcmp(argv[2],"-f") == 0){
		strcpy(ip, argv[4]);

	}else{
		strcpy(ip, argv[3]);

	}

	//printf("path %s", argv[3]);
	//printf("path %s", argv[3]);

	

	
	

	



	if(strcmp(argv[1],"0") == 0)
	{

		

        pont_arq = fopen("tempos_exec_Client.csv", "a");
        fprintf(pont_arq, "%s", "\n\n\nPC-PC, CHAVE 256 bits, Imagem\n");
        fprintf(pont_arq, "%s", "No Exp.,");
        fprintf(pont_arq, "%s","Tempo criptografia cliente:,");
        fprintf(pont_arq, "%s", "Tempo decriptografia cliente em ms:,");
        fprintf(pont_arq, "%s", "Tempo de envio entre os nós em ms:\n");
        fclose(pont_arq);
       

	}else
	{
		socketClient(&socket_desc, ip); // cria socket e conecta ao servidor	
		if (strcmp(argv[2],"-f") == 0)
		{
			FILE * fp;
			fp = fopen (argv[3],"rb");
			fread(&dados.decryptedtext,sizeof(uint8_t),MAX_MSG,fp);
			fclose(fp);
		}else
		{
			//printf("Insira uma mensagem para enviar ao servidor:\n\n");
			//fgets(dados.decryptedtext,MAX_MSG,stdin);
			strcpy(dados.decryptedtext,argv[2]);
		}		

			gettimeofday(&utime, NULL);

			T0 = utime.tv_sec + ( utime.tv_usec / 1000000.0 );
			
			enc(&dados,dados.decryptedtext); // criptografa mensagem 
			
			gettimeofday(&utime, NULL);

		    T1 = utime.tv_sec + ( utime.tv_usec / 1000000.0 );
		    
			
			enviaMsgServer(&socket_desc,&dados); // envia mensagem para o servidor
				
			
			recebeMsg(&socket_desc,&dados); //Recebendo resposta do servidor
			
			
			gettimeofday(&utime, NULL); 
			T6 = utime.tv_sec + ( utime.tv_usec / 1000000.0 ); 
			
			
			dec(&dados); // decriptografa mensagem 
			
			gettimeofday(&utime, NULL);

		    T7 = utime.tv_sec + ( utime.tv_usec / 1000000.0 );

		    pont_arq = fopen("tempos_exec_Client.csv", "a");
		    fprintf(pont_arq, "%s,", argv[1]);

		    fprintf(pont_arq, "%.10lf,", T1 - T0);
		        
			
		    
		    fprintf(pont_arq, "%.10lf,", T7 - T6);
		        
		    
		    fprintf(pont_arq, "%.10lf\n", (T6-T1-(dados.DIFF_Server)/2));
		    fclose(pont_arq);

		    if (strcmp(argv[2],"-f") == 0){

		    	fp3 = fopen("confirmacao.jpg","wb+"); 

  				fwrite (&dados.decryptedtext,1,MAX_MSG,fp3);

  				fclose(fp3);
		    }
		    
		    



	}

	fechaSocket(&socket_desc); // encerra a comunicação	

	
	return 0;
}
