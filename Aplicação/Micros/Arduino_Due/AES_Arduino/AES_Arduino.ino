extern "C" { 

  #include <relic_bc.h>
 }
 
#include <string.h>
#define MAX_MSG 102400
#define DEBUG 0
  
    
    

   

/*============================================================================*/
/* Public definitions                                                         */
/*============================================================================*/

 

void setup() {
  // put your setup code here, to run once:

    Serial.begin(115200);

}

void loop() {
  

   uint8_t key[] = "01234567890123456789012345678901"; // KEY 256 BITS
  

    /* A 128 bit IV */
    uint8_t iv[] = "01234567890123456789012345678901"; // IV 256 BITS 

     /* Buffer for the decrypted text */
    unsigned char decryptedtext[MAX_MSG];
    uint8_t ciphertext[MAX_MSG];
    char plaintext[MAX_MSG];
    char *mensagem = "Isso e um teste muito serio";
    int in_len = 0;
    int out_len = MAX_MSG;
    in_len = strlen(mensagem);
    

 
  if (bc_aes_cbc_enc(ciphertext,&out_len,(uint8_t*)mensagem,in_len,key,32,iv)){
    if(DEBUG)
      Serial.println("ERRO enc");       
    
  }else{
    if(DEBUG)
      Serial.println("Sucesso enc");
  }
  
  in_len = out_len; 
  out_len = in_len;
 
   if (bc_aes_cbc_dec((uint8_t*)plaintext,&out_len,ciphertext,in_len,key,32,iv)){
    if(DEBUG)
      Serial.println("ERRO dec");
   }else{
    if(DEBUG)    
      Serial.println("Sucesso dec");
       
   }

   

   plaintext[out_len]='\0';  
   
   
   Serial.print("Resultado da cifra: "); Serial.println ((char*)plaintext);
   Serial.flush();

   delay(1000);

  

  

}
