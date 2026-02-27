flags=-O2 -Wall -std=c2x
ldflags=-larcfour

.PHONY:all clean
all: clean  fse fsd

fse:fse.o 
	gcc fse.o -o fse

fsd:fsd.o
	gcc $(flags) $^ -o  $@ $(ldflags)

fsd.o: fsd.c fsd.h
	gcc $(flags) -c $^

fse.o: fse.c fse.h
	gcc -c fse.c $<

clean: 
	rm -f *.so *.o fse fsd