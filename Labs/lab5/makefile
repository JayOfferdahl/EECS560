lab: main.o Node.o Queue.o AVLTree.o
	g++ -g -std=c++11 main.o Node.o Queue.o AVLTree.o -o lab

main.o: main.cpp
	g++ -g -std=c++11 -c main.cpp

Node.o: Node.h Node.cpp
	g++ -g -std=c++11 -c Node.cpp

Queue.o: Queue.h Queue.cpp
	g++ -g -std=c++11 -c Queue.cpp

AVLTree.o: AVLTree.h AVLTree.cpp
	g++ -g -std=c++11 -c AVLTree.cpp

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