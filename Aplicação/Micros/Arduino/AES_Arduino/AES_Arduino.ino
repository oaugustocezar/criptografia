
#include <relic_bc.h>
#include <string.h>

  
    unsigned char  *key = "01234567890123456789012345678901";

    /* A 128 bit IV */
     unsigned char *iv = "0123456789012345";

     /* Buffer for the decrypted text */
    unsigned char decryptedtext[128];
    unsigned char ciphertext[128];
    unsigned char* mensagem= "012345678901234";
    
   


/*============================================================================*/
/* Public definitions                                                         */
/*============================================================================*/

 

void setup() {
  // put your setup code here, to run once:

    Serial.begin(9600);


    
    
    

    

}

void loop() {
  // put your main code here, to run repeatedly: mensagem = (uint8_t*)testes;

  int outputsize;

  if (bc_aes_cbc_enc(ciphertext,&outputsize,mensagem,128,key,128,iv) == 0){
    
  }


 

 // String mensagem = "ola"; 
  //uint8_t text = (uint8_t )mensagem;// caracter por caracter 
   
 

    
 



}
