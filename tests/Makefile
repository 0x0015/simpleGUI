all:
	g++ -g -std=c++20 simple.cpp -o simple -L../build -lsimpleGUI -Wl,-rpath='$$ORIGIN'
	g++ -g -std=c++20 elementInsertion.cpp -o elementInsertion -L../build -lsimpleGUI -Wl,-rpath='$$ORIGIN'
	gcc -g simple_c.c -o simple_c -L../build -lsimpleGUI -Wl,-rpath='$$ORIGIN'
	cp ../build/libsimpleGUI.so .

clean:
	rm -f simple
	rm -f elementInsertion
	rm -f simple_c
	rm -f libsimpleGUI.so
