run1:
	gcc -o a1 a1.c
	./a1
	rm -rf a1

run2:
	gcc -o a2 a2.c
	./a2
	rm -rf a2

run3:
	gcc -o a3 b1.c
	./a3
	rm -rf a3