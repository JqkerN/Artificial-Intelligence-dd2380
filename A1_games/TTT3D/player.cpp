#include "player.hpp"
#include <cstdlib>
#include <limits>
#include <cmath>

namespace TICTACTOE3D
{

int rows_tmp(const GameState &pState, uint8_t player){
    int X_tmp = 0;
    int O_tmp = 0;
    bool X_row = false;
    bool O_row = false;
    int rowOut = 0;
    

    for (int l = 0; l < 4; l++){
        for (int r = 0; r < 4; r++){
            for (int c = 0; c < 4; c++){
                if (pState.at(c,r,l) == CELL_X){
                    X_tmp += 1;
                    X_row = true;
                }
                else if (pState.at(c,r,l) == CELL_O){
                    O_tmp += 1;
                    O_row = true;
                }
                if (X_row == true && O_row == true){
                    X_tmp = 0;
                    O_tmp = 0;
                    X_row = false;
                    O_row = false;
                    break;
                }
            }  
            if (X_row == true && O_row == false){   
                if (X_tmp <= 1){
                rowOut += X_tmp;
                X_row = false;
                }else {
                rowOut += pow(10,X_tmp);
                X_row = false;
                }
            }else if (O_row == true && X_row == false){
                if (O_tmp <= 1){
                rowOut -= O_tmp;
                O_row = false;
                }else {
                rowOut -= pow(10,O_tmp);
                O_row = false;
                }
            }
            O_tmp = 0;
            X_tmp = 0;
            X_row = false;
            O_row = false;       
        } 
    }

    
    return rowOut;
}

int rows(const GameState &pState, uint8_t player){
    int X_tmp = 0;
    int O_tmp = 0;
    bool X_row = false;
    bool O_row = false;
    int rowOut = 0;
    

    for (int l = 0; l < 4; l++){
        for (int r = 0; r < 4; r++){
            for (int c = 0; c < 4; c++){
                if (pState.at(c,r,l) == CELL_X){
                    X_tmp += 1;
                    X_row = true;
                }
                else if (pState.at(c,r,l) == CELL_O){
                    O_tmp += 1;
                    O_row = true;
                }
                
            }  
            if (X_row == true && O_row == true){
                X_tmp = 0;
                O_tmp = 0;
                X_row = false;
                O_row = false;
            }else if (X_row == true && O_row == false){   
                if (X_tmp <= 1){
                rowOut += X_tmp;
                X_row = false;
                }else {
                rowOut += pow(10,X_tmp);
                X_row = false;
                }
            }else if (O_row == true && X_row == false){
                if (O_tmp <= 1){
                rowOut -= O_tmp;
                O_row = false;
                }else {
                rowOut -= pow(10,O_tmp);
                O_row = false;
                }
                
            }
            O_tmp = 0;
            X_tmp = 0;
            X_row = false;
            O_row = false;       
        }
        O_tmp = 0;
        X_tmp = 0;
        X_row = false;
        O_row = false;  
    }

    
    return rowOut;
}
    
int cols(const GameState &pState, uint8_t player){
    int X_tmp = 0;
    int O_tmp = 0;
    bool X_col = false;
    bool O_col = false;
    int colOut = 0;


    for (int l = 0; l < 4; l++){
        for (int c = 0; c < 4; c++){
            for (int r = 0; r < 4; r++){
                if (pState.at(c,r,l) == CELL_X){
                    X_tmp += 1;
                    X_col = true;
                }else if (pState.at(c,r,l) == CELL_O){
                    O_tmp += 1;
                    O_col = true;
                }
            } 
            if (X_col == true && O_col == true){
                O_tmp = 0;
                X_tmp = 0;
                X_col = false;
                O_col = false;
            }else if (X_col == true && O_col == false){
                if (X_tmp <= 1){
                colOut += X_tmp;
                X_col = false;
                }else {
                colOut += pow(10,X_tmp);
                X_col= false;
                }
            }else if (O_col == true && X_col == false){
                if (O_tmp <= 1){
                colOut -= O_tmp;
                O_col = false;
                }else {
                colOut -= pow(10,O_tmp);
                O_col = false;
                }
            }
            O_tmp = 0;
            X_tmp = 0;
            X_col = false;
            O_col = false;       
        }
        O_tmp = 0;
        X_tmp = 0;
        X_col = false;
        O_col = false;  
    }
    return colOut;   
}

int layers(const GameState &pState, uint8_t player){
    int X_tmp = 0;
    int O_tmp = 0;
    bool X_lay = false;
    bool O_lay = false;
    int colOut = 0;


    for (int r = 0; r < 4; r++){
        for (int c = 0; c < 4; c++){
            for (int l = 0; l < 4; l++){
                if (pState.at(c,r,l) == CELL_X){
                    X_tmp += 1;
                    X_lay = true;
                }else if (pState.at(c,r,l) == CELL_O){
                    O_tmp += 1;
                    O_lay = true;
                }
            }  
            if (X_lay == true && O_lay == true){
                O_tmp = 0;
                X_tmp = 0;

                X_lay = false;
                O_lay = false;
            }else if (X_lay == true && O_lay == false){
                if (X_tmp <= 1){
                colOut += X_tmp;
                X_lay = false;
                }else {
                colOut += pow(10,X_tmp);
                X_lay= false;
                }
            }else if (O_lay == true && X_lay == false){
                if (O_tmp <= 1){
                colOut -= O_tmp;
                O_lay = false;
                }else {
                colOut -= pow(10,O_tmp);
                O_lay = false;
                }
            }
            O_tmp = 0;
            X_tmp = 0;
            X_lay = false;
            O_lay = false;       
        }
    }
    return colOut;   
}

int diag(const GameState &pState, uint8_t player){
    int X_tmp = 0;
    int O_tmp = 0;
    bool X_diag = false;
    bool O_diag = false;
    int diagOut = 0;

    for (int l = 0; l < 4; l++){
        for (int d = 0; d < 4; d++){
            if (pState.at(d,d,l) == CELL_X){
                X_tmp += 1;
                X_diag = true;
            }else if (pState.at(d,d,l) == CELL_O){
                O_tmp += 1;
                O_diag = true;
            }
        }
        if (X_diag == true && O_diag == true){
                O_tmp = 0;
                X_tmp = 0;
                X_diag = false;
                O_diag = false;
        }else if (X_diag == true && O_diag == false){
            if (X_tmp <= 1){
                diagOut += X_tmp;
                X_diag = false;
                }else {
                diagOut += pow(10,X_tmp);
                X_diag= false;
                }
        }else if (O_diag == true && X_diag == false){
            if (O_tmp <= 1){
                diagOut -= O_tmp;
                O_diag = false;
                }else {
                diagOut -= pow(10,O_tmp);
                O_diag= false;
                }

        }
        X_tmp = 0;
        O_tmp = 0;
        X_diag = false;
        O_diag = false;
    }


    for (int l = 0; l < 4; l++){
        for (int d = 0; d < 4; d++){
            if (pState.at(d,3-d,l) == CELL_X){
                X_tmp += 1;
                X_diag = true;
            }else if (pState.at(d,3-d,l) == CELL_O){
                O_tmp += 1;
                O_diag = true;
            }
        } 
        if (X_diag == true && O_diag == true){
            O_tmp = 0;
            X_tmp = 0;
            X_diag = false;
            O_diag = false;
        }else if (X_diag == true && O_diag == false){
            if (X_tmp <= 1){
                diagOut += X_tmp;
                X_diag = false;
                }else {
                diagOut += pow(10,X_tmp);
                X_diag= false;
                }
        }else if (O_diag == true && X_diag == false){
            if (O_tmp <= 1){
                diagOut -= O_tmp;
                O_diag = false;
                }else {
                diagOut -= pow(10,O_tmp);
                O_diag= false;
                }
        }
        X_tmp = 0;
        O_tmp = 0;
        X_diag = false;
        O_diag = false;
    }

    for (int c = 0; c < 4; c++){
        for (int d = 0; d < 4; d++){
            if (pState.at(c,d,d) == CELL_X){
                X_tmp += 1;
                X_diag = true;
            }else if (pState.at(c,d,d) == CELL_O){
                O_tmp += 1;
                O_diag = true;
            }
        }
        if (X_diag == true && O_diag == true){
            O_tmp = 0;
            X_tmp = 0;
            X_diag = false;
            O_diag = false;
        }else if (X_diag == true && O_diag == false){
            if (X_tmp <= 1){
                diagOut += X_tmp;
                X_diag = false;
                }else {
                diagOut += pow(10,X_tmp);
                X_diag= false;
                }
        }else if (O_diag == true && X_diag == false){
            if (O_tmp <= 1){
                diagOut -= O_tmp;
                O_diag = false;
                }else {
                diagOut -= pow(10,O_tmp);
                O_diag= false;
                }
        }
        X_tmp = 0;
        O_tmp = 0;
        X_diag = false;
        O_diag = false;
    }

    for (int c = 0; c < 4; c++){
        for (int d = 0; d < 4; d++){
            if (pState.at(c,d,3-d) == CELL_X){
                X_tmp += 1;
                X_diag = true;
            }else if (pState.at(c,d,3-d) == CELL_O){
                O_tmp += 1;
                O_diag = true;
            }
        } 
        if (X_diag == true && O_diag == true){
            O_tmp = 0;
            X_tmp = 0;
            X_diag = false;
            O_diag = false;
        }else if (X_diag == true && O_diag == false){
            if (X_tmp <= 1){
                diagOut += X_tmp;
                X_diag = false;
                }else {
                diagOut += pow(10,X_tmp);
                X_diag= false;
                }
        }else if (O_diag == true && X_diag == false){
            if (O_tmp <= 1){
                diagOut -= O_tmp;
                O_diag = false;
                }else {
                diagOut -= pow(10,O_tmp);
                O_diag= false;
                }
        }
        X_tmp = 0;
        O_tmp = 0;
        X_diag = false;
        O_diag = false;
    }
    

    for (int r = 0; r < 4; r++){
        for (int d = 0; d < 4; d++){
            if (pState.at(d,r,d) == CELL_X){
                X_tmp += 1;
                X_diag = true;
            }else if (pState.at(d,r,d) == CELL_O){
                O_tmp += 1;
                O_diag = true;
            }
        }
        if (X_diag == true && O_diag == true){
            O_tmp = 0;
            X_tmp = 0;
            X_diag = false;
            O_diag = false;
        }else if (X_diag == true && O_diag == false){
            if (X_tmp <= 1){
                diagOut += X_tmp;
                X_diag = false;
                }else {
                diagOut += pow(10,X_tmp);
                X_diag= false;
                }
        }else if (O_diag == true && X_diag == false){
            if (O_tmp <= 1){
                diagOut -= O_tmp;
                O_diag = false;
                }else {
                diagOut -= pow(10,O_tmp);
                O_diag= false;
                }
        }
        X_tmp = 0;
        O_tmp = 0;
        X_diag = false;
        O_diag = false;
    }

    for (int r = 0; r < 4; r++){
        for (int d = 0; d < 4; d++){
            if (pState.at(3-d,r,d) == CELL_X){
                X_tmp += 1;
                X_diag = true;
            }else if (pState.at(3-d,r,d) == CELL_O){
                O_tmp += 1;
                O_diag = true;
            }
        }
        if (X_diag == true && O_diag == true){
            O_tmp = 0;
            X_tmp = 0;
            X_diag = false;
            O_diag = false;
        }else if (X_diag == true && O_diag == false){
            if (X_tmp <= 1){
                diagOut += X_tmp;
                X_diag = false;
                }else {
                diagOut += pow(10,X_tmp);
                X_diag= false;
                }
        }else if (O_diag == true && X_diag == false){
            if (O_tmp <= 1){
                diagOut -= O_tmp;
                O_diag = false;
                }else {
                diagOut -= pow(10,O_tmp);
                O_diag= false;
                }
        }
        X_tmp = 0;
        O_tmp = 0;
        X_diag = false;
        O_diag = false;
    }

    return diagOut;
}

int cross(const GameState &pState, uint8_t player){
    int X_tmp = 0;
    int O_tmp = 0;
    bool X_cross = false;
    bool O_cross = false;
    int crossOut = 0;


    for (int d = 0; d < 4; d++){
        if (pState.at(d,d,d) == CELL_X){
            X_tmp += 1;
            X_cross = true;
        }else if (pState.at(d,d,d) == CELL_O){
            O_tmp += 1;
            O_cross = true;
        }
        if (X_cross == true && O_cross == true){
            O_tmp = 0;
            X_tmp = 0;
            X_cross = false;
            O_cross = false;
            break;
        }
    }  
    if (X_cross == true && O_cross == false){
        if (X_tmp <= 1){
            crossOut += X_tmp;
            X_cross = false;
            }else {
            crossOut += pow(10, X_tmp);
            X_cross= false;
            }
    }else if (O_cross == true && X_cross == false){
        if (O_tmp <= 1){
            crossOut -= O_tmp;
            O_cross = false;
        }else {
            crossOut -= pow(10, O_tmp);
            O_cross= false;
        }
    }

    X_tmp = 0;
    O_tmp = 0;
    X_cross = false;
    O_cross = false;

    for (int d = 0; d < 4; d++){
        if (pState.at(3-d,d,d) == CELL_X){
            X_tmp += 1;
            X_cross = true;
        }else if (pState.at(3-d,d,d) == CELL_O){
            O_tmp += 1;
            O_cross = true;
        }
        if (X_cross == true && O_cross == true){
            O_tmp = 0;
            X_tmp = 0;
            X_cross = false;
            O_cross = false;
            break;
        }
    }  
    if (X_cross == true && O_cross == false){
        if (X_tmp <= 1){
            crossOut += X_tmp;
            X_cross = false;
            }else {
            crossOut += pow(10, X_tmp);
            X_cross = false;
            }
    }else if (O_cross == true && X_cross == false){
        if (O_tmp <= 1){
            crossOut -= O_tmp;
            O_cross = false;
        }else {
            crossOut -= pow(10, O_tmp);
            O_cross = false;
        }
    }


    X_tmp = 0;
    O_tmp = 0;
    X_cross = false;
    O_cross = false;


    for (int d = 0; d < 4; d++){
        if (pState.at(d,3-d,d) == CELL_X){
            X_tmp += 1;
            X_cross = true;
        }else if (pState.at(d,3-d,d) == CELL_O){
            O_tmp += 1;
            O_cross = true;
        }
        if (X_cross == true && O_cross == true){
            O_tmp = 0;
            X_tmp = 0;
            X_cross = false;
            O_cross = false;
            break;
        }
    }  
    if (X_cross == true && O_cross == false){
        if (X_tmp <= 1){
            crossOut += X_tmp;
            X_cross = false;
            }else {
            crossOut += pow(10, X_tmp);
            X_cross = false;
            }
    }else if (O_cross == true && X_cross == false){
        if (O_tmp <= 1){
            crossOut -= O_tmp;
            O_cross = false;
        }else {
            crossOut -= pow(10, O_tmp);
            O_cross = false;
        }
    }
    


    X_tmp = 0;
    O_tmp = 0;
    X_cross = false;
    O_cross = false;

    
    for (int d = 0; d < 4; d++){
        if (pState.at(d,d,3-d) == CELL_X){
            X_tmp += 1;
            X_cross = true;
        }else if (pState.at(d,d,3-d) == CELL_O){
            O_tmp += 1;
            O_cross = true;
        }
        if (X_cross == true && O_cross == true){
            O_tmp = 0;
            X_tmp = 0;
            X_cross = false;
            O_cross = false;
            break;
        }
    }  
    if (X_cross == true && O_cross == false){
        if (X_tmp <= 1){
            crossOut += X_tmp;
            X_cross = false;
            }else {
            crossOut += pow(10, X_tmp);
            X_cross = false;
            }
    }else if (O_cross == true && X_cross == false){
        if (O_tmp <= 1){
            crossOut -= O_tmp;
            O_cross = false;
        }else {
            crossOut -= pow(10, O_tmp);
            O_cross = false;
        }
    }
    
    return crossOut;
}


int gamma(const GameState &pState, uint8_t player){
    
    if (pState.isXWin()) return 10000000;
    else if (pState.isOWin()) return -10000000;
    else if (pState.isDraw()) return 0;
    else{
        int R = rows_tmp(pState, player);
        int C = cols(pState, player); 
        int L = layers(pState, player);
        int D = diag(pState, player);
        int CR = cross(pState, player);
        // std::cerr << pState.toMessage() << std::endl;
        // std::cerr << "R=" << R << " C=" << C << " L=" << L << " D=" << D_cl + D_lr + D_rc << " CR=" << CR << std::endl;
        return R + C + L + D + CR;
    }
    
}


int alphabeta(const GameState &pState, int depth, int alpha, int beta, uint8_t player){
    std::vector<GameState> lNextStates;
    pState.findPossibleMoves(lNextStates);
    int v;

    if (int(lNextStates.size()) == 0 || depth <= 0){
        v = gamma(pState, player);
    }else if(player == CELL_X){
        v = std::numeric_limits<int>::min();
        for (GameState state : lNextStates){
            v = std::max(v, alphabeta(state, depth-1, alpha, beta, CELL_O));
            alpha = std::max(alpha, v);
            if (beta <= alpha) break;
        }
    }else{
        v = std::numeric_limits<int>::max();
        for (GameState state : lNextStates){
            v = std::min(v, alphabeta(state, depth-1, alpha, beta, CELL_X));
            beta = std::min(beta, v);
            if (beta <= alpha) break;
        }
    }
    return v;
}


GameState Player::play(const GameState &pState,const Deadline &pDue)
{
    //std::cerr << "Processing " << pState.toMessage() << std::endl;

    std::vector<GameState> lNextStates;
    pState.findPossibleMoves(lNextStates);  

    
    if (lNextStates.size() == 0) return GameState(pState, Move());

    /*
     * Here you should write your clever algorithms to get the best next move, ie the best
     * next state. This skeleton returns a random move instead.
     */

    // VARIABLES
    uint8_t player = pState.getNextPlayer();
    uint8_t nextPlayer = (player == CELL_X) ? CELL_O:CELL_X;
    int alpha = std::numeric_limits<int>::min();
    int beta = std::numeric_limits<int>::max();
    int current_MAX = std::numeric_limits<int>::min();
    int current_MIN = std::numeric_limits<int>::max();
    GameState bestState;
    int depth = 0;
    int v;
    int v_tmp;
    // std::cerr <<"NEXT PLAYER: " << nextPlayer << std::endl;

    if(player == CELL_X){
        v = std::numeric_limits<int>::min();
        for (GameState state : lNextStates){
            v_tmp = alphabeta(state, depth, alpha, beta, nextPlayer);
            if (v_tmp > v){
                bestState = state;
            } 
            v = std::max(v, v_tmp);
            alpha = std::max(alpha, v);
            if (beta <= alpha) break;
        }
    }
    if(player == CELL_O){
        v = std::numeric_limits<int>::max();
        for (GameState state : lNextStates){
            v_tmp = alphabeta(state, depth, alpha, beta, nextPlayer);
            if (v_tmp < v){
                bestState = state;
            } 
            v = std::min(v, v_tmp);
            beta = std::min(beta, v);
            if (beta <= alpha) break;
        }
    }

    // std::cerr <<"PLAYER X: " << current_MAX << std::endl;
    // std::cerr <<"PLAYER O: " << current_MIN << std::endl;
    return bestState;
}

/*namespace TICTACTOE3D*/ }
