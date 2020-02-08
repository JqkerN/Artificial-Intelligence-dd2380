# include "printVector.hpp"
using namespace std;

void print_float_vector(vector<float> A)
{   
	int idx = 2;
	for (int r = 0; r < A[0]; r++) {
		for (int c = 0; c < A[1]; c++) {
			cout << A[idx++] << '	';
		}
    	cout << endl;
	}
	cout << " " << endl;
}

void print_sequence(vector<float> A)
{   
	for (int r = 0; r < A[0]; r++) {
		cout << A[r+1] << '	';
	}
	cout << endl;
	cout << " " << endl;
}


