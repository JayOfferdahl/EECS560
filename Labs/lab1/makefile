lab: main.o LinkedList.o Node.o
	g++ -g -std=c++11 main.o LinkedList.o Node.o -o lab

main.o: main.cpp LinkedList.h
	g++ -g -std=c++11 -c main.cpp

LinkedList.o: LinkedList.h LinkedList.cpp Node.h
	g++ -g -std=c++11 -c LinkedList.cpp

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
