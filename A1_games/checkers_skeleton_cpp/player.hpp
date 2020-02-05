#ifndef _CHECKERS_PLAYER_HPP_
#define _CHECKERS_PLAYER_HPP_

#include "constants.hpp"
#include "deadline.hpp"
#include "move.hpp"
#include "gamestate.hpp"
#include <vector>
#include <cstdlib>
#include <limits>
#include <cmath>

namespace checkers
{   
    /** Calculates the board state.
         * - If protected.
         * - If king.
         * - Number of pieces left, multiplied with position value.
    */
    int numberOfPieces(const GameState &pState, uint8_t player);

    /** GAMMA FUNCTION
         * Calculates the heuristic state of the board
    */
    int gamma(const GameState &pState, uint8_t player);

    /** MINIMAX with alpha-beta proning and iterative deepening
        * recursive function to calculate the best move for min and max player, ie white and red.
    */
    int alphabeta(const GameState &pState, int depth, int alpha, int beta, uint8_t player, const Deadline &pDue);

class Player
{
public:
    ///perform a move
    ///\param pState the current state of the board
    ///\param pDue time before which we must have returned
    ///\return the next state the board is in after our move
    GameState play(const GameState &pState, const Deadline &pDue);
};

/*namespace checkers*/ }

#endif
