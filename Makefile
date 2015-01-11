# GCC complier 
CC=g++

# GCC complier options
	# -pedantic		Issue all the warnings demanded by strict ISO C
	# -Wall			Turns on all optional warnings which are desirable for normal code.
	# -O3			turns on all optimizations
	# -g			turns on debugging information	
	
CFLAGS= -g
LIBS= -lsfml-graphics -lsfml-window -lsfml-system

hexMap: hexMap.cpp 
	@$(CC) -o hexMap hexMap.cpp $(CFLAGS) $(CFLAGS) $(LIBS)
	
test: test.cpp 
	@$(CC) -o test test.cpp $(CFLAGS) $(CFLAGS) $(LIBS)


clean:
	@rm -f *.o
