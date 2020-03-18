gcc crypto_rasp.c Server.c \
    -I/home/pi/relic/relic-target/include \
    -I/home/pi/relic/include \
    -L/home/pi/relic/relic-target/lib \
    -lrelic_s \
    -o server

 for i in {0..20}
do
 	./server $i
 	sleep 1s
done   
