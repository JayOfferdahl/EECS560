lab: main.o Timer.o
	g++ -g -std=c++11 main.o Timer.o -o lab

main.o: main.cpp
	g++ -g -std=c++11 -c main.cpp

Timer.o: Timer.cpp
	g++ -g -std=c++11 -c Timer.cpp

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