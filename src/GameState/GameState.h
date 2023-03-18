//
// Created by pedram on 3/17/23.
//

#ifndef GAME_GAMESTATE_H
#define GAME_GAMESTATE_H

#include "AbstractState/AbstractState.h"
#include "Game/Game.h"
#include <map>
#include <vector>
#include "Cell/Cell.h"
#include "Utils/PerlinNoise.hpp"
#include <cmath>

namespace game {

    class GameState : public AbstractState {
    private:
        BiomeType _get_env_type(Env *env);
        const sf::Texture *_biome_to_texture(BiomeType type);

        sf::View _view;
        sf::Vector2f _center_view;
        sf::Vector2f _size_view;
        bool _paused;

        std::vector<Cell *> _grid;
    public:
        explicit GameState(Game *game);

        ~GameState();

        void render() override;

        void update() override;
    };

} // game

#endif //GAME_GAMESTATE_H
