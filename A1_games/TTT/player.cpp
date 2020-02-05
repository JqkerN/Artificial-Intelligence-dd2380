#include "player.hpp"
#include <cstdlib>
#include <limits>
#include <cmath>

namespace TICTACTOE
{

int rows(const GameState &pState, uint8_t player){
    int X_tmp = 0;
    int O_tmp = 0;
    bool X_row = false;
    bool O_row = false;
    int rowOut = 0;



    for (int r = 0; r < 4; r++)
    {
        for (int c = 0; c < 4; c++)
        {
            if (pState.at(r,c) == CELL_X)
            {
                X_tmp += 1;
                X_row = true;
            }
            else if (pState.at(r,c) == CELL_O)
            {
                O_tmp += 1;
                O_row = true;
            }
        }  
        if (X_row == true && O_row == true)
        {
            X_tmp = 0;
            O_tmp = 0;

            X_row = false;
            O_row = false;
        }
        else if (X_row == true && O_row == false)
        {   if (X_tmp == 1){
            rowOut += X_tmp;
            X_row = false;
            }else {
            rowOut += pow(10,X_tmp);
            X_row = false;
            }
        } 
        else if (O_row == true && X_row == false){
            if (O_tmp == 1){
            rowOut -= X_tmp;
            X_row = false;
            }else {
            rowOut -= pow(10,X_tmp);
            X_row = false;
            }
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



    for (int c = 0; c < 4; c++)
    {
        for (int r = 0; r < 4; r++)
        {
            if (pState.at(r,c) == CELL_X)
            {
                X_tmp += 1;
                X_col = true;
            }
            else if (pState.at(r,c) == CELL_O)
            {
                O_tmp += 1;
                O_col = true;
            }
        }  
        if (X_col == true && O_col == true)
        {
            O_tmp = 0;
            X_tmp = 0;

            X_col = false;
            O_col = false;
        }
        else if (X_col == true && O_col == false){
            if (X_tmp <= 1){
            colOut += X_tmp;
            X_col = false;
            }else {
            colOut += pow(10,X_tmp);
            X_col= false;
            }
        }
        else if (O_col == true && X_col == false){
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
    return colOut;
}

int diag(const GameState &pState, uint8_t player){
    int X_tmp = 0;
    int O_tmp = 0;
    bool X_diag = false;
    bool O_diag = false;
    int diagOut = 0;


    for (int d = 0; d < 4; d++)
    {
        if (pState.at(d,d) == CELL_X)
        {
            X_tmp += 1;
            X_diag = true;
        }
        else if (pState.at(d,d) == CELL_O)
        {
            O_tmp += 1;
            O_diag = true;
        }
    }  
    if (X_diag == true && O_diag == true)
    {
        O_tmp = 0;
        X_tmp = 0;
        X_diag = false;
        O_diag = false;
    }
    else if (X_diag == true && O_diag == false){
        if (X_tmp <= 1){
            diagOut += X_tmp;
            X_diag = false;
            }else {
            diagOut += pow(10,X_tmp);
            X_diag= false;
            }
    }
    else if (O_diag == true && X_diag == false){
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

    for (int d = 0; d < 4; d++)
    {
        if (pState.at(3-d,d) == CELL_X)
        {
            X_tmp += 1;
            X_diag = true;
        }
        else if (pState.at(3-d,d) == CELL_O)
        {
            O_tmp += 1;
            O_diag = true;
        }
    }  
    if (X_diag == true && O_diag == true)
    {
        O_tmp = 0;
        X_tmp = 0;
        X_diag = false;
        O_diag = false;
    }
    else if (X_diag == true && O_diag == false){
        if (X_tmp <= 1){
            diagOut += X_tmp;
            X_diag = false;
            }else {
            diagOut += pow(10,X_tmp);
            X_diag= false;
            }
    }
    else if (O_diag == true && X_diag == false){
        if (O_tmp <= 1){
            diagOut -= O_tmp;
            O_diag = false;
            }else {
            diagOut -= pow(10,O_tmp);
            O_diag= false;
            } 
    } 
    return diagOut;
}


int gamma(const GameState &pState, uint8_t player){
    int R = rows(pState, player);
    int C = cols(pState, player);
    int D = diag(pState, player);
    
    if (pState.isXWin())
    {   
        return 10000 + R + C + D;
    }
    else if (pState.isOWin())
    {   
        return -10000 + R + C + D;
    }
    else if (pState.isDraw())
    {
        return 0;
    }
    else
    {
        return R + C + D;
    }
}

int alphabeta(const GameState &pState, uint8_t player, int depth, int alpha, int beta){
    std::vector<GameState> lNextStates;
    pState.findPossibleMoves(lNextStates);
    // std::cerr << pState.toMessage() << std::endl;
    int v;

    if (depth == 0 || lNextStates.size() == 0)
    {   
        v = gamma(pState, player);
    }
    else if (player == CELL_X)
    {
        v = std::numeric_limits<int>::min();
        for (GameState child : lNextStates)
        {   
            v = std::max(v, alphabeta(child, CELL_O, depth-1, alpha, beta));
            alpha = std::max(alpha, v);
            if (beta <= alpha)
            {
                break;
            }
            
        }

    }
    else
    {
        v = std::numeric_limits<int>::max();
        for (GameState child : lNextStates)
        {   
            v = std::min(v, alphabeta(child, CELL_X, depth-1, alpha, beta));
            beta = std::min(beta, v);
            if (beta <= alpha)
            {
                break;
            }   
        }
    }
    return v;
}



GameState Player::play(const GameState &pState,const Deadline &pDue)
{
    std::vector<GameState> lNextStates;
    pState.findPossibleMoves(lNextStates);
    

    if (lNextStates.size() == 0) return GameState(pState, Move());
    /*
     * Here you should write your clever algorithms to get the best next move, ie the best
     * next state. This skeleton returns a random move instead.
     */

    // DEFINING VARIABLES:
    uint8_t PLAYER = pState.getNextPlayer();
    uint8_t OPPONENT;
    GameState bestState;
    int alpha = std::numeric_limits<int>::min();
    int beta = std::numeric_limits<int>::max();
    int depth = 4;
    int current_MAX = std::numeric_limits<int>::min();
    int current_MIN = std::numeric_limits<int>::max();
    int v = 0;
    if (PLAYER == CELL_X) OPPONENT = CELL_O;
    else OPPONENT = CELL_X;

    for (GameState state : lNextStates){
        v = alphabeta(state, OPPONENT, depth, alpha, beta);
        if (PLAYER == CELL_X)
        {
            if (v > current_MAX)
                {
                    current_MAX = v;
                    bestState = state;
                }
        }
        else
        {
            if (v < current_MIN)
                {
                    current_MIN = v;
                    bestState = state;
                }
        }
        
    }
    

    return bestState;
}

/*namespace TICTACTOE*/ }
