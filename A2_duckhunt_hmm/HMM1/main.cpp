#include <iostream>
#include <string> 
#include <vector>
#include <fstream>
#include <sstream>
#include "printVector.hpp"

using namespace std;

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

vector<float> matrixScalarMultiplication(vector<float> A, int scalar){
    vector<float> result;
    float tmp = 0;
    result.push_back(A[0]); // Adds number of rows
    result.push_back(A[1]); // Adds number of cols
    for (int idx = 0; idx < A.size(); idx++) {
        result.push_back(A[idx+2]*scalar);
    }
    return result;
}

vector<float> matrixAddition(vector<float> A, vector<float> B){
    vector<float> result;
    float tmp = 0;
    result.push_back(A[0]); // Adds number of rows
    result.push_back(A[1]); // Adds number of cols
    for (int idx = 0; idx < A.size(); idx++) {
        result.push_back(A[idx+2] + B[idx+2]);
    }
    return result;
}

vector<float> getColumn(vector<float> B, int column){
    vector<float> result;
    float tmp = 0;
    result.push_back(B[0]); // Adds number of rows
    result.push_back(1); // Adds number of cols
    for (int idx = 0; idx < B[0]; idx++) {
        int elm = idx*B[0] + column + 2;
        result.push_back(B[elm]);
    }
    return result;
}

float alpha_pass(vector<float> A, vector<float> B, vector<float> pi, vector<float> seq){
    vector<float> alpha_values;

    int last_state = seq[1];
    int next_state = seq[1];
    float a;
    float b;
    float alpha_sum;
    vector<float> alpha;
    alpha.push_back(pi[2 + last_state + next_state] * B[2 + last_state*B[0] + next_state]);

    /**
     *  TODO: Change to sum over every possible state.. see lecture slide. 
     *        It´s more complex then you want it to be, ie we have to sum over every possible state.
     *        HAR DET SÅ JÄVLA ROLIGT! :D
     */

    for (int state_idx = 1; state_idx < seq[0]; state_idx++) {
        last_state = seq[state_idx];
        next_state = seq[state_idx + 1];
        alpha_sum = 0;
        for (int alpha_idx = 0; alpha_idx < alpha.size(); alpha_idx++ ) {
            int idx = 2 + last_state*A[0] + next_state;
            alpha_sum += alpha[alpha_idx] * A[idx];
        }
        int idx = 2 + last_state*B[0] + next_state;
        cout << alpha_sum  << endl;
        cout << "States: " << last_state << " "<< next_state << endl;
        cout << "B value: " << B[idx] << endl;
        cout << "alpha value: " << alpha_sum * B[idx] << endl;
        
        alpha.push_back(alpha_sum * B[idx]);
    }

    return alpha[alpha.size()-1];
}



int main(){
    string A_string;    
    string B_string;
    string pi_string;
    string sequence_string;

    getline(cin, A_string);     // Transition Matrix
    getline(cin, B_string);     // Emission Matrix
    getline(cin, pi_string);    // Inital State Probability Distribution
    getline(cin, sequence_string);     // Sequence of Emissions
    cout << A_string <<endl;
    cout << B_string <<endl;


    vector<float> A = string2vector(A_string);
    vector<float> B = string2vector(B_string);
    vector<float> pi = string2vector(pi_string);
    vector<float> sequence = string2vector(sequence_string);
    cout<< "A: "<< endl;
    print_float_vector(A);
    cout<< "B: "<< endl;
    print_float_vector(B);
    // cout<< "Column of B: "<< endl;
    // print_float_vector(getColumn(B,0));
    cout<< "sequence: "<< endl;
    print_sequence(sequence);
    
    float prob = alpha_pass(A, B, pi, sequence);
    cout << "prob = " << prob << endl;
    return 0;
}