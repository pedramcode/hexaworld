//
// Created by pedram on 3/17/23.
//

#ifndef GAME_ABSTRACTSTATE_H
#define GAME_ABSTRACTSTATE_H

namespace game {

    class Game;

    class AbstractState {
    protected:
        Game *_game;
    public:
        explicit AbstractState(Game* game);
        virtual void update() = 0;
        virtual void render() = 0;
    };

} // game

#endif //GAME_ABSTRACTSTATE_H
