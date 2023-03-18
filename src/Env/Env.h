//
// Created by pedram on 3/18/23.
//

#ifndef GAME_ENV_H
#define GAME_ENV_H

namespace game {

    class Env {
    public:
        Env(double _humidity, double _height, double _temp);

        double humidity;
        double height;
        double temp;
    };

} // game

#endif //GAME_ENV_H
