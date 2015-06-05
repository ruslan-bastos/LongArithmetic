all: windows

windows:
	swig -c++ -python LN_Class.i
	g++ -c LN_Class.cpp
	g++ -c LongNumber.c
	g++ -c LN_Class_wrap.cxx -IC:\dev64\Python27\include
	g++ LN_Class.o LongNumber.o LN_Class_wrap.o -Ic:\dev64\python27\include -Lc:\dev64\python27\libs -lpython27 -shared -o _LN_Class.pyd
	rm -rf *.o *.cxx

linux:
	swig -c++ -python -o LN_Class_wrap.cpp LN_Class.i
	g++ -c -fPIC LN_Class.cpp -o LN_Class.o
	g++ -c -fPIC LongNumber.c -o LongNumber.o
	g++ -fPIC -c LN_Class_wrap.cpp -I/usr/include/python2.7
	g++ -shared LN_Class.o LongNumber.o LN_Class_wrap.o -o _LN_Class.so