lab: main.o MinHeap.o MinMaxHeap.o
	g++ -g -std=c++11 main.o MinHeap.o MinMaxHeap.o -o lab

main.o: main.cpp
	g++ -g -std=c++11 -c main.cpp

MinHeap.o: MinHeap.h MinHeap.cpp
	g++ -g -std=c++11 -c MinHeap.cpp

MinMaxHeap.o: MinMaxHeap.h MinMaxHeap.cpp
	g++ -g -std=c++11 -c MinMaxHeap.cpp

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