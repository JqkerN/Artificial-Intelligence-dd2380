#include <iostream>
#include <string> 
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>


using namespace std;
class matrix_3D{
    public:
    string name;
    string input;
    int rows;
    int cols;
    int depth;

    vector<vector<vector<double>>> mat;


    void empty_3D();
    void initilizeMatrix_3D(bool verbose);
    void printMatrix_3D();
};

void matrix_3D::initilizeMatrix_3D(bool verbose = false){
    if (name.empty()){
        fprintf(stderr, "INIT 3D: Fill in name properly. name empty: %i ", name.empty());
        exit(1);
    }
    
    empty_3D();
    if (verbose){
        printMatrix_3D();
    }
}

void matrix_3D::empty_3D(){
    if (depth == 0 || cols == 0 || rows == 0){
        fprintf(stderr, "EMPTY 3D: Fill in rows and cols properly. depth: %i rows: %i cols: %i", depth, rows, cols);
        exit(1);
    }
    for (int d = 0; d < depth; d ++){
        vector<vector<double>> tmp_rows;
        for (int r = 0; r < rows; r++) {
            vector<double> tmp_cols;
            for (int c = 0; c < cols; c++) {
                tmp_cols.push_back(0.0);
            }
            tmp_rows.push_back(tmp_cols);  
        }
        mat.push_back(tmp_rows);
    }
}

void matrix_3D::printMatrix_3D() {
    cout << "size of " << name <<": (" << depth << "," << rows << "," << cols << ")"<<endl;
    for (int d = 0; d < depth; d++){
        cout << "DEPTH: " << d << endl;
        for (int r = 0; r < rows; r++){
            for (int c = 0; c < cols; c++){
                cout << mat[d][r][c] << '	';
            }
            cout << endl;
        }
    }
}

class matrix{
    public:
    string name;
    string input;
    int rows;
    int cols;
    vector<double> vec;
    vector<vector<double>> mat;

    void string2vector();
    void getMatrix();
    void printMatrix();
    void initilizeMatrix(bool verbose, bool empty);
    void emptyMatrix();
};

void matrix::initilizeMatrix(bool verbose = false, bool empty = false){
    if (name.empty() || (input.empty() && empty == false) ){
        fprintf(stderr, "INIT 2D: Fill in name and input properly. name empty: %i input: %i", name.empty(), input.empty());
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
        vec.push_back(stod(tmp));
    }
}

void matrix::getMatrix(){
    rows = vec[0];
    cols = vec[1];
    for (int r = 0; r < vec[0]; r++) {
        vector<double> tmp;
        for (int c = 0; c < vec[1]; c++) {
            int idx = 2 + c + r * vec[1];
            tmp.push_back( vec[idx]);
        }
        mat.push_back(tmp);  
    }
}

void matrix::emptyMatrix(){
    if (cols == 0 || rows == 0){
        fprintf(stderr, "EMPTY MATRIX:  Fill in rows and cols properly. rows: %i cols: %i", rows, cols);
        exit(1);
    }
    for (int r = 0; r < rows; r++) {
        vector<double> tmp;
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
    vector<double> vec;

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

string vector2string(vector<int> vector_float){
    string value;
    for (int idx = 0; idx < vector_float.size(); idx++){
        value += to_string(vector_float[idx]) +  " ";
    }
    return value;
}

matrix ALPHA(matrix A, matrix B, matrix pi, sequence O, int N, int T){

    matrix alpha;
    double alpha_prob = 0;
    double tmp;
    alpha.name = "ALPHA Matrix";
    alpha.rows = N;
    alpha.cols = T;
    alpha.initilizeMatrix(false, true);

    // Initialization step
    for (int s = 0; s < N; s++) {
        alpha.mat[s][0] = ( pi.mat[0][s] * B.mat[s][O.vec[0]]);
    }

    // Recursion step
    for (int t = 0; t < T-1; t++) {
        for (int s = 0; s < N; s++) {
            tmp = 0;
            for (int sp = 0; sp < N; sp++) {
                tmp +=  alpha.mat[sp][t] * A.mat[sp][s]; 
            }
            alpha.mat[s][t+1] = tmp * B.mat[s][O.vec[t+1]]; 
        }   
    }
    // // Termination step
    // for (int s = 0; s < N; s++) {
    //             alpha_prob +=  alpha.mat[s][T-1]; 
    //         }
    return alpha;
}

matrix BETA(matrix A, matrix B, matrix pi, sequence O, int N, int T, int t_current){

    matrix beta; beta.name = "BETA matrix ";
    beta.rows = N; 
    beta.cols =T; 
    beta.initilizeMatrix(false, true);
    // INITIALIZATION:
    for (int i = 0; i < N; i++) {
        beta.mat[i][T-1] = 1;
    }
    // RECURSION:
    for (int t = T-1; t >= t_current; t--) {
        for (int i = 0; i < N; i++) {
            int sum = 0;
            for (int j = 0; j < N; j++) {
                sum += A.mat[i][j] * B.mat[j][O.vec[t]] * beta.mat[i][t];
            }
            beta.mat[i][t-1] = sum;
        }
    }

    return beta;
}

struct gamma_zeta_output
{
    matrix_3D gamma;
    matrix zeta;
};


gamma_zeta_output GAMMA(matrix A, matrix B, matrix pi, sequence O, int N, int T){
    matrix_3D gamma; gamma.name = "gamma 3D matrix";
    gamma.depth = T; gamma.rows = N; gamma.cols = N;
    gamma.initilizeMatrix_3D();

    matrix zeta; zeta.name = "zeta matriz";
    zeta.rows = N; zeta.cols = T; zeta.initilizeMatrix(false, true);
    double sum;

    sequence O_alpha; O_alpha.name = "O_(1:t)";
    sequence O_beta; O_beta.name = "O_(t+1:T)";

    matrix alpha;
    matrix beta;
    double alpha_prob;
    alpha = ALPHA(A, B, pi, O, N, T);
    alpha.printMatrix();
    for (int s = 0; s < N; s++) {
        alpha_prob +=  alpha.mat[s][T-1]; 
    }
    cout << "FINAL ALPHA durududu durututudu: " << alpha_prob << endl;

    for (int t = 1; t < T; t++) {
        O_alpha.vec = vector<double> (&O.vec[0], &O.vec[t]); O_alpha.observations = t;
        O_beta.vec = vector<double> (&O.vec[t], &O.vec[T]); O_beta.observations = T-t;
        for (int i = 0; i < N; i++){
            sum = 0;
            for (int j = 0; j < N; j++){
                alpha = ALPHA(A, B, pi, O_alpha, N, O_alpha.observations);
                beta = BETA(A, B, pi, O_beta, N, T, O_beta.observations);
                gamma.mat[t][i][j] = (alpha.mat[i][t] * A.mat[i][j] * B.mat[j][O.vec[t]] * beta.mat[j][t])/alpha_prob;
                sum += gamma.mat[t][i][j];
            }
            zeta.mat[i][t] = sum;
        }
    }
    // gamma.printMatrix_3D();
    // zeta.printMatrix();
    return {gamma, zeta};
}

void printVector(vector<int> A){   
	for (int r = 0; r < A.size(); r++) {
		cout << A[r] << '	';
	}
	cout << endl;
	cout << " " << endl;
}


struct baum_welch_estimate
{
    matrix A;
    matrix B;
};

baum_welch_estimate baum_welch(matrix A, matrix B, matrix pi, sequence O, int N, int T){
    /**
     * __Psudocode__
     * INITILIZE: A and B.
     * ITERATE: -> to convergence.
     * E:
     *      Calculate Gamma(alpha, beta)
     *      Caluclate Zeta(alpha, beta, B, A) 
     * M:
     *      Calculate A(gamma, zeta)
     *      Caluclate B(zeta)
     * RETURN: A, B
    */
    double A_numerator;
    double A_denominator;
    double B_numerator;
    double B_denominator;

    // WHILE -> to convergence:
    gamma_zeta_output gamma_N_zeta = GAMMA(A, B, pi, O, N, T);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++){
            A_numerator = 0;
            A_denominator = 0;
            for (int t = 1; t < T; t++){
                A_numerator +=  gamma_N_zeta.gamma.mat[t][i][j];
                A_denominator += gamma_N_zeta.zeta.mat[i][t];

            }
            // cout << "A_numerator = "<< A_numerator << endl;
            // cout << "A_denominator = "<< A_denominator << endl;
            A.mat[i][j] = A_numerator/A_denominator;
        }
    }
    cout << "A" << endl;

    for (int i = 0; i < N; i++) {
        for (int k = 0; k < B.cols; k++){
            B_numerator = 0;
            B_denominator = 0;
            for (int t = 0; t < T; t++){
                if (O.vec[t] == k){
                    B_numerator += gamma_N_zeta.zeta.mat[i][t];
                }
                B_denominator += gamma_N_zeta.zeta.mat[i][t];
            }
            // cout << "B_numerator = "<< B_numerator << endl;
            // cout << "B_denominator = "<< B_denominator << endl;
            B.mat[i][k] = B_numerator/B_denominator;
        }
    }



    return {A, B};
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
    cout << "Number of states: " << A.rows << endl;
    cout << "Number of time steps: " << O.observations << endl;
    baum_welch_estimate tmp = baum_welch(A, B, pi, O, A.rows, O.observations);
    tmp.B.printMatrix();
    tmp.A.printMatrix();



    return 0;
}