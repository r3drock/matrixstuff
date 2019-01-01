#include <string>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <algorithm>
#include "matrixv2.h"
#include "test.h"
size_t get_file_length(std::ifstream &quelle);
void print_vec(size_t rows, size_t columns, std::vector<std::string> &values) {
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
int main(){
	std::string dateiname = "datasets/iris.csv";

	std::ifstream quelle(dateiname);

	size_t filelength = get_file_length(quelle);

	std::vector<double> sepal_length_vec = std::vector<double>(0);
	std::vector<double> sepal_width_vec  = std::vector<double>(0);
	std::vector<double> petal_length_vec = std::vector<double>(0);
	std::vector<double> petal_width_vec  = std::vector<double>(0);
	std::vector<std::string> species_vec = std::vector<std::string>(0);

	std::vector<std::vector<double>> vecs = std::vector<std::vector<double>>();
	vecs.push_back(sepal_length_vec);
	vecs.push_back(sepal_width_vec );
	vecs.push_back(petal_length_vec);
	vecs.push_back(petal_width_vec );

	if ( vecs.size() != 4){
		std::cout << "vector length: " << vecs.size() << "should be 4!";
		exit(1);
	}


	while(quelle.good()){
		std::string zeile;
		getline(quelle,zeile);
		std::string delimiter = "\t";
		std::string token;
		size_t pos = 0;
		unsigned int t = 0;
		while ((pos = zeile.find(delimiter)) != std::string::npos) {
			token = zeile.substr(0, pos);
			if (token.at(0) == 'I'){
			species_vec.push_back(token);
			} else {
			vecs.at(t).push_back(std::stod(token));
			}
			zeile.erase(0, pos + delimiter.length());
			++t;
		}
	}

	Matrixv2 sepal_length = Matrixv2(filelength,1,&vecs[0]);
	Matrixv2 sepal_width  = Matrixv2(filelength,1,&vecs[1]);
	Matrixv2 petal_length = Matrixv2(filelength,1,&vecs[2]);
	Matrixv2 petal_width  = Matrixv2(filelength,1,&vecs[3]);
	
	std::vector<Matrixv2*> matrices = std::vector<Matrixv2*>(0);
	matrices.push_back(&sepal_length);
	matrices.push_back(&sepal_width);
	matrices.push_back(&petal_length);
	matrices.push_back(&petal_width);

	std::vector<std::string> attribute_names = std::vector<std::string>(4);
	attribute_names[0] = "sepal_length";
	attribute_names[1] = "sepal_width ";
	attribute_names[2] = "petal_length";
	attribute_names[3] = "petal_width ";

	std::vector<double> mean = std::vector<double>(4);
	std::vector<double> variance = std::vector<double>(4);
	std::vector<double> std_dev = std::vector<double>(4);
	

	for( int i = 0; i < 4; ++i){
		mean[i] = matrices[i]->mean();
	}
	for( int i = 0; i < 4; ++i){
		variance[i] = matrices[i]->variance();
	}
	for( int i = 0; i < 4; ++i){
		std_dev[i] = matrices[i]->std_dev();
	}

	std::cout << std::fixed;
	std::cout << std::setprecision(4);
	std::cout << "arithmetic means:\n";
	for( int i = 0; i < 4; ++i){
		std::cout << attribute_names[i] << ": " << mean[i] << " ";
	}
	std::cout << "\nvariances:\n";
	for( int i = 0; i < 4; ++i){
		std::cout << attribute_names[i] << ": " << variance[i] << " ";
	}
	std::cout << "\nstandard deviations:\n";
	for( int i = 0; i < 4; ++i){
		std::cout << attribute_names[i] << ": " << std_dev[i] << " ";
	}
	std::cout << "pearson coefficient:\n[";
	for( int x = 0; x < 4; ++x){
		if(x==0)
			std::cout << "[ ";
		else
			std::cout << " [ ";
		for( int y = 0; y < 4; ++y){
			std::cout << matrices[x]->pearson((*matrices[y]));
			std::cout << "\t";
		}	
		if (x< 3)
			std::cout << "]\n";
	}
	std::cout << "]]\n";
}


size_t get_file_length(std::ifstream &quelle){
	size_t filelength = std::count(std::istreambuf_iterator<char>(quelle), 
             std::istreambuf_iterator<char>(), '\n');
	quelle.seekg(0);
	return filelength;
}
