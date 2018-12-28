#ifndef MATRIX_H
#define MATRIX_H
#include <vector>
#include <iostream>
class Matrix{
public:
	void print() const;			
	size_t get_rows() const;
	size_t get_columns() const;
	std::vector<double>& get_raw_vector();
	Matrix(size_t rows, size_t columns);
	Matrix(size_t rows, size_t columns, std::vector<double> &initvalues);
	Matrix(size_t rows, size_t columns,std::vector<double> *valuespointer);
	Matrix add(Matrix b) const;
	Matrix mult(Matrix b) const;
private:
	const size_t rows;
	const size_t columns;
	std::vector<double> values;
};
#endif
