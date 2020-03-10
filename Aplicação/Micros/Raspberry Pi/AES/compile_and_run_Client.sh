gcc crypto_rasp.c Client.c \
    -I/home/augusto/relic/relic-target/include \
    -I/home/augusto/relic/include \
    -L/home/augusto/relic/relic-target/lib \
    -lrelic_s \
    -o client 
./client -f /home/augusto/Documentos/criptografia/Aplicação/Micros/Raspberry Pi/AES
