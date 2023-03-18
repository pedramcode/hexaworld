//
// Created by pedram on 3/17/23.
//

#include "GameState.h"


namespace game {
    GameState::GameState(Game *game) : AbstractState(game) {
        _center_view.x = 0;
        _center_view.y = 0;
        auto win_size = _game->get_window()->getSize();
        _size_view.x = win_size.x / 2;
        _size_view.y = win_size.y / 2;

//        auto rnd_noise = [](double v, int range) -> double {
//            int min = -range;
//            int max = range;
//            double randNum = rand() % (max - min + 1) + min;
//            return v + randNum;
//        };


//        double hm = rand() % (100 - 0 + 1) + 0;
//        double hg = rand() % (1000 - 0 + 1) + 0;
//        double tm = rand() % (100 - 0 + 1) + 0;
//
//        int W = 200;
//        int H = 200;
//        int x = 0;
//        int y = 0;
//        int dx = 0;
//        int dy = -1;

        // Spiral loop
        // pow should be MAX(W,H)
//        for (int i = 0; i < pow(W, 2); i++) {
//            if ((-W / 2 < x <= W / 2) && (-H / 2 < y <= H / 2)) {
//                Cell *cell = nullptr;
//                hm = rnd_noise(hm, 10);
//                hg = rnd_noise(hg, 100);
//                tm = rnd_noise(tm, 10);
//                auto env = new Env(hm, hg, tm);
//                auto selected_biome = _get_env_type(env);
//                cell = new Cell(selected_biome, _biome_to_texture(selected_biome), sf::Vector2i(x, y), env);
//                _grid.push_back(cell);
//            }
//            if (x == y || (x < 0 and x == -y) || (x > 0 and x == 1 - y)) {
//                int tmp = dx;
//                dx = -dy;
//                dy = tmp;
//            }
//            x = x + dx;
//            y = y + dy;
//        }

        const siv::PerlinNoise::seed_type seed = 1234u;
        const siv::PerlinNoise perlin{seed};

        for (int y = -100; y < 100; y++) {
            for (int x = -100; x < 100; x++) {
                double hm = perlin.octave2D_01((x * 0.01), (y * 0.01), 4) * 100;
                double ht = perlin.octave2D_01((x * 0.03), (y * 0.04), 4) * 10000;
                double tm = perlin.octave2D_01((x * 0.06), (y * 0.02), 4) * 100;
                auto env = new Env(hm, ht, tm);
                auto selected_biome = _get_env_type(env);
                auto *cell = new Cell(selected_biome, _biome_to_texture(selected_biome), sf::Vector2i(x, y), env);
                _grid.push_back(cell);
            }
        }

        _paused = false;
    }

    GameState::~GameState() {
        for (auto cell: _grid) {
            delete cell;
        }
    }

    void GameState::render() {
        _game->get_window()->setView(_view);
        const int offset_visible = 30;
        for (auto cell: _grid) {
            auto pos = cell->get_real_pos();
            if (pos.x >= _center_view.x - _size_view.x / 2 - offset_visible &&
                pos.x <= _center_view.x + _size_view.x / 2 + offset_visible &&
                pos.y >= _center_view.y - _size_view.y / 2 - offset_visible &&
                pos.y <= _center_view.y + _size_view.y / 2 + offset_visible) {
                _game->get_window()->draw(*cell);
            }
        }
    }

    void GameState::update() {
        _paused = !_game->get_window()->hasFocus();
        if (!_paused) {
            auto win_size = _game->get_window()->getSize();

            float speed = 3;
            float size_speed_x = win_size.x / 100;
            float size_speed_y = win_size.y / 100;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
                speed *= 3;
                size_speed_x *= 5;
                size_speed_y *= 5;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                _center_view.x -= speed;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                _center_view.y -= speed;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                _center_view.x += speed;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                _center_view.y += speed;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
                _size_view.x = win_size.x / 2;
                _size_view.y = win_size.y / 2;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                if (_size_view.x <= win_size.x / 5 || _size_view.y <= win_size.y / 5) {
                    _size_view.x = win_size.x / 5;
                    _size_view.y = win_size.y / 5;
                } else {
                    _size_view.x -= size_speed_x;
                    _size_view.y -= size_speed_y;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
                if (_size_view.x >= win_size.x * 1.5 || _size_view.y >= win_size.y * 1.5) {
                    _size_view.x = win_size.x * 1.5;
                    _size_view.y = win_size.y * 1.5;
                } else {
                    _size_view.x += size_speed_x;
                    _size_view.y += size_speed_y;
                }
            }
            _view.setCenter(_center_view.x, _center_view.y);
            _view.setSize(_size_view.x, _size_view.y);
        }
    }

    const sf::Texture *GameState::_biome_to_texture(BiomeType type) {
        switch (type) {

            case DEEP_SEA:
                return _game->textures.get("deep_sea");
            case SHALLOW_SEA:
                return _game->textures.get("shallow_sea");
            case JUNGLE:
                return _game->textures.get("jungle");
            case GRASS:
                return _game->textures.get("grass");
            case BEACH:
                return _game->textures.get("beach");
            case SWAMP:
                return _game->textures.get("swamp");
            case MOUNTAINS:
                return _game->textures.get("mountains");
            case DESERT:
                return _game->textures.get("desert");
            case SNOWY:
                return _game->textures.get("snowy");
            case CANYON:
                return _game->textures.get("canyon");
            case GRASS_VILLAGE:
                return _game->textures.get("grass_village");
            case SNOW_VILLAGE:
                return _game->textures.get("snow_village");
            case TAIGA:
                return _game->textures.get("taiga");
        }
        return nullptr;
    }

    BiomeType GameState::_get_env_type(Env *env) {
        const int len = 13;
        BiomeType biomes[len] = {
                JUNGLE, SWAMP, DESERT, MOUNTAINS, SHALLOW_SEA, DEEP_SEA, GRASS, BEACH, CANYON, SNOWY, GRASS_VILLAGE,
                SNOW_VILLAGE, TAIGA
        };
        int min_index = 0;
        double min_value = INT32_MAX;
        for (int i = 0; i < len; i++) {
            auto benv = get_biome_env(biomes[i]);
            double score = sqrt(pow(env->humidity - benv.humidity, 2) +
                                pow(env->height - benv.height, 2) +
                                pow(env->temp - benv.temp, 2));
            if (score < min_value) {
                min_index = i;
                min_value = score;
            }
        }
        return biomes[min_index];
    }

} // game