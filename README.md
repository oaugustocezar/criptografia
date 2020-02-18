### Criptografia para sistemas embarcados ###

Estudo de algoritmos de criptografia para microcontroladores. 


### Compilando a biblioteca ###

Para compilar a biblioteca Relic, os passos seguidos foram conforme dita a documentação oficial

https://github.com/relic-toolkit/relic/wiki/Building 
 

A escolha do preset é de acordo com a arquitetura onde a biblioteca deverá ser compilada. 

Caso desejado compilar a biblioteca em um computador convencional, não há necessidade da escolha
de um preset. 

Presets escolhidos: 

----Raspberry Pi 3 (com SO raspibian)----

arm-pbc-bn-254.sh

----Arduino UNO----

armuno-pbc-bn254.sh (editado por natássya) -- problemas com memória insuficiente do arduino

----Computador convencional (ubuntu 19.04)----

sem preset

### Compilando códigos em C com a Relic ###

Um script foi feito para facilitar a compilação e execução dos códigos em C produzidos. 

O script deve ser alterado de acordo com os paths da Relic já compilada. 

O script modelo tem a seguinte forma: 


gcc teste.c \
    -I/home/pi/Documents/relic/relic-target/include \ 
    -I/home/pi/Documents/relic/include \
    -L//home/pi/Documents/relic/relic-target/lib \
    -lrelic_s \
    -o teste
./teste



