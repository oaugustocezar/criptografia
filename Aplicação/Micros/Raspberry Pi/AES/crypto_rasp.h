#ifndef CRYPTO_RASP
#define CRYPTO_RASP

#define MAX_MSG 102400
#define key_len 16
#include <time.h> 
typedef struct {
	
	int16_t buffer; 
	uint8_t crypto[MAX_MSG];
	clock_t tempo;
	
	}estrutura;

	

#endif //CRYPTO_RASP 