//
// Created by pedram on 3/17/23.
//

#ifndef GAME_COLLECTION_HPP
#define GAME_COLLECTION_HPP

#include <string>
#include <vector>

namespace game {

    template<typename T>
    struct collection_struct {
        T *content;
        std::string name;
    };

    template<typename T>
    class Collection {
    private:
        std::vector<struct collection_struct<T> *> _data;
    public:
        Collection();

        ~Collection();

        void store(std::string name, T *content);

        const T *get(std::string name);
    };

    template<typename T>
    Collection<T>::Collection() = default;

    template<typename T>
    Collection<T>::~Collection() {
        for (auto item: this->_data) {
            delete item;
        }
    }

    template<typename T>
    void Collection<T>::store(std::string name, T *content) {
        struct collection_struct<T> *data = new struct collection_struct<T>();
        data->name = name;
        data->content = content;
        this->_data.push_back(data);
    }

    template<typename T>
    const T *Collection<T>::get(std::string name) {
        for (struct collection_struct<T> *item: this->_data) {
            if (item->name == name) {
                return item->content;
            }
        }
        return nullptr;
    }


} // game

#endif //GAME_COLLECTION_HPP
