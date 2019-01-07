#include "matrixv2.h"

double Matrixv2::mean(){
	double sum = 0.0;
	for (double val : (*values)){
		sum += val;
	}
	double mean = sum / static_cast<double>(values->size());
	return mean;  
}
double Matrixv2::variance(){
	double variance = 0.0;
	double mean = this->mean();
	for (double val : (*values)){
		variance += pow(val - mean,2.0);
	}	
	return variance * (1.0 / (static_cast<double>(rows*columns) - 1.0));  
}
double Matrixv2::std_dev(){
	return sqrt(this->variance());
}
double Matrixv2::covariance(Matrixv2 &b){
	if (columns != 1 || b.get_columns() != 1){
		std::cerr << "shape passt nicht! Es muss genau eine column sein." 
			<< "\nDiese Matrix columns: " << columns 
			<< "\nMatrix b columns: " << b.get_columns() << std::endl;
		exit(1);
	}
	if (rows != b.get_rows()){
		std::cerr << "Matrix is not the same size as the matrix which is given"
		   	<< "as parameter."
			<< "\nDiese Matrix:\n" 
			<< "rows: " << rows << "columns: " << columns
			<< "\nMatrix b:\n" 
			<< "rows: " << b.get_rows() << "columns: " << b.get_columns() 
			<< std::endl;
		exit(1);
	}
	double mean = this->mean();
	double b_mean = b.mean();

	std::vector<double> &b_values = b.get_raw_vector();

	double covariance = 0.0;
	for( size_t i = 0 ; i < rows ; ++i){
		covariance += ((*values)[i] - mean) * (b_values[i] - b_mean);
	}	
	return covariance * (1.0 / (static_cast<double>(rows) - 1.0));  
}

double Matrixv2::pearson(Matrixv2 &b){

	double sxy = this->covariance(b);
	double sxx = this->variance();
	double syy = b.variance();

	return sxy / sqrt(sxx * syy);
}
void Matrixv2::print() const{
	std::cout << "[";
	for(size_t y = 0; y < rows; ++y){
		if(y>0) 
			std::cout << " ";
		std::cout << "[";

		for(size_t x = 0; x < columns; ++x){
			if(x<columns-1)
				std::cout << (*values)[x + (y * columns)] << ",";
			else
				std::cout << (*values)[x + (y * columns)];
		}
		if(y<rows-1)
			std::cout << "]" << std::endl;
		else
			std::cout << "]";
	}
	std::cout << "]"  << std::endl;
}

size_t Matrixv2::get_rows() const{ return rows;}

size_t Matrixv2::get_columns() const{ return columns;}

std::vector<double>& Matrixv2::get_raw_vector(){
	return (*values);
}


Matrixv2::Matrixv2(size_t rows, size_t columns,std::vector<double> *values_p)
: rows {rows}, columns {columns}{
	size_t elements = rows * columns;
	if ( elements != (*values_p).size()){
		std::cerr << "Matrix is not the same size as rows * columns indicates!" 
			<< "rows: " << rows << "columns: " << columns << "rows * columns: " 
			<< elements << "values size: " << values_p->size()<< std::endl;
		exit(1);
	}
	values = values_p;
}	
Matrixv2::~Matrixv2(){
	values->~vector<double>();
}

Matrix Matrixv2::add(Matrix b) const{
	if(b.get_rows()!= rows || b.get_columns() != columns){
		std::cerr << "Matrix is not the same size!";
		exit(1);
	}	
	std::vector<double> resultvector = std::vector<double>(rows*columns);
	for( size_t i = 0; i < values->size(); ++i){
		resultvector[i] = (*values)[i] + b.get_raw_vector()[i]; 
	}
	
	//inefficient because matrix gets copied
	return Matrix(rows,columns,resultvector);
}

Matrix Matrixv2::add(Matrixv2 b) const{
	if(b.get_rows()!= rows || b.get_columns() != columns){
		std::cerr << "Matrix is not the same size!";
		exit(1);
	}	
	std::vector<double> resultvector = std::vector<double>(rows*columns);
	for( size_t i = 0; i < values->size(); ++i){
		resultvector[i] = (*values)[i] + b.get_raw_vector()[i]; 
	}
	
	//inefficient because matrix gets copied
	return Matrix(rows,columns,resultvector);
}
void Matrixv2::addinplace(Matrix b) const{
	if(b.get_rows()!= rows || b.get_columns() != columns){
		std::cerr << "Matrix is not the same size!";
		exit(1);
	}	
	for( size_t i = 0; i < values->size(); ++i){
		(*values)[i] = (*values)[i] + b.get_raw_vector()[i]; 
	}
}
void Matrixv2::addinplace(Matrixv2 b) const{
	if(b.get_rows()!= rows || b.get_columns() != columns){
		std::cerr << "Matrix is not the same size!";
		exit(1);
	}	
	for( size_t i = 0; i < values->size(); ++i){
		(*values)[i] = (*values)[i] + b.get_raw_vector()[i]; 
	}
}

Matrix Matrixv2::mult(Matrix b) const{
	if( columns != b.get_rows()){
		std::cerr << "Matrices have wrong shapes!\n" << "This Matrix:\n" 
		<< "rows: " << rows << "columns: " << columns 
		<< "Matrix given as parameter:\n"  
		<< "rows: " << b.get_rows() << "columns: " << b.get_columns() 
		<< std::endl;
		exit(1);
	}

	std::vector<double> &B = b.get_raw_vector();	

	const std::vector<double> &A = (*values);

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
Matrix Matrixv2::mult(Matrixv2 b) const{
	if( columns != b.get_rows()){
		std::cerr << "Matrices have wrong shapes!\n" << "This Matrix:\n" 
		<< "rows: " << rows << "columns: " << columns 
		<< "Matrix given as parameter:\n"  
		<< "rows: " << b.get_rows() << "columns: " << b.get_columns() 
		<< std::endl;
		exit(1);
	}

	std::vector<double> &B = b.get_raw_vector();	

	const std::vector<double> &A = (*values);

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

Matrixv2 Matrixv2::mult(Matrixv2 b, std::vector<double> *resultmatrixpointer) const{
	if( columns != b.get_rows()){
		std::cerr << "Matrices have wrong shapes!\n" << "This Matrix:\n" 
		<< "rows: " << rows << "columns: " << columns 
		<< "Matrix given as parameter:\n"  
		<< "rows: " << b.get_rows() << "columns: " << b.get_columns() 
		<< std::endl;
		exit(1);
	}

	std::vector<double> &B = b.get_raw_vector();	

	const std::vector<double> &A = (*values);

	size_t new_rows = rows;
	size_t new_columns = b.get_columns();
	size_t new_size = new_rows * new_columns;

	if ( resultmatrixpointer->size() != new_size){
		std::cerr << "resultmatrix has wrong shapes!\n" << "This Matrix:\n" 
		<< "size needed: " << new_size <<std::endl 
		<< "resultmatrix size: " << resultmatrixpointer->size()
		<< std::endl;
		exit(1);
	}
	
	std::vector<double> resultvector = (*resultmatrixpointer);

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

	return Matrixv2(new_rows, new_columns, resultmatrixpointer);
}

size_t Matrixv2::get_mult_result_matrix_size(Matrixv2 &b){
	size_t new_rows = rows;
	size_t new_columns = b.get_columns();
	size_t new_size = new_rows * new_columns;
	return new_size;	
}
size_t Matrixv2::get_mult_result_matrix_size(Matrix &b){
	size_t new_rows = rows;
	size_t new_columns = b.get_columns();
	size_t new_size = new_rows * new_columns;
	return new_size;	
}
