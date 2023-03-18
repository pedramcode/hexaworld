//
// Created by pedram on 3/17/23.
//

#include "AbstractState.h"

namespace game {
    AbstractState::AbstractState(Game *game) {
        this->_game = game;
    }
} // game