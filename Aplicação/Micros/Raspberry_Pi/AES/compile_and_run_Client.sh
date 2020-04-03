gcc crypto_rasp.c Client.c \
    -I/home/augusto/relic/relic-target/include \
    -I/home/augusto/relic/include \
    -L/home/augusto/relic/relic-target/lib \
    -lrelic_s \
    -o client 


	for i in {0..100}
do
	./client $i "criptografando mensagens para realizar testes de tempo de criptografia e decriptografia em um sistema de comunicação cliente-servidorcriptografando mensagens para realizar testes de tempo de criptografia e decriptografia em um sistema de comunicação cliente-servidorcriptografando mensagens para realizar testes de tempo de criptografia e decriptografia em um sistema de comunicação cliente-servidorcriptografando mensagens para realizar testes de tempo de criptografia e decriptografia em um sistema de comunicação cliente-servidorcriptografando mensagens para realizar testes de tempo de criptografia e decriptografia em um sistema de comunicação cliente-servidorcriptografando mensagens para realizar testes de tempo de criptografia e decriptografia em um sistema de comunicação cliente-servidorcriptografando mensagens para realizar testes de tempo de criptografia e decriptografia em um sistema de comunicação cliente-servidorcriptografando mensagens para realizar testes de tempo de criptografia e decriptografia em um sistema de comunicação cliente-servidorcriptografando mensagens para realizar testes de tempo de criptografia e decriptografia em um sistema de comunicação cliente-servidor" 10.0.0.9
	sleep 3s
done

	for i in {0..100}
do
	./client $i -f /home/augusto/Documentos/criptografia/Aplicação/Micros/Raspberry_Pi/AES/Imagens/foto.jpg 10.0.0.9
	sleep 3s
done


 
