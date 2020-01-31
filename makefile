#compiler: 
CC = gcc 
#compiler flags:
#-g -ansi -Wall - pedantic -std=gnu99 -I
CFLAGS = -g -Wall  

all: sinocruc.buildrooms sinocruc.adventure

sinocruc.buildrooms: sinocruc.buildrooms.c
	$(CC) $(CFLAGS) -o sinocruc.buildrooms sinocruc.buildrooms.c 	

#sinocruc.adventure: sinocruc.adventure.c
#	$(CC) $(CFLAGS) -o sinocruc.adventure sinocruc.adventure.c

clean:
	$(RM) sinocruc.buildrooms sinocruc.adventure *.o *~