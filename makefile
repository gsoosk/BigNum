all: BigNum

BigNum: main.o bignum.o
	g++ main.o bignum.o
main.o: main.cpp bignum.h bignum.cpp
	g++ -c main.cpp
bignum.o: bignum.h bignum.cpp
	g++ -c bignum.cpp
clean:
		rm *.o 