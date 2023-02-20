CFLAGS="--std=c++14"
all: main tests

expr:
	$(CC) $(CFLAGS) -c -o expr.o expr.cpp

main: expr
	$(CC) $(CFLAGS) -o expr main.cpp expr.o
	 
tests: expr
	$(CC) $(CFLAGS) -o tests testcases.cpp expr.o

clean:
	rm *.o expr tests
