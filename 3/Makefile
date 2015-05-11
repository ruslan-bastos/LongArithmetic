all:
	swig -c++ -python LN_Class.i
	g++ -c LN_Class.cpp
	g++ -c LongNumber.cpp
	g++ -c LN_Class_wrap.cxx -IC:\dev64\Python27\include
	g++ LN_Class.o LongNumber.o LN_Class_wrap.o -Ic:\dev64\python27\include -Lc:\dev64\python27\libs -lpython27 -shared -o _LN_Class.pyd
	rm -rf *.o *.cxx