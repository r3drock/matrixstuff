.PHONY: clean

#Variablen
CXX := g++
CXXFLAGS := -c -g -Wall 

helloworld: src/main.o src/test.o src/matrix.o 
	$(CXX) -o helloworld src/matrix.o src/main.o src/test.o

matrix.o: src/matrix.cpp src/matrix.h
	$(CXX) $(CXXFLAGS) src/matrix.cpp 

main.o: src/main.cpp src/test.h 
	$(CXX) $(CXXFLAGS) src/main.cpp

test.o: src/test.cpp src/test.h src/matrix.h
	$(CXX) $(CXXFLAGS) src/test.cpp

clean:
	rm -f src/*.o 
