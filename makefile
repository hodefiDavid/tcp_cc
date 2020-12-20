CC = gcc
COMP_FLAG = -Wall 


all: mains mainc

mains: measure.c 
	$(CC)  $(COMP_FLAG)   -o mains measure.c
	
mainc: sender.c 
	$(CC)  $(COMP_FLAG)   -o mainc sender.c	

measure.o: measure.c 
	$(CC) $(COMP_FLAG) -c $*.c

sender.o: sender.c 
	$(CC) $(COMP_FLAG) -c $*.c
	
.PHONY: clean all  

clean:
	rm -f *.a *.so *.o mains mainc
		
	


