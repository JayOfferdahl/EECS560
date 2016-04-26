lab: main.o PairingHeap.o
	g++ -g -std=c++11 main.o PairingHeap.o -o lab

main.o: main.cpp
	g++ -g -std=c++11 -c main.cpp

PairingHeap.o: PairingHeap.h PairingHeap.cpp
	g++ -g -std=c++11 -c PairingHeap.cpp

ifdef SystemRoot
    RM = del /Q
    FixPath = $(subst /,\,$1)
else
    ifeq ($(shell uname), Linux)
        RM = rm -f
        FixPath = $1
    endif
endif

clean:
	$(RM) *.o *.exe lab

build:
	make
	lab