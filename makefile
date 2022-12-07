INCS:=`root-config --cflags`
LIBS:=`root-config --libs`

main: main.cpp Integral.o RandomGen.o Funzioni.o AlgoZeri.o  VectorOperations.h EquazioniDifferenziali.h
	g++ main.cpp Integral.o RandomGen.o Funzioni.o AlgoZeri.o  $(INCS) $(LIBS) -o main

Integral.o: Integral.cpp Integral.h Funzioni.o RandomGen.h
	g++ -c Integral.cpp $(INCS) -o Integral.o

RandomGen.o: RandomGen.cpp RandomGen.h
	g++ -c RandomGen.cpp -o RandomGen.o 

AlgoZeri.o: AlgoZeri.cpp AlgoZeri.h Funzioni.o
	g++ -c AlgoZeri.cpp -o AlgoZeri.o

Funzioni.o: Funzioni.h Funzioni.cpp
	g++ -c Funzioni.cpp -o Funzioni.o

clean:
	rm *.o