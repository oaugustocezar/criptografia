gcc crypto_rasp.c Server.c \
    -I/home/augusto/relic/relic-target/include \
    -I/home/augusto/relic/include \
    -L/home/augusto/relic/relic-target/lib \
    -lrelic_s \
    -o server
./server
