
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
	if(DEBUG)
		printf("\nConectado no servidor\n");
	
}	
	 
 void enviaBytesServer (int * socket_desc, estrutura *dados)
{
	 
	if (send(*socket_desc, &dados->buffer, sizeof(dados->buffer), 0) < 0)  // envia o texto cifrado para  server
	{
		printf(RED"Erro ao enviar mensagem\n"RESET);
		exit(1);
	}
	if(DEBUG)
		puts("Tamanho enviado ao servidor\n");
}


void enviaMsgServer (int * socket_desc, estrutura *dados)
{
	
	 
	if (send(*socket_desc, dados->crypto, dados->buffer , 0) < 0)  // envia o texto cifrado para  server
	{
		printf(RED"Erro ao enviar mensagem\n"RESET);
		exit(1);
	}
	if(DEBUG)
		printf("Mensagem criptograda enviada\n");
}

	 

		
void recebeBytes(int * socket_desc, estrutura *dados)
{

	int tamanho;

	tamanho = 0;
	dados->tamanho_in = 0;
	memset(&dados->tamanho_in, 0, sizeof(dados->tamanho_in));

	

			if ((tamanho = recv(*socket_desc, &dados->tamanho_in, 4, 0)) < 0) /* envia os bytes em dados->crypto*/
		{
			printf("Falha ao receber resposta\n");
			exit(1);
				
		}
		if(DEBUG)
			printf("Tamanho recebido do cliente %d\n", dados->tamanho_in);

	}
	

	
				




void recebeTempo(int * socket_desc, estrutura *dados)
{

	int tamanho;

	tamanho = 0;


	while(tamanho < 8)
    {
      
        tamanho += recv(*socket_desc, &dados->DIFF_Server+tamanho, 8,0);


        
      
    }
	
	

	

			/*if ((tamanho = recv(*socket_desc, &dados->DIFF_Server,8 , 0)) < 0) /* envia os bytes em dados->crypto
		{
			printf("Falha ao receber resposta\n");
			exit(1);
				
		}
		if(DEBUG)
			printf("Resposta recebida:");*/

	

	//printf("tamanho do double %ld", sizeof(dados->DIFF_Server));
	

	
				
}


void recebeMsg(int * socket_desc, estrutura *dados)
{

	int tamanho;

	tamanho = 0;
	memset(&dados->crypto, 0, dados->tamanho_in);



	while(tamanho < dados->tamanho_in)
    {
      
        tamanho += recv(*socket_desc, dados->crypto+tamanho, dados->tamanho_in+8,0);

        
      
    }
    if(DEBUG)
    	printf("Mensagem criptograda recebida de tamanho %d\n", tamanho);

	

						
	/*if ((tamanho = recv(*socket_desc, dados->crypto, dados->tamanho_in, 0)) < 0) /* envia os bytes em dados->crypto
	{
		printf("Falha ao receber resposta\n");
		exit(1);
			
	}
	if(DEBUG)
		printf("Mensagem criptograda recebida de tamanho %d", tamanho);*/


	dados->tamanho_in = tamanho; /*atribui o tamanho do buffer*/
				
}
			
 void fechaSocket (int * socket_desc)

{

	close(*socket_desc); // fechando o socket
	if(DEBUG)
		printf("\nCliente finalizado com sucesso!\n");
}



        

int main(int argc, char *argv[ ])
{

	extern int errno ;
	setlocale(LC_ALL,"Portuguese");
	
	
	// variaveis
	int socket_desc;	
	estrutura dados; 
	FILE *pont_arq, *fp3,*fp2;

	strcpy(dados.crypto,"\0");
    strcpy(dados.decryptedtext,"\0");
    dados.buffer = 0;
    dados.tamanho_in = 0;
    dados.DIFF_Server = 0.0;
	
	

	

	char ip [15];

	if (strcmp(argv[2],"-f") == 0){
		strcpy(ip, argv[4]);

	}else{
		strcpy(ip, argv[3]);

	}

	//printf("path %s", argv[3]);
	//printf("path %s", argv[3]);

	

	
	if(atoi(argv[1]) == 0){

		
	}else{
		printf(MAG"\nExp no %s iniciado\n"RESET,argv[1]);
	}

	strcpy(dados.decryptedtext,"\0");


	



	if(strcmp(argv[1],"0") == 0)
	{

		

        if(strcmp(argv[2],"-f") == 0){
            pont_arq = fopen("tempos_exec_Client_Imagem.csv", "a");
        }else{
            pont_arq = fopen("tempos_exec_Client_String.csv", "a");
        }
        if(EXP == 0)
        	if(fprintf(pont_arq, "%s", "\n\n\nPC-PC,") < 0)
        		printf("Erro de gravação no arquivo\n");
        if(EXP == 1)
        	if(fprintf(pont_arq, "%s", "\n\n\nPC-Placa,") < 0)
        		printf("Erro de gravação no arquivo\n");
        if(EXP == 2)
        	if (fprintf(pont_arq, "%s", "\n\n\nPlaca-Placa,") <0)
        		printf("Erro de gravação no arquivo\n");
        if(KEY_LEN == 16){
        	if(fprintf(pont_arq, "%s", "CHAVE 128 bits,") < 0)
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
        	if(fprintf(pont_arq, "%s", "String\n") < 0)
        		printf("Erro de gravação no arquivo\n");
        }

        fprintf(pont_arq, "%s", "No Exp.,");
        fprintf(pont_arq, "%s","Tempo criptografia cliente:,");
        fprintf(pont_arq, "%s", "Tempo decriptografia cliente em ms:,");
        fprintf(pont_arq, "%s", "Tempo de envio entre os nos em ms:\n");
        fclose(pont_arq);


        if(strcmp(argv[1],"0") == 0)
	{

		

        if(strcmp(argv[2],"-f") == 0){
            fp2 = fopen("Tempos_SEP_Client_Imagem.csv", "a");
        }else{
            fp2 = fopen("Tempos_SEP_Client_String.csv", "a");
        }
        if(EXP == 0)
        	if(fprintf(fp2, "%s", "\n\n\nPC-PC,") < 0)
        		printf("Erro de gravação no arquivo\n");
        if(EXP == 1)
        	if(fprintf(fp2, "%s", "\n\n\nPC-Placa,") < 0)
        		printf("Erro de gravação no arquivo\n");
        if(EXP == 2)
        	if (fprintf(fp2, "%s", "\n\n\nPlaca-Placa,") <0)
        		printf("Erro de gravação no arquivo\n");
        if(KEY_LEN == 16){
        	if(fprintf(fp2, "%s", "CHAVE 128 bits,") < 0)
        		printf("Erro de gravação no arquivo\n");
        }else if(KEY_LEN == 24){
        	if (fprintf(fp2, "%s", "CHAVE 192 bits,") < 0)
        		printf("Erro de gravação no arquivo\n");
        }else if(KEY_LEN == 32){
        	if (fprintf(fp2, "%s", "CHAVE 256 bits,") < 0)
        		printf("Erro de gravação no arquivo\n");
        }
        if (strcmp(argv[2],"-f") == 0){
        	if (fprintf(fp2, "%s", "Imagem\n") < 0)
        		printf("Erro de gravação no arquivo\n");
        }else{
        	if(fprintf(fp2, "%s", "String\n") < 0)
        		printf("Erro de gravação no arquivo\n");
        }

        fprintf(fp2, "%s", "No Exp.,");
        fprintf(fp2, "%s","T0,");
        fprintf(fp2, "%s", "T1,");
        fprintf(fp2, "%s", "T6,");
        fprintf(fp2, "%s", "T7\n");
        fclose(fp2);
    }
       

	}else
	{
		socketClient(&socket_desc, ip); // cria socket e conecta ao servidor	
		if (strcmp(argv[2],"-f") == 0)
		{
			FILE * fp;
			fp = fopen (argv[3],"rb");
			dados.tamanho_in = fread(&dados.decryptedtext,sizeof(uint8_t),MAX_MSG,fp);
			fclose(fp);
		}else
		{
			//printf("Insira uma mensagem para enviar ao servidor:\n\n");
			//fgets(dados.decryptedtext,MAX_MSG,stdin);
			//printf("%ld",strlen(argv[2]));

			strcpy(dados.decryptedtext,argv[2]);
			dados.decryptedtext[strlen(dados.decryptedtext)] = '\0';
			dados.tamanho_in  = strlen(dados.decryptedtext);

		}		

			if (ret_Val = gettimeofday(&utime, NULL) != 0){

				errnum = errno;
				printf("Value of errno: %d\n", errno);
      			perror("Error printed by perror");
      			printf("Error opening file: %s\n", strerror( errnum ));
			}else{
				T0 = utime.tv_sec + ( utime.tv_usec / 1000000.0 );

			}
			
			
			enc(&dados,dados.decryptedtext); // criptografa mensagem 
			
			if (ret_Val = gettimeofday(&utime, NULL) != 0){

				errnum = errno;
				printf("Value of errno: %d\n", errno);
      			perror("Error printed by perror");
      			printf("Error opening file: %s\n", strerror( errnum ));
			}else{
				T1 = utime.tv_sec + ( utime.tv_usec / 1000000.0 );

			}

			enviaBytesServer(&socket_desc,&dados);
			
			enviaMsgServer(&socket_desc,&dados); // envia mensagem para o servidor

			recebeBytes(&socket_desc,&dados);				
			
			recebeMsg(&socket_desc,&dados); //Recebendo resposta do servidor
			//sleep(1);
			recebeTempo(&socket_desc,&dados);
			//printf("\nTempo recebebido %.10f",dados.DIFF_Server);
			
			//printf("teste");
			

			//printf("\ndados.tamanho_in %d",dados.tamanho_in);
			//printf("\ndados.buffer %d", dados.buffer);



			dados.tamanho_in = dados.buffer;

			//printf("dados antes da decriptografa %d",dados.tamanho_in);

			

			
			
			if (ret_Val = gettimeofday(&utime, NULL) != 0){

				errnum = errno;
				printf("Value of errno: %d\n", errno);
      			perror("Error printed by perror");
      			printf("Error opening file: %s\n", strerror( errnum ));
			}else{
				T6 = utime.tv_sec + ( utime.tv_usec / 1000000.0 );

			} 
			
			
			dec(&dados); // decriptografa mensagem 
			//printf("tamanho buffer %d",strlen(dados.decryptedtext));

			
			
			if (ret_Val = gettimeofday(&utime, NULL) != 0){

				errnum = errno;
				printf("Value of errno: %d\n", errno);
      			perror("Error printed by perror");
      			printf("Error opening file: %s\n", strerror( errnum ));
			}else{
				T7 = utime.tv_sec + ( utime.tv_usec / 1000000.0 );

			}

			

		      if(strcmp(argv[2],"-f") == 0){
            		pont_arq = fopen("tempos_exec_Client_Imagem.csv", "a");
        	}else{
            		pont_arq = fopen("tempos_exec_Client_String.csv", "a");
        	}

		    if (fprintf(pont_arq, "%s,", argv[1]) < 0 ){
		    	printf("Erro de gravação no arquivo\n");
		    	
		    }


		    if(fprintf(pont_arq, "%.10lf,", T1 - T0) < 0 ){
		    	printf("Erro de gravação no arquivo\n");

		    }

		        
			
		    
		    if(fprintf(pont_arq, "%.10lf,", T7 - T6) < 0){
		    	printf("Erro de gravação no arquivo\n");
		    }

		    //printf("%s",argv[5]);





		        
		    
		    if (fprintf(pont_arq, "%.10lf\n", (T6-T1-(dados.DIFF_Server))/2) < 0)
		    	printf("Erro de gravação no arquivo\n");
		    
		    fclose(pont_arq);



		    if(strcmp(argv[2],"-f") == 0){
            		fp2 = fopen("Tempos_SEP_Client_Imagem.csv", "a");
        	}else{
            		fp2 = fopen("Tempos_SEP_Client_String.csv", "a");
        	}

		    if (fprintf(fp2, "%s,", argv[1]) < 0 ){
		    	printf("Erro de gravação no arquivo\n");
		    	
		    }


		    if(fprintf(fp2, "%.10lf,",T0) < 0 ){
		    	printf("Erro de gravação no arquivo\n");

		    }	    
		        
			
		    
		    if(fprintf(fp2, "%.10lf,", T1) < 0){
		    	printf("Erro de gravação no arquivo\n");
		    }

		    //printf("%s",argv[5]);





		        
		    
		    if (fprintf(fp2, "%.10lf,", T6) < 0)
		    	printf("Erro de gravação no arquivo\n");

		    if (fprintf(fp2, "%.10lf\n", T7) < 0)
		    	printf("Erro de gravação no arquivo\n");

		    
		    fclose(fp2);
		    

		    if (strcmp(argv[2],"-f") == 0){
		    	

		    	fp3 = fopen(argv[5],"wb+"); 

  				fwrite (&dados.decryptedtext,1,dados.buffer,fp3);

  				fclose(fp3);
		    }else{

		    	fp3 = fopen(argv[6],"wb+"); 

  				fwrite (&dados.decryptedtext,1,dados.buffer,fp3);

  				fclose(fp3);

		    }


		  


}
	fechaSocket(&socket_desc); // encerra a comunicação	
	if(atoi(argv[1]) == 0){

		
	}else{
		printf(GRN"\nExp nº %s realizado com sucesso!\n"RESET,argv[1]);
	}

	

	
	return 0;
}
