#ifndef MATRIXV2_H
#define MATRIXV2_H
#include <vector>
#include <cmath>
#include <iostream>
#include "matrix.h"
class Matrixv2{
public:
	void print() const;			
	size_t get_rows() const;
	size_t get_columns() const;
	std::vector<double>& get_raw_vector();
	Matrixv2(size_t rows, size_t columns,std::vector<double> *valuespointer);
	Matrix add(Matrixv2 b) const;
	Matrix add(Matrix b) const;
	void addinplace(Matrix b) const;
	void addinplace(Matrixv2 b) const;
	Matrix mult(Matrix b) const;
	Matrix mult(Matrixv2 b) const;
	Matrixv2 mult(Matrixv2 b, std::vector<double> *resultmatrixpointer) const;

	double mean();
	double variance();
	double std_dev();
	double covariance(Matrixv2 &b);
	double pearson(Matrixv2 &b);

	size_t get_mult_result_matrix_size(Matrixv2 &b);
	size_t get_mult_result_matrix_size(Matrix &b);
private:
	const size_t rows;
	const size_t columns;
	std::vector<double> *values;
};
#endif
