gcc crypto_rasp.c Server.c \
    -I/home/augusto/relic/relic-target/include \
    -I/home/augusto/relic/include \
    -L/home/augusto/relic/relic-target/lib \
    -lrelic_s \
    -o server

 for i in {0..40}
do
 	./server $i /home/augusto/Documentos/criptografia/Aplicação/Micros/Raspberry_Pi/AES/Imagens/pao_na_chapa.jpg 10.0.0.9
 	sleep 1s
done   

for i in {0..40}
do
 	./server $i -f /home/augusto/Documentos/criptografia/Aplicação/Micros/Raspberry_Pi/AES/Imagens/pao_na_chapa.jpg 10.0.0.9
 	sleep 1s
done   
