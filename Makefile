all: fse
fse:fse.o
	gcc fse.o -o fse

fse.o: fse.c
	gcc -c fse.c

clean: 
	rm -f *.so *.o