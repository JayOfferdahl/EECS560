proj1: proj1_main.o proj1_Fraction.o proj1_Node.o proj1_LinkedList.o
	g++ -g -std=c++11 proj1_main.o proj1_Fraction.o proj1_Node.o proj1_LinkedList.o -o proj1

proj1_main.o: proj1_main.cpp
	g++ -g -std=c++11 -c proj1_main.cpp

proj1_Fraction.o: proj1_Fraction.h proj1_Fraction.cpp
	g++ -g -std=c++11 -c proj1_Fraction.cpp

proj1_Node.o: proj1_Node.h proj1_Node.cpp
	g++ -g -std=c++11 -c proj1_Node.cpp

proj1_LinkedList.o: proj1_LinkedList.h proj1_LinkedList.cpp
	g++ -g -std=c++11 -c proj1_LinkedList.cpp

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
	$(RM) *.o *.exe proj1