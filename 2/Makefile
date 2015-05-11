all:
	g++ -c LN_Class.cpp LongNumber.cpp
	g++ -shared -o LN_Class.dll LN_Class.o LongNumber.o
	g++ main.cpp LN_Class.dll -I. -Wl,-rpath,. -L. -o TCHMK-2.exe
	rm -rf *.o