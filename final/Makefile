all:

	gcc -c -fPIC LongNumber.c -o LongNumber.o

	gcc -shared -o libfirst.so LongNumber.o ##first lab



	g++ -c -fPIC LN_Class.cpp -o LN_Class.o
	g++ -shared -L. -lfirst -o libsecond.so LN_Class.o ## second lab


	swig -c++ -python -o LN_Class_wrap.cpp LN_Class.i

	g++ -fPIC -c LN_Class_wrap.cpp -I/usr/include/python2.7 ##third lab
	
	g++ -shared LN_Class.o LongNumber.o LN_Class_wrap.o -o _LN_Class.so
	