all : receive sender
.PHONY : clean

sender : sender.o
	cc -pthread -o sender sender.o
receive : receive.o
	cc -pthread -o receive receive.o
clean :
	rm sender
	rm receive
	rm *.o