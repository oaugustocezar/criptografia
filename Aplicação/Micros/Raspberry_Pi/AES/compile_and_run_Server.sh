gcc crypto_rasp.c Server.c \
    -I/home/augusto/relic/relic-target/include \
    -I/home/augusto/relic/include \
    -I/home/augusto/openssl/include \
    -L/home/augusto/relic/relic-target/lib \
    -lrelic_s \
    -o server.run

  for i in {0..10}
do
 	./server.run $i /home/augusto/Documentos/criptografia/Aplicação/Micros/Raspberry_Pi/AES/Confirmações/Server/Strings/Confirmaçao$i.txt
 	sleep 1s
done

for i in {0..10}
do
 	./server.run $i -f /home/augusto/Documentos/criptografia/Aplicação/Micros/Raspberry_Pi/AES/Confirmações/Server/Imagens/Confirmaçao$i.jpg
 	sleep 1s
done   
