//
// Created by pedram on 3/17/23.
//

#ifndef GAME_CELL_H
#define GAME_CELL_H

#include <SFML/Graphics.hpp>
#include "Env/Env.h"

namespace game {

    typedef enum cell_biome_type {
        DEEP_SEA,
        SHALLOW_SEA,
        JUNGLE,
        GRASS,
        BEACH,
        SWAMP,
        MOUNTAINS,
        DESERT,
        CANYON,
        SNOWY,
        GRASS_VILLAGE,
        SNOW_VILLAGE,
        TAIGA,
    } BiomeType;

    Env get_biome_env(BiomeType type);

    class Cell : public sf::Drawable, public sf::Transformable {
    private:
        sf::Vector2i _pos;
        BiomeType _type;
        const sf::Texture *_texture;
        sf::Sprite _sprite;
        Env *_env;
    public:
        Cell(BiomeType type, const sf::Texture *texture, sf::Vector2i pos, Env *env);
        ~Cell();

        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
        sf::Vector2f get_real_pos();
    };

} // game

#endif //GAME_CELL_H
