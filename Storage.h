//
// Created by Yulia on 18.05.2023.
//

#ifndef AHR_STORAGE_H
#define AHR_STORAGE_H

#include <string>

class Storage;
#include "Model.h"

// singleton class of storage
class Storage {
public:
    static Storage& getInstance(){
        static Storage storage = Storage();
        return storage;
    }

    bool loadFromFile(const std::string& path, Model& model);

    bool saveToFile(const std::string& path, const Model& model);
private:
    Storage() = default;
    Storage(Storage&& st) = default;
    ~Storage() = default;

    Storage& operator=( Storage&) = default;
};

#endif //AHR_STORAGE_H
