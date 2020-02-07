#include <iostream>
#include <string> 
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;


vector<float> matrixMultiplication(vector<float> A, vector<float> B){
    if (A[1] != B[0]) {
        fprintf(stderr, "ERROR: Matrix missmatch, Matrix1[%.0f x %.0f] x Matrix2[%.0f x %.0f].\n", A[0],A[1],B[0],B[1]);
        exit(1);
    }
    vector<float> result;
    float tmp = 0;
    result.push_back(A[0]); // Adds number of rows
    result.push_back(B[1]); // Adds number of cols
    for (int A_rows = 0; A_rows < A[0]; A_rows++) {
        for (int B_cols = 0; B_cols < B[1]; B_cols++) {
            for (int idx = 0; idx < A[1]; idx++) {
                int A_idx = 2 + idx + A_rows * A[0];
                int B_idx = 2 + B_cols + idx * B[1];
                tmp += A[A_idx] * B[B_idx];
            }
            result.push_back(tmp);
            tmp = 0;   
        }
    }
    return result;
}

vector<float> string2vector(string list_string){
    vector<float> value;
    istringstream iss(list_string);
    string value_string;
    while(iss >> value_string) {
        value.push_back(stof(value_string));
    }
    return value;
}

string vector2string(vector<float> vector_float){
    string value;
    for (int idx = 0; idx < vector_float.size(); idx++){
        value += to_string(vector_float[idx]) +  " ";
    }
    return value;
}


int main(){
    string A_string;
    string B_string;
    string pi_string;

    getline(cin, A_string);
    getline(cin, B_string);
    getline(cin, pi_string);

    vector<float> A = string2vector(A_string);
    vector<float> B = string2vector(B_string);
    vector<float> pi = string2vector(pi_string);
    vector<float> pi_times_A = matrixMultiplication(pi, A);
    vector<float> new_state = matrixMultiplication(pi_times_A, B);
    string output = vector2string(new_state);
    cout << output << endl;
    return 0;
}