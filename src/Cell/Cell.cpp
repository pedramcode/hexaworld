//
// Created by pedram on 3/17/23.
//

#include "Cell.h"

namespace game {
    Env get_biome_env(BiomeType type) {
        switch (type) {

            case DEEP_SEA:
                return Env(100, 0, 30);
            case SHALLOW_SEA:
                return Env(100, 1000, 40);
            case JUNGLE:
                return Env(35, 6000, 25);
            case GRASS:
                return Env(35, 6000, 20);
            case BEACH:
                return Env(50, 5000, 30);
            case SWAMP:
                return Env(50, 6500, 30);
            case MOUNTAINS:
                return Env(10, 10000, 0);
            case DESERT:
                return Env(5, 5500, 100);
            case CANYON:
                return Env(5, 10000, 80);
            case SNOWY:
                return Env(10, 8000, 0);
            case GRASS_VILLAGE:
                return Env(35, 6000, 25);
            case SNOW_VILLAGE:
                return Env(12, 8000, 5);
            case TAIGA:
                return Env(5, 7000, 10);
        }
    }

    void Cell::draw(sf::RenderTarget &target, sf::RenderStates states) const {
        states.transform *= getTransform();
        states.texture = _texture;
        target.draw(_sprite, states);
    }

    Cell::Cell(BiomeType type, const sf::Texture *texture, sf::Vector2i pos, Env *env) {
        this->_texture = texture;
        this->_type = type;
        this->_pos = pos;
        this->_env = env;


        auto real_pos = get_real_pos();

        sf::VertexArray quad(sf::Quads, 4);
        quad[0].position = sf::Vector2f(real_pos.x, real_pos.y);
        quad[1].position = sf::Vector2f(real_pos.x + 32, real_pos.y);
        quad[2].position = sf::Vector2f(real_pos.x + 32, real_pos.y + 32);
        quad[3].position = sf::Vector2f(real_pos.x, real_pos.y + 32);

        quad[0].texCoords = sf::Vector2f(0, 0);
        quad[1].texCoords = sf::Vector2f(32, 0);
        quad[2].texCoords = sf::Vector2f(32, 32);
        quad[3].texCoords = sf::Vector2f(0, 32);

        sf::Sprite sp(*this->_texture);
        sp.setPosition(real_pos.x, real_pos.y);
        this->_sprite = sp;
    }

    sf::Vector2f Cell::get_real_pos() {
        sf::Vector2f real_pos;
        real_pos.x = 32 * _pos.x - 16;
        real_pos.y = 22 * _pos.y - 16;
        if (_pos.y % 2 != 0) {
            real_pos.x += 16;
        }
        return real_pos;
    }

    Cell::~Cell() {
        delete _env;
    }
} // game