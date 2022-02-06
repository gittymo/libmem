release: libmem.o
	ar rcs libmem.a libmem.o

debug: libmemd.o
	ar rcs libmemd.a libmemd.o

libmem.o: libmem.c libmem.h
	gcc -c libmem.c

libmemd.o: libmem.c libmem.h
	gcc -g -Wall -c -o libmemd.o libmem.c

test: release testlibmem.c
	gcc -O3 -o testlibmem testlibmem.c -I./ -L./ -lmem

testdebug: debug testlibmem.c
	gcc -o testlibmemd testlibmem.c -I./ -L./ -lmemd

clean:
	rm -f *.a *.o testlibmem testlibmemd