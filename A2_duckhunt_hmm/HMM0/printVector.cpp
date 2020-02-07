# include "printVector.hpp"
using namespace std;

void print_float_vector(vector<float> A)
{   
	for (int r = 0; r < A[0]; r++) {
		for (int c = 0; c < A[1]; c++) {
			cout << A[r+c+2] << '	';
		}
    	cout << endl;
	}
	cout << " " << endl;
}

