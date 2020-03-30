#ifndef CRYPTO_RASP
#define CRYPTO_RASP

#define MAX_MSG 2000000

#define DEBUG 0
#define KEY_LEN 32

#include <sys/time.h> 
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <relic_bc.h>
#include <sys/time.h> 
#include <locale.h>

struct timeval utime;
    double T0,T1,T2,T3,T4,T5,T6,T7;
    
    

    
typedef struct {
	
	int16_t buffer; 
	uint8_t crypto[MAX_MSG];
	uint8_t decryptedtext[MAX_MSG];
	double DIFF_Server;
	
		
	}estrutura;

	void dec (estrutura * dados);
	void enc (estrutura * dados, uint8_t *mensagem);

	

#endif //CRYPTO_RASP 
