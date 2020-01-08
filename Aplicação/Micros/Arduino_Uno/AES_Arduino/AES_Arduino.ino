extern "C" {
  //#include <relic.h>
  //#include <relic_core.h>
  #include <relic_bc.h>
  //#define RLC_STR(S)        PSTR(S)
 }

#include <string.h>
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
  uint8_t  *key = "01234567890123456789012345678901";

    /* A 128 bit IV */
     uint8_t *iv = "0123456789012345";

     /* Buffer for the decrypted text */
    unsigned char decryptedtext[128];
    uint8_t ciphertext[128];
    uint8_t* mensagem= "012345678901234";

//  int code = RLC_ERR;
//
//  Serial.println(RLC_ERR);
//
//  /* Initialize library with default configuration. */
//  if (core_init() != RLC_OK) {
//    core_clean();
//  }
  bc_aes_cbc_enc(ciphertext,&outputsize,mensagem,128,key,128,iv);

  delay(1000);

}
