#include <iostream>
#include "matrix.h"
void printVec(size_t rows, size_t columns, std::vector<double> &values) {
	std::cout << "[";
	for(size_t y = 0; y < rows; ++y){
		if(y>0) 
			std::cout << " ";
		std::cout << "[";

		for(size_t x = 0; x < columns; ++x){
			if(x<columns-1)
				std::cout << values[x + (y * columns)] << ",";
			else
				std::cout << values[x + (y * columns)];
		}
		if(y<rows-1)
			std::cout << "]" << std::endl;
		else
			std::cout << "]";
	}
	std::cout << "]"  << std::endl;
}
void test3(){
	
	auto rows = 2;
	auto columns = 3;
	std::vector<double> A = std::vector<double>(rows*columns);
	A[0] = 3;
	A[1] = 2;
	A[2] = 1;
	A[3] = 1;
	A[4] = 0;
	A[5] = 2;

	Matrix B = Matrix(rows, columns, A);

	A[0] = 1;
	A[1] = 2;
	A[2] = 0;
	A[3] = 1;
	A[4] = 4;
	A[5] = 0;

	Matrix C = Matrix(columns, rows, A);

	std::cout << "B:\n";
	B.print();
	std::cout << "C:\n";
	C.print();
	
	Matrix D = B.mult(C);

	std::cout << "B * C:\n";
	D.print();
}
void test4(){
	std::vector<double> E = std::vector<double>(3*3);
	std::vector<double> F = std::vector<double>(3*2);

	E[0] = 1;
	E[1] = 2;
	E[2] = 3;
	E[3] = 4;
	E[4] = 5;
	E[5] = 6;
	E[6] = 7;
	E[7] = 8;
	E[8] = 9;

	Matrix G = Matrix(3, 3, E);

	F[0] = 1;
	F[1] = 2;
	F[2] = 3;
	F[3] = 4;
	F[4] = 5;
	F[5] = 6;

	Matrix H = Matrix(3, 2, F);

	std::cout << "G:\n";
	G.print();
	std::cout << "H:\n";
	H.print();
	
	Matrix I = G.mult(H);

	std::cout << "G * H:\n";
	I.print();
}

//Test add and get_raw_vector() 
void test2(){
	auto rows = 2;
	auto columns = 5;
	std::vector<double> A = std::vector<double>(10);
	for(double &val: A){
		val = 5;
	}
	Matrix B = Matrix(rows, columns, A);
	for(double &val: A){
		val = 1;
	}
	Matrix C = Matrix(rows, columns, A);

	std::cout << "B:\n";
	B.print();
	std::cout << "C:\n";
	C.print();
	
	Matrix D = B.add(C);

	std::cout << "B:\n";
	B.print();
	std::cout << "C:\n";
	C.print();
	std::cout << "D:\n";
	D.print();

	std::cout << "B,C,D mit get_raw_vector(): " <<std::endl;
	std::cout << "B:\n";
	printVec(rows,columns,B.get_raw_vector());
	std::cout << "C:\n";
	printVec(rows,columns,C.get_raw_vector());
	std::cout << "D:\n";
	printVec(rows,columns,D.get_raw_vector());
}

//Test if copys are made properly with constructor
void test1(){
	auto rows = 2;
	auto columns = 5;
	std::vector<double> A = std::vector<double>(10);
	std::vector<double> *valuespointer = &A;
	
	for(double &val: A){
		val = 5;
	}

	Matrix B = Matrix(rows, columns, A);
	Matrix C = Matrix(rows, columns, valuespointer);
	
	std::cout << "A:\n";
	printVec(rows, columns, A);
	std::cout << "B:\n";
	B.print();
	std::cout << "C:\n";
	C.print();

	std::cout << "A[1] := 10\n";
	A[1]=10;
		
	std::cout << "A:\n";
	printVec(rows, columns, A);
	std::cout << "B:\n";
	B.print();
	std::cout << "C:\n";
	C.print();
}
