runfifo: fifo compilefifo cleanfifo

runshm: compileshm 

compilefifo:
	gcc -o p1 FifoP1.c
	gcc -o p2 FifoP2.c
	./p1 & ./p2
	
cleanfifo:
	rm -rf p1 p2 sender reciever

fifo:
	mkfifo sender
	mkfifo reciever

compileshm:
	touch a.txt
	touch b.txt
	gcc -o p1 ShmP1.c
	gcc -o p2 ShmP2.c
	gcc -o semcreater semcreater.c
	./semcreater
	./p1 & ./p2

cleanshm:
	gcc -o semdeleter semdeleter.c
	./semdeleter
	rm -rf p1 p2 a.txt b.txt semcreater semdeleter
