all: windows

windows:
	g++ -c LN_Class.cpp LongNumber.c
	g++ -shared -o LN_Class.dll LN_Class.o LongNumber.o
	g++ main.cpp LN_Class.dll -I. -Wl,-rpath,. -L. -o TCHMK-2.exe
	rm -rf *.o

linux:
	g++ -g -c -fPIC LN_Class.cpp -o LN_Class.o -I../first
	g++ -shared -L../first -lLongNumber -o libLN_Class.so LN_Class.o
	g++ -g -c main.cpp -I../first 
	g++  main.o -L. -lLN_Class -L../first -I../first -lLongNumber -o TCHMK-2