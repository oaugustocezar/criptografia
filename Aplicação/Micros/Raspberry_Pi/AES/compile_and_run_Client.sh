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

