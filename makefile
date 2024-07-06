all: p2.o myls.o mycp.o mymv.o mygrep.o myps.o
	gcc p2.o myls.o mycp.o mymv.o mygrep.o myps.o -o myshell -lreadline

p2.o: p2.c
	gcc -c p2.c -o p2.o

myls.o: myls.c
	gcc -c myls.c -o myls.o

mycp.o: mycp.c
	gcc -c mycp.c -o mycp.o

mymv.0: mymv.c
	gcc -c mymv.c -o mymv.o

mygrep.o: mygrep.c
	gcc -c mygrep.c -o mygrep.o

myps.o: myps.c
	gcc -c myps.c -o myps.o
