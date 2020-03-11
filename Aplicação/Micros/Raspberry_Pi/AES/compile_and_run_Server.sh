gcc crypto_rasp.c Server.c \
    -I/home/augusto/relic/relic-target/include \
    -I/home/augusto/relic/include \
    -L/home/augusto/relic/relic-target/lib \
    -lrelic_s \
    -o server

 for i in {0..10}
do
 	./server $i
 	sleep 1s
done   
