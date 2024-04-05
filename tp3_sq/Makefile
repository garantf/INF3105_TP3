# Makefile pour INF3105 / TP3

#OPTIONS = -Wall           # option standard
#OPTIONS = -g -O0 -Wall    # pour rouler dans gdb
OPTIONS = -O2 -Wall        # pour optimiser

#
all : tp3

tp3 : tp3.cpp carte.h carte.o 
	g++ ${OPTIONS} -o tp3 tp3.cpp carte.o

carte.o : carte.cpp carte.h 
	g++ ${OPTIONS} -c -o carte.o carte.cpp

clean:
	rm -rf tp3 *~ *.o

