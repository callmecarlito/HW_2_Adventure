#compiler: 
CC = gcc 
#compiler flags:
#-g -ansi -Wall - pedantic -std=gnu99 -I
CFLAGS = -g -Wall  

all: sinocruc.buildrooms sinocruc.adventure

sinocruc.buildrooms: sinocruc.buildrooms.c
	$(CC) $(CFLAGS) -o sinocruc.buildrooms.out sinocruc.buildrooms.c 	

sinocruc.adventure: sinocruc.adventure.c
	$(CC) $(CFLAGS) -o sinocruc.adventure.out sinocruc.adventure.c -lpthread

clean:
	$(RM) sinocruc.buildrooms sinocruc.adventure *.o *~