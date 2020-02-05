#ifndef _TICTACTOE_PLAYER_HPP_
#define _TICTACTOE_PLAYER_HPP_

#include "constants.hpp"
#include "deadline.hpp"
#include "move.hpp"
#include "gamestate.hpp"
#include <vector>

namespace TICTACTOE
{

    int rows(const GameState &pState, uint8_t player);
    int cols(const GameState &pState, uint8_t player);
    int diag(const GameState &pState, uint8_t player);
    int gamma(const GameState &pState, uint8_t player);
    int alphabeta(const GameState &pState, uint8_t player, int depth, int alpha, int beta);
    

class Player
{
public:
    ///perform a move
    ///\param pState the current state of the board
    ///\param pDue time before which we must have returned
    ///\return the next state the board is in after our move
    GameState play(const GameState &pState, const Deadline &pDue);
};

/*namespace TICTACTOE*/ }

#endif
