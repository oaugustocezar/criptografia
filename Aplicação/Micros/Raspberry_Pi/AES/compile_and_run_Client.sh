gcc crypto_rasp.c Client.c \
    -I/home/augusto/relic/relic-target/include \
    -I/home/augusto/relic/include \
    -L/home/augusto/relic/relic-target/lib \
    -lrelic_s \
    -o client 


	for i in {0..40}
do
	./client $i "criptografando mensagens para realizar testes" 127.0.0.1
	sleep 3s
done


	for i in {0..40}
do
	./client $i -f /home/augusto/Documentos/criptografia/Aplicação/Micros/Raspberry_Pi/AES/Imagens/cripto.jpg /home/augusto/Documentos/criptografia/Aplicação/Micros/Raspberry_Pi/AES/Imagens/Confirmação_Client/img$i.jpg 127.0.0.1
	sleep 3s
done


 



 
