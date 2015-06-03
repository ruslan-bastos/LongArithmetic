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
	gcc -c -fPIC LN_Class_wrap.cpp -o LN_Class_wrap.o -I/usr/include/python2.7 -I../first -I ../second
	g++ -fPIC -shared LN_Class_wrap.o -I../first -I../second -L../first -L../second -lLN_Class -lLongNumber -o _LN_Class.so