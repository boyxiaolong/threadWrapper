main:main.o threadWrapper.o
	g++ -o main main.o threadWrapper.o 
main.o:main.cpp threadWrapper.h Buffer.h
	g++ -c main.cpp -std=c++11 -pthread
threadWrapper.o:threadWrapper.cpp Buffer.h
	g++ -c threadWrapper.cpp -std=c++11 -pthread
