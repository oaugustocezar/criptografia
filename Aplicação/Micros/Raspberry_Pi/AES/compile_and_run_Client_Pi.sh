gcc crypto_rasp.c Client.c \
    -I/home/pi/relic/relic-target/include \
    -I/home/pi/relic/include \
    -L/home/pi/relic/relic-target/lib \
    -lrelic_s \
    -o client


	for i in {0..40}
do
	./client $i "criptografando mensagens para realizar testes" 127.0.0.1 
	sleep 3s
done

gcc crypto_rasp.c Client.c \
    -I/home/pi/relic/relic-target/include \
    -I/home/pi/relic/include \
    -L/home/pi/relic/relic-target/lib \
    -lrelic_s \
    -o client

	for i in {0..40}
do
	./client $i -f /home/pi/Documents/criptografia/Aplicação/Micros/Raspberry_Pi/AES/Imagens/cripto.jpg /home/pi/Documents/criptografia/Aplicação/Micros/Raspberry_Pi/AES/Imagens/Confirmação_Client/img$i.jpg 127.0.0.1 
	sleep 3s
done


 
