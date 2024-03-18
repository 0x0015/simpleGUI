all:
	g++ -g simple.cpp -o simple -L../build -lsimpleGUI -Wl,-rpath='$$ORIGIN'
	cp ../build/libsimpleGUI.so .

clean:
	rm -f simple
	rm -f libsimpleGUI.so
