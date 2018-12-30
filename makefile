.PHONY: clean

#Variablen
CXX := g++
CXXFLAGS := -c -g -std=c++11 -Wall

helloworld: src/main.o src/test.o src/matrix.o src/matrixv2.o
	$(CXX) -o helloworld src/matrix.o src/main.o src/test.o src/matrixv2.o

matrix.o: src/matrix.cpp src/matrix.h
	$(CXX) $(CXXFLAGS) src/matrix.cpp 

main.o: src/main.cpp src/test.h 
	$(CXX) $(CXXFLAGS) src/main.cpp

test.o: src/test.cpp src/test.h src/matrix.h src/matrixv2.h
	$(CXX) $(CXXFLAGS) src/test.cpp

matrixv2.o: src/matrixv2.cpp src/matrixv2.h
	$(CXX) $(CXXFLAGS) src/matrixv2.cpp 

clean:
	rm -f src/*.o 
