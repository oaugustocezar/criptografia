gcc Server.c \
    -I/home/pi/Documents/relic/relic-target/include \
    -I/home/pi/Documents/relic/include \
    -L/home/pi/Documents/relic/relic-target/lib \
    -lrelic_s \
    -o server
./server
