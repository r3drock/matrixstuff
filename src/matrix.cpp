#include "matrix.h"
	
void Matrix::print() const{
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

size_t Matrix::get_rows() const{ return rows;}

size_t Matrix::get_columns() const{ return columns;}

std::vector<double>& Matrix::get_raw_vector(){
	return values;
}

Matrix::Matrix(size_t rows, size_t columns)
: rows {rows}, columns {columns}{
	values = std::vector<double>(rows*columns);
}

//inefficient because matrix gets copied
Matrix::Matrix(size_t rows, size_t columns, std::vector<double> &initvalues)
: rows {rows}, columns {columns}{
	size_t elements = rows * columns;
	if ( elements != initvalues.size()){
		std::cerr << "Matrix is not the same size as rows * columns indicates!" 
			<< "rows: " << rows << "columns: " << columns << "rows * columns: " 
			<< elements << "initvalues size: " << initvalues.size()<< std::endl;
		exit(1);
	}
	values = initvalues; 
}	
hallo

//inefficient because matrix gets copied
Matrix::Matrix(size_t rows, size_t columns,std::vector<double> *valuespointer)
: rows {rows}, columns {columns}{
	size_t elements = rows * columns;
	if ( elements != (*valuespointer).size()){
		std::cerr << "Matrix is not the same size as rows * columns indicates!" 
			<< "rows: " << rows << "columns: " << columns << "rows * columns: " 
			<< elements << "values size: " << (*valuespointer).size()<< std::endl;
		exit(1);
	}
	values = (*valuespointer);
}	

Matrix Matrix::add(Matrix b) const{
	if(b.get_rows()!= rows || b.get_columns() != columns){
		std::cerr << "Matrix is not the same size!";
		exit(1);
	}	
	std::vector<double> resultvector = std::vector<double>(rows*columns);
	for( size_t i = 0; i < values.size(); ++i){
		resultvector[i] = values[i] + b.get_raw_vector()[i]; 
	}
	
	//inefficient because matrix gets copied
	return Matrix(rows,columns,resultvector);
}

Matrix Matrix::mult(Matrix b) const{
	if( columns != b.get_rows()){
		std::cerr << "Matrices have wrong shapes!\n" << "This Matrix:\n" 
		<< "rows: " << rows << "columns: " << columns 
		<< "Matrix given as parameter:\n"  
		<< "rows: " << b.get_rows() << "columns: " << b.get_columns() 
		<< std::endl;
		exit(1);
	}

	std::vector<double> &B = b.get_raw_vector();	

	const std::vector<double> &A = values;

	size_t new_rows = rows;
	size_t new_columns = b.get_columns();
	
	std::vector<double> resultvector =std::vector<double>(new_rows*new_columns);

	for(size_t y = 0; y < new_rows; ++y){
		for(size_t x = 0; x < new_columns; ++x){
			double smallresult = 0.0;
			for(size_t i = 0; i < columns; ++i){
				smallresult += A[i + (y * columns)] *
							   B[x + (i * b.get_columns())]; 
			}
			resultvector[x + (y * new_columns)] = smallresult;
		}
	}
	return Matrix(new_rows, new_columns, resultvector);
}
