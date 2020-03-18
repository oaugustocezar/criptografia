gcc crypto_rasp.c Client.c \
    -I/home/pi/relic/relic-target/include \
    -I/home/pi/relic/include \
    -L/home/pi/relic/relic-target/lib \
    -lrelic_s \
    -o client


: '	for i in {0..20}
do
	./client $i "criptografando mensagens para realizar testes de tempo de criptografia e decriptografia em um sistema de comunicação cliente-servidor" 10.0.0.9 
	sleep 3s
done'

	for i in {0..20}
do
	./client $i -f /home/pi/Documents/criptografia/Aplicação/Micros/Raspberry_Pi/AES/Imagens/pao_na_chapa.jpg 10.0.0.9 
	sleep 3s
done


 
