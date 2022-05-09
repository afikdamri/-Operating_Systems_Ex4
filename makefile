CC = gcc
FLAGS= 
all: server client

server: server.o
	$(CC) $(FLAGS) -pthread $^ -o server

client: client.o
	$(CC) $(FLAGS) $^ -o client	

%.o: %.c
	$(CC) -c $< -o $@
clean:
	rm *.o server 