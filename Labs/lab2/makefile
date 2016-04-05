lab: main.o BinarySearchTree.o Queue.o Node.o
	g++ -g -std=c++11 main.o BinarySearchTree.o Queue.o Node.o -o lab

main.o: main.cpp
	g++ -g -std=c++11 -c main.cpp

BinarySearchTree.o: BinarySearchTree.h BinarySearchTree.cpp
	g++ -g -std=c++11 -c BinarySearchTree.cpp

Queue.o: Queue.h Queue.cpp
	g++ -g -std=c++11 -c Queue.cpp

Node.o: Node.h Node.cpp
	g++ -g -std=c++11 -c Node.cpp

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