#include <iostream>
#include <string> 
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class matrix{
    public:
    string name;
    string input;
    int rows;
    int cols;
    vector<float> vec;
    vector<vector<float>> mat;

    void string2vector();
    void getMatrix();
    void printMatrix();
    void initilizeMatrix(bool verbose, bool empty);
    void printSequence();
    void emptyMatrix();
};

void matrix::initilizeMatrix(bool verbose = false, bool empty = false){
    if (name.empty() || (input.empty() && empty == false) ){
        fprintf(stderr, "Fill in name and input properly. name empty: %i input: %i", name.empty(), input.empty());
        exit(1);
    }
    if (empty == true){
        emptyMatrix();
        if (verbose){
            printMatrix();
        }
    }else{
        string2vector();
        getMatrix();
        if (verbose){
            printMatrix();
        }
    }

}

void matrix::string2vector(){
    istringstream iss(input);
    string tmp;
    while(iss >> tmp) {
        vec.push_back(stof(tmp));
    }
}

void matrix::getMatrix(){
    rows = vec[0];
    cols = vec[1];
    for (int r = 0; r < vec[0]; r++) {
        vector<float> tmp;
        for (int c = 0; c < vec[1]; c++) {
            int idx = 2 + c + r * vec[0];
            tmp.push_back( vec[idx]);
        }
        mat.push_back(tmp);  
    }
}

void matrix::emptyMatrix(){
    if (cols == 0 || rows == 0){
        fprintf(stderr, "Fill in rows and cols properly. name rows: %i cols: %i", rows, cols);
        exit(1);
    }
    for (int r = 0; r < rows; r++) {
        vector<float> tmp;
        for (int c = 0; c < cols; c++) {
            tmp.push_back(0.0);
        }
        mat.push_back(tmp);  
    }
}

void matrix::printMatrix() {
    cout << "size of " << name <<": (" << rows << "," << cols << ")"<<endl;;
    for (int r = 0; r < mat.size(); r++){
        for (int c = 0; c < mat[0].size(); c++){
            cout << mat[r][c] << '	';
        }
        cout << endl;
    }
}

class sequence{
    public:
    string name;
    string input;
    int observations;
    vector<float> vec;

    void string2vector();
    void printSequence();
    void initilizeSequence(bool verbose);
};

void sequence::initilizeSequence(bool verbose = false){
    if (name.empty() || input.empty()){
        fprintf(stderr, "Fill in name and input properly. name empty: %i input: %i", name.empty(), input.empty());
    }
    string2vector();
    if (verbose){
        printSequence();
    }
    

}

void sequence::string2vector(){
    istringstream iss(input);
    string tmp;
    string tmp_2;
    iss >> tmp_2;
    observations = stoi(tmp_2);
    while(iss >> tmp) {
        vec.push_back(stof(tmp));
    }
}

void sequence::printSequence() {
    cout << "size of " << name <<": (" << observations << ")" <<endl;;
    for (int idx = 0; idx < observations; idx++){
        cout << vec[idx] << '	';
    }
    cout << endl;
}

double FORWARD(matrix A, matrix B, matrix pi, sequence O, int N, int T){

    matrix forward;
    double forwardprob = 0;
    forward.name = "Forward Matrix";
    forward.rows = N;
    forward.cols = T;
    forward.initilizeMatrix(false, true);

    // Initialization step
    for (int s = 0; s < N; s++) {
        forward.mat[s][0] = ( pi.mat[0][s] * B.mat[s][O.vec[0]]);
    }

    // Recursion step
    for (int t = 0; t < T-1; t++) {
        for (int s = 0; s < N; s++) {
            float tmp = 0;
            for (int sp = 0; sp < N; sp++) {
                tmp +=  forward.mat[sp][t] * A.mat[sp][s]; 
            }
            forward.mat[s][t+1] = tmp * B.mat[s][O.vec[t+1]]; 
        }   
    }
    // forward.printMatrix();
    // Termination step
    for (int s = 0; s < N; s++) {
                forwardprob +=  forward.mat[s][T-1]; 
            }
    return forwardprob;
}

int main(){
    matrix A;   // Transition Matrix 
    matrix B;   // Emission Matrix
    matrix pi;  // Inital State Probability Distribution
    sequence O;   // Sequence of Emissions

    A.name = "Transition Matrix (A)";
    B.name = "Emission Matrix (B)";
    pi.name = "Inital State Probability Distribution (pi)";
    O.name = "Sequence of Emissions (O)";

    // Read input from terminal
    getline(cin, A.input); 
    getline(cin, B.input);
    getline(cin, pi.input);
    getline(cin, O.input);

    // Initilize matrixes and sequence with all attributes (OBS: can be done manuely)
    A.initilizeMatrix(false);
    B.initilizeMatrix(false);
    pi.initilizeMatrix(false);
    O.initilizeSequence(false);
    double res = FORWARD(A, B, pi, O, A.rows, O.observations);
    cout << res << endl;

    return 0;
}