crypto: rsa.o rsa.h hash.o hash.h main.o
	gcc -o crypto -lssl -lcrypto rsa.o hash.o main.o

main.o: rsa.h rsa.o hash.h hash.o main.c
	gcc -c main.c

rsa.o: rsa.h rsa.c
	gcc -c rsa.c

hash.o: hash.h hash.c
	gcc -c hash.c

run:
	./crypto

clean:
	rm -f crypto main.o rsa.o hash.o
