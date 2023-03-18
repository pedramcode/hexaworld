//
// Created by pedram on 3/17/23.
//

#include "Game.h"

namespace game {
    void Game::_load_assets() {
        std::map<std::string, std::string> texture_data;
        texture_data.emplace("beach", "./assets/textures/beach.png");
        texture_data.emplace("grass", "./assets/textures/grass.png");
        texture_data.emplace("jungle", "./assets/textures/jungle.png");
        texture_data.emplace("deep_sea", "./assets/textures/deep_sea.png");
        texture_data.emplace("shallow_sea", "./assets/textures/shallow_sea.png");
        texture_data.emplace("swamp", "./assets/textures/swamp.png");
        texture_data.emplace("mountains", "./assets/textures/mountains.png");
        texture_data.emplace("desert", "./assets/textures/desert.png");
        texture_data.emplace("canyon", "./assets/textures/canyon.png");
        texture_data.emplace("snowy", "./assets/textures/snaowy.png");
        texture_data.emplace("grass_village", "./assets/textures/grass_village.png");
        texture_data.emplace("snow_village", "./assets/textures/snow_village.png");
        texture_data.emplace("taiga", "./assets/textures/tiga.png");

        for (auto item: texture_data) {
            sf::Texture *texture = new sf::Texture();
            texture->loadFromFile(item.second);
            this->textures.store(item.first, texture);
        }
    }

    void Game::_init_states() {
        GameState *game_state = new GameState(this);
        this->push_state(game_state);
    }

    Game::Game() {
        srand(324);

        this->_window = new sf::RenderWindow();
        this->_window->create(sf::VideoMode(800, 600), "Game", sf::Style::Titlebar | sf::Style::Close);
        this->_window->setVerticalSyncEnabled(true);
        auto windowSize = sf::VideoMode::getDesktopMode();
        auto _pos = sf::Vector2i(windowSize.width / 2 - this->_window->getSize().x / 2,
                                 windowSize.height / 2 - this->_window->getSize().y / 2);
        this->_window->setPosition(_pos);

        this->_load_assets();
        this->_init_states();
    }

    Game::~Game() {
        while (!this->_states.empty()) {
            auto *tmp = this->_states.top();
            this->_states.pop();
            delete tmp;
        }
        delete this->_window;
    }

    sf::RenderWindow *Game::get_window() {
        return this->_window;
    }

    void Game::push_state(AbstractState *state) {
        this->_states.push(state);
    }

    void Game::pop_state() {
        this->_states.pop();
    }

    void Game::main_loop() {
        if (!this->_window) return;
        while (this->_window->isOpen()) {
            sf::Event event{};
            while (this->_window->pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    this->_window->close();
                }
            }

            this->_window->clear(sf::Color::Black);
            if (!this->_states.empty()) {
                this->_states.top()->update();
                this->_states.top()->render();
            }
            this->_window->display();
        }
    }


} // game