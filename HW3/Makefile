#source: https://www.youtube.com/watch?v=_r7i5X0rXJk&t=218s
all: team clean

team: teamInfo.o teamInfo_LinkedList.o
	gcc -g -Wall teamInfo.o teamInfo_LinkedList.o -o team

teamInfo.o: teamInfo.c teamInfo.h
	gcc -c -g -Wall teamInfo.c	

teamInfo_LinkedList.o: teamInfo_LinkedList.c teamInfo_LinkedList.h
	gcc -c -g -Wall teamInfo_LinkedList.c

clean:
	rm *o team