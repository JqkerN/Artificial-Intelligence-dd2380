#include <iostream>
#include <string> 
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <limits>
#include <cmath>


using namespace std;

class matrix_3D{
    public:
    string name;
    string input;
    int rows;
    int cols;
    int depth;

    vector<vector<vector<double>>> mat;


    void initilizeMatrix_3D(bool verbose = false){
        if (name.empty()){
            fprintf(stderr, "INIT 3D: Fill in name properly. name empty: %i ", name.empty());
            exit(1);
        }
        
        empty_3D();
        if (verbose){
            printMatrix_3D();
        }
    }

    void empty_3D(){
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

    void printMatrix_3D() {
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

};

class matrix{
    public:
    string name;
    string input;
    int rows;
    int cols;
    vector<double> vec;
    vector<vector<double>> mat;

    void initilizeMatrix(bool verbose = false, bool empty = false){
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

    void string2vector(){
        istringstream iss(input);
        string tmp;
        while(iss >> tmp) {
            vec.push_back(stod(tmp));
        }
    }

    void getMatrix(){
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

    void emptyMatrix(){
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

    void printMatrix() {
        cout << "size of " << name <<": (" << rows << "," << cols << ")"<<endl;;
        for (int r = 0; r < mat.size(); r++){
            for (int c = 0; c < mat[0].size(); c++){
                cout << mat[r][c] << '	';
            }
            cout << endl;
        }
    }

    void KATTIS_OUTPUT(){
        cout << rows << ' ' << cols << ' ';
        for (int r = 0; r < mat.size(); r++){
            for (int c = 0; c < mat[0].size(); c++){
                cout << mat[r][c] << ' ';
            }
        }
        cout << endl;
    }
};

class sequence{
    public:
    string name;
    string input;
    int observations;
    vector<double> vec;

    void initilizeSequence(bool verbose = false, bool empty = false){
        if (name.empty() ){
            fprintf(stderr, "Fill in name and input properly. name empty: %i", name.empty());
        }
        if(empty == true){
            emptySequence();
        }else{
            string2vector();
            if (verbose){
                printSequence();
            }
        }
        

    }
    void emptySequence(){
        for (int i = 0; i < observations; i++){
            vec.push_back(0.0);
        }
    }

    void string2vector(){
        istringstream iss(input);
        string tmp;
        string tmp_2;
        iss >> tmp_2;
        observations = stoi(tmp_2);
        while(iss >> tmp) {
            vec.push_back(stof(tmp));
        }
    }

    void printSequence() {
        cout << "size of " << name <<": (" << observations << ")" <<endl;;
        for (int idx = 0; idx < observations; idx++){
            cout << vec[idx] << '	';
        }
        cout << endl;
    }
};

string vector2string(vector<int> vector_float){
    string value;
    for (int idx = 0; idx < vector_float.size(); idx++){
        value += to_string(vector_float[idx]) +  " ";
    }
    return value;
}

void printVectorDouble(vector<double> A){   
	for (int r = 0; r < A.size(); r++) {
		cout << A[r] << '	';
	}
	cout << endl;
	cout << " " << endl;
}


void printVector(vector<int> A){   
	for (int r = 0; r < A.size(); r++) {
		cout << A[r] << '	';
	}
	cout << endl;
	cout << " " << endl;
}

struct alpha_beta_output{
    matrix alpha;
    matrix beta;
    sequence C;
};

struct gamma_zeta_output{
    matrix_3D gamma;
    matrix zeta;
    sequence C;
};

struct baum_welch_output{
    matrix A;
    matrix B;
};


alpha_beta_output ALPHA_BETA(matrix A, matrix B, matrix pi, sequence O, int N, int T){
    matrix alpha; alpha.name = "alpha matrix"; alpha.rows = N; alpha.cols = T; alpha.initilizeMatrix(false, true);
    matrix beta; beta.name = "beta matrix"; beta.rows = N; beta.cols = T; beta.initilizeMatrix(false, true);
    sequence C; C.name = "Scale Factors"; C.observations = T; C.initilizeSequence(false, true);
    double c = 0.0; 
    double alpha_tmp = 0.0;
    double beta_tmp = 0.0;

    // NOTE: alpha - pass
    // Compute alpha_0(i)
    for (int i = 0; i < N; i++){
        alpha.mat[i][0] = pi.mat[0][i] * B.mat[i][O.vec[0]];
        c += alpha.mat[i][0];
    }
    
    // Scale alpha_0(i)
    C.vec[0] = 1/c;
    for (int i = 0; i < N; i++){
        alpha.mat[i][0] = alpha.mat[i][0]*C.vec[0];
    }

    // Compute alpha_t(i)
    for (int t = 1; t < T; t++){
        c = 0.0;
        for (int i = 0; i < N; i++){
            alpha_tmp = 0.0;
            for (int j = 0; j < N; j++){
                alpha_tmp +=  alpha.mat[j][t-1] * A.mat[j][i];
            }
            alpha.mat[i][t] = alpha_tmp * B.mat[i][O.vec[t]];
            c += alpha.mat[i][t];
        }
        // Scale alpha_t(i)
        C.vec[t] = 1/c;
        for (int idx = 0; idx < N; idx++){
            alpha.mat[idx][t] = alpha.mat[idx][t] * C.vec[t];
        }
    }
    

    // NOTE: beta - pass
    // Let B_(T-1)(i) = 1, scaled by C(T-1)
    for (int i = 0; i < N; i++){
        beta.mat[i][T-1] = C.vec[T-1];
    }

    // Compute beta_t(i)
    for (int t = T-2; t >= 0; t--){
        for (int i = 0; i < N; i++){
            beta_tmp = 0.0;
            for (int j = 0; j < N; j++){
                beta_tmp += A.mat[i][j] * B.mat[j][O.vec[t+1]] * beta.mat[j][t+1];
            }
            beta.mat[i][t] = C.vec[t] * beta_tmp;
        }
    }

    return {alpha, beta, C};
}

gamma_zeta_output GAMMA(matrix A, matrix B, matrix pi, sequence O, int N, int T){
    matrix_3D gamma; gamma.name = "gamma 3D matrix"; gamma.depth = T; gamma.rows = N; gamma.cols = N; gamma.initilizeMatrix_3D(false);
    matrix zeta; zeta.name = "zeta matrix"; zeta.rows = N; zeta.cols = T ; zeta.initilizeMatrix(false, true);
    alpha_beta_output A_B_C = ALPHA_BETA(A, B, pi, O, N, T);
    matrix alpha = A_B_C.alpha;
    matrix beta = A_B_C.beta;
    sequence C = A_B_C.C;
    
    double alpha_norm = 0.0;
    for (int k = 0; k < N; k++){
        alpha_norm += alpha.mat[k][T-1];
    }
    cout << "ALPHA NORM : " << alpha_norm<< endl;

    // NOTE: Gamma
    for (int t = 0; t < T-1; t++ ){
        for (int i = 0; i < N; i++){
            for (int j = 0; j < N; j++){
                gamma.mat[t][i][j] = alpha.mat[i][t] * A.mat[i][j] * B.mat[j][O.vec[t + 1]] * beta.mat[j][t+1];
                zeta.mat[i][t] += gamma.mat[t][i][j];
            }
        }
    }

    // Special case for gamma_(T-1)(i)
    for (int i = 0; i < N; i++){
        zeta.mat[i][T-1] = alpha.mat[i][T-1];
    }
    
    return {gamma, zeta, C};
}

baum_welch_output BAUM_WELCH(matrix A, matrix B, matrix pi, sequence O, int N, int T){
    double denom;
    double numer;

    int maxIters = 1000;
    int iters = 0;
    double oldLogProb = numeric_limits<double>::min();
    double logProb = 0;

    while (iters < maxIters && oldLogProb > logProb){
        gamma_zeta_output G_Z_C = GAMMA(A, B, pi, O, N, T);
        matrix_3D gamma = G_Z_C.gamma; 
        matrix zeta = G_Z_C.zeta; 
        sequence C = G_Z_C.C;
        // C.printSequence();
        zeta.printMatrix();


        // NOTE: Re-estimate pi
        for (int i = 0; i < N; i++){
            pi.mat[0][i] = zeta.mat[i][0];
        }
        pi.printMatrix();

        // NOTE: Re-estimate A
        for (int i = 0; i < N; i++){
            denom = 0.0;
            for (int t = 0; t < T-1; t++){
                denom += zeta.mat[i][t];
            }
            for (int j = 0; j < N; j++){
                numer = 0.0;
                for (int t = 0; t < T-1; t++){
                    numer += gamma.mat[t][i][j];
                }
                A.mat[i][j] = numer/denom;
            }
        }
        A.printMatrix();
        
        // NOTE: Re-estimate B
        for (int i = 0; i < N; i++){
            denom = 0.0;
            for (int t = 0; t < T; t++){
                denom += zeta.mat[i][t];
            }
            for (int j = 0; j < B.cols; j++){
                numer = 0.0;
                for (int t = 0; t < T; t++){
                    if (O.vec[t] == j){
                        numer += zeta.mat[i][t];
                    }
                }
                B.mat[i][j] = numer/denom;
            }
        }
        B.printMatrix();

        // NOTE: Compute log(P(O|lambda))
        logProb = 0.0;
        for (int i = 0; i < T; i++){
            logProb += log(C.vec[i]);
        }
        logProb = -logProb;
        iters++;
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
    pi.initilizeMatrix(true);
    O.initilizeSequence(false);

    baum_welch_output newEstimate = BAUM_WELCH(A, B, pi, O, A.rows, O.observations);
    newEstimate.A.KATTIS_OUTPUT();
    newEstimate.B.KATTIS_OUTPUT();
    return 0;
}

