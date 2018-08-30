.PHONY:clean
all:server client1 client2
server:http.c listensock.c
	gcc -o $@ $^ -lpthread
client1:client1.c
	gcc -o $@ $^
client2:client2.c
	gcc -o $@ $^
clean:
	rm server client1 client2
