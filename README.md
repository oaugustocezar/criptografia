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


gcc crypto_rasp.c Client.c \
    -I/home/augusto/relic/relic-target/include \
    -I/home/augusto/relic/include \
    -L/home/augusto/relic/relic-target/lib \
    -lrelic_s \
    -o client 

 for i in {0..10}
do
	./client $i -k "oi teste" 127.0.0.1 
	sleep 3s
done



## Realizando testes com diferentes tipos de mensages ## 

Ao realizar testes criptografando uma imagem, inserir no script do cliente (compile_and_run_Client.sh) o parâmetro -f seguido do path da imagem que deseja realizar as operações. O ip do nó servidor é passado como último parâmetro.

Para testes com Strings, foi utilizado o parametro -k seguido da string entre aspas duplas. O ip do nó servidor é passado como último parâmetro.



O numero de repetições que o experimento será realizado também é definido no script e deve ser alterado com os mesmos valores, tanto no cliente, quanto no servidor. 

Ao terminar os experimentos um arquivo .csv será criado com os tempos de execução de cada operação. 











