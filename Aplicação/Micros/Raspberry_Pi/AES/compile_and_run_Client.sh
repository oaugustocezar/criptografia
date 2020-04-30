gcc crypto_rasp.c Client.c \
    -I/home/augusto/relic/relic-target/include \
    -I/home/augusto/relic/include \
    -L/home/augusto/relic/relic-target/lib \
    -lrelic_s \
    -o client.run 


	for i in {0..50}
do
	./client.run $i "criptografando mensagens para realizar testes de tempo de criptografia e decriptografia em um sistema de comunicação cliente-servidorcriptografando mensagens para realizar testes de tempo de criptografia e decriptografia em um sistema de comunicação cliente-servidorcriptografando mensagens para realizar testes de tempo de criptografia e decriptografia em um sistema de comunicação cliente-servidorcriptografando mensagens para realizar testes de tempo de criptografia e decriptografia em um sistema de comunicação cliente-servidorcriptografando mensagens para realizar testes de tempo de criptografia e decriptografia em um sistema de comunicação cliente-servidorcriptografando mensagens para realizar testes de tempo de criptografia e decriptografia em um sistema de comunicação cliente-servidorcriptografando mensagens para realizar testes de tempo de criptografia e decriptografia em um sistema de comunicação cliente-servidorcriptografando mensagens para realizar testes de tempo de criptografia e decriptografia em um sistema de comunicação cliente-servidorcriptografando mensagens para realizar testes de tempo de criptografia e decriptografia em um sistema de comunicação cliente-servidor" 127.0.0.1
	sleep 3s
done
	for i in {0..50}
do
	./client.run $i -f /home/augusto/Documentos/criptografia/Aplicação/Micros/Raspberry_Pi/AES/Imagens/foto.jpg 127.0.0.1
	sleep 3s
done


 
