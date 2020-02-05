#include "player.hpp"
#include <cstdlib>
#include <limits>
#include <cmath>


namespace checkers
{

int numberOfPieces(const GameState &pState, uint8_t player){
    /** Calculates the board state.
     * - If protected.
     * - If king.
     * - Number of pieces left, multiplied with position value.
    */
    int RED_points = 0;
    int WHITE_points = 0;
    int posMultiplier[8][8] ={{1, 1, 1, 1, 1, 1, 1, 1},
                              {1, 1, 1, 1, 1, 1, 1, 1},
                              {1, 1, 8, 8, 8, 8, 1, 1},
                              {1, 1, 8, 8, 8, 8, 1, 1},
                              {1, 1, 8, 8, 8, 8, 1, 1},
                              {1, 1, 8, 8, 8, 8, 1, 1},
                              {1, 1, 1, 1, 1, 1, 1, 1},
                              {1, 1, 1, 1, 1, 1, 1, 1}};

    for(int r=0; r<=7; r++){
        for(int c=0; c<=7; c++){
            if (pState.at(r,c)&CELL_RED){

            // Checking for RED player
                if (pState.at(r-1,c-1)&CELL_RED || pState.at(r-1,c-1)&CELL_INVALID ){
                    RED_points += 3 * posMultiplier[r][c];
                }
                if (pState.at(r-1,c+1)&CELL_RED || pState.at(r-1,c+1)&CELL_INVALID){
                    RED_points += 3 * posMultiplier[r][c];
                }

                if (pState.at(r,c)&CELL_KING){
                    RED_points += 20 * posMultiplier[r][c];
                }else{
                    RED_points += 5 * posMultiplier[r][c];
                }

            // Checking for WHITE player
            } else if( pState.at(r,c)&CELL_WHITE){
                if (pState.at(r+1,c-1)&CELL_WHITE || pState.at(r+1,c-1)&CELL_INVALID){
                    WHITE_points += 3 * posMultiplier[r][c];
                }
                if (pState.at(r+1,c+1)&CELL_WHITE || pState.at(r+1,c+1)&CELL_INVALID){
                    WHITE_points += 3 * posMultiplier[r][c];
                }

                if (pState.at(r,c)&CELL_KING){
                    WHITE_points += 20 * posMultiplier[r][c];
                }else{
                    WHITE_points += 5 * posMultiplier[r][c];
                    
                }
            }
            
        }
    }
    return RED_points - WHITE_points;
    
}


int gamma(const GameState &pState, uint8_t player){
    /** GAMMA FUNCTION
     * Calculates the heuristic state of the board
    */
    if (pState.isRedWin())          return 10000;
    else if (pState.isWhiteWin())   return -10000;
    else if (pState.isDraw())       return 0;
    else                            return numberOfPieces(pState, player);
}


int alphabeta(const GameState &pState, int depth, int alpha, int beta, uint8_t player, const Deadline &pDue){
    /** MINIMAX with alpha-beta proning and iterative deepening
     * recursive function to calculate the best move for min and max player, ie white and red.
    */
    std::vector<GameState> lNextStates;
    pState.findPossibleMoves(lNextStates);
    int v;

    if (int(lNextStates.size()) == 0 || depth <= 0 ){
        v = gamma(pState, player);

    }else if(player == CELL_RED){
        if (pDue.operator-(pDue.now()) <= 0.001 ) return gamma(pState, player);
        v = std::numeric_limits<int>::min();
        for (GameState state : lNextStates){
            v = std::max(v, alphabeta(state, depth-1, alpha, beta, CELL_WHITE, pDue));
            alpha = std::max(alpha, v);
            if (beta <= alpha){
                break;
            }
        }

    }else{
        if (pDue.operator-(pDue.now()) <= 0.001 ) return gamma(pState, player);
        v = std::numeric_limits<int>::max();
        for (GameState state : lNextStates){
            v = std::min(v, alphabeta(state, depth-1, alpha, beta, CELL_RED, pDue));
            beta = std::min(beta, v);
            if (beta <= alpha){
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

    uint8_t player = pState.getNextPlayer();
    uint8_t nextPlayer = (player == CELL_RED) ? CELL_WHITE:CELL_RED;
    int alpha = std::numeric_limits<int>::min();
    int beta = std::numeric_limits<int>::max();
    GameState bestState;
    int depth =0;
    int v;
    int v_tmp;
    


    
    while (true){
        if(player == CELL_RED){
            v = std::numeric_limits<int>::min();
            for (GameState state : lNextStates){
                v_tmp = alphabeta(state, depth, alpha, beta, nextPlayer, pDue);
                if (v_tmp > v){
                    bestState = state;
                } 
                v = std::max(v, v_tmp);
                alpha = std::max(alpha, v);
                if (beta <= alpha){ 
                    break;
                }
            }
        }
        if(player == CELL_WHITE){
            v = std::numeric_limits<int>::max();
            for (GameState state : lNextStates){
                v_tmp = alphabeta(state, depth, alpha, beta, nextPlayer, pDue);
                if (v_tmp < v){
                    bestState = state;
                } 
                v = std::min(v, v_tmp);
                beta = std::min(beta, v);
                if (beta <= alpha){
                    break;
                }
            }
        }
        if ( v >= 10000 && player == CELL_RED)      return bestState;
        if ( v <= -10000 && player == CELL_WHITE)   return bestState;
        if ( pDue.operator-(pDue.now()) <= 0.001 )  return bestState;
        depth += 1;
    }

    return bestState;
}

/*namespace checkers*/ }