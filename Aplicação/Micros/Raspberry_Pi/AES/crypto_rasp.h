#ifndef CRYPTO_RASP
#define CRYPTO_RASP

#define KEY_LEN 32
#define EXP 0

#define MAX_MSG 204800
#define DEBUG 0

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define MAG   "\x1B[35m"
#define RESET "\x1B[0m"


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
