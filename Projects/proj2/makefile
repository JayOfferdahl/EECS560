all: proj2
	dos2unix *.txt -o

proj2: proj2_main.o proj2_HashTable.o proj2_Customer.o
	g++ -g -std=c++11 proj2_main.o proj2_HashTable.o proj2_Customer.o -o proj2

proj2_main.o: proj2_main.cpp
	g++ -g -std=c++11 -c proj2_main.cpp

proj2_HashTable.o: proj2_HashTable.h proj2_HashTable.cpp
	g++ -g -std=c++11 -c proj2_HashTable.cpp

proj2_Customer.o: proj2_Customer.h proj2_Customer.cpp
	g++ -g -std=c++11 -c proj2_Customer.cpp

test: all
	./proj2 proj2data.txt

output: all
	./proj2 proj2data.txt > proj2output.txt

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
	$(RM) *.o *.exe proj2