all: OutProgram

OutProgram: main.o singleton_static.a singleton_dynamic.so
	g++ -lm -o OutProgram main.o -L. -lsingleton_static -L. -lsingleton_dynamic

main.o: main.cpp
	g++ -std=c++17 -c -g -Wall -pedantic -Werror -o main.o main.cpp
#static library
singleton.o: singleton.cpp singleton.h
	g++ -c -Wall -pedantic -Werror singleton.cpp

calls1.o: calls1.cpp calls1.h
	g++ -c -Wall -pedantic -Werror calls1.cpp

singleton_static.a: singleton.o calls1.o
	ar rcs libsingleton_static.a singleton.o calls1.o

libs: singleton_static.a
#dynamic library
singleton.o: singleton.cpp singleton.h
	g++ -fPIC -c -Wall -pedantic -Werror singleton.cpp

singleton_dynamic.o: singleton_dynamic.cpp singleton_dynamic.h
	g++ -fPIC -c -Wall -pedantic -Werror singleton_dynamic.cpp

singleton_dynamic.so: singleton.o singleton_dynamic.o
	g++ -shared -o libsingleton_dynamic.so singleton.o singleton_dynamic.o
#to work properly we have to add path to library for example:
#LD_LIBRARY_PATH=/home/username/foo:$LD_LIBRARY_PATH
#export LD_LIBRARY_PATH=/home/username/foo:$LD_LIBRARY_PATH
clean:
	rm -f OutProgram *.o *.a *.gch