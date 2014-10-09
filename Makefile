CC=g++

library.so: cosmology.o
	$(CC) -shared -W1,-soname,library.so -o library.so cosmology.o
	rm -f *.o

cosmology.o: cosmology.cpp
	$(CC) -shared -c -fPIC cosmology.cpp -o cosmology.o