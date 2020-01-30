#ifndef CRYPTO_RASP
#define CRYPTO_RASP

#define MAX_MSG 102400
#define key_len 16
#include <sys/time.h> 

struct timeval utime;
    double T0,T1,T2,T3,T4,T5,T6,T7;
    
    

    
typedef struct {
	
	int16_t buffer; 
	uint8_t crypto[MAX_MSG];
	uint8_t decryptedtext[MAX_MSG];
	double DIFF_Server;
	
		
	}estrutura;

	

#endif //CRYPTO_RASP 
