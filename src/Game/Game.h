//
// Created by pedram on 3/17/23.
//

#ifndef GAME_GAME_H
#define GAME_GAME_H

#include <SFML/Graphics.hpp>
#include "AbstractState/AbstractState.h"
#include <stack>
#include <map>
#include <iostream>
#include "GameState/GameState.h"
#include "Collection/Collection.hpp"


namespace game {

    class Game {
    private:
        std::stack<AbstractState*> _states;
        sf::RenderWindow* _window{};
        void _load_assets();
        void _init_states();
    public:
        Game();
        ~Game();
        sf::RenderWindow* get_window();
        void push_state(AbstractState* state);
        void pop_state();
        void main_loop();

        Collection<sf::Texture> textures;
    };

} // game

#endif //GAME_GAME_H
