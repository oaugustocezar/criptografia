/*
 * teste.c
 *
 * Copyright 2020  <pi@raspberrypi>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */


#include <stdio.h>
#include <string.h>
#include <relic_bc.h> //  local onde está o include da lib
//#include </home/pi/Documents/relic/include/relic_bc.h> //  local onde está o include da lib

#define BC_len 16

int main()
{
	int outputsize = 32;
	int out_len = 32;
	/* A 128 bit key */
	uint8_t  *key = "0123456789012345";

    /* A 128 bit IV */
    uint8_t *iv = "0123456789012345";

     /* Buffer for the decrypted text */
    uint8_t decryptedtext[32];
    uint8_t ciphertext[32];
    uint8_t* mensagem= "012345678901234";

  // criptografando mensagem

	if(bc_aes_cbc_enc(ciphertext,&outputsize,mensagem,16,key,BC_len,iv)){
		printf("ERRO\n");

	}else{
		printf("Criptografado com sucesso\n");
	}

	printf("Outputsize %d\n", outputsize);

	// decriptografando texto
	if(bc_aes_cbc_dec(decryptedtext,&out_len,ciphertext,outputsize,key,BC_len,iv)){

		printf("ERRO\n");

	}else{
		printf("Descriptografado com sucesso\n");
	}

	printf("Decryptedtext: %s\n",decryptedtext);

	return 0;
}
