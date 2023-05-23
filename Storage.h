//
// Created by Yulia on 18.05.2023.
//

#ifndef AHR_STORAGE_H
#define AHR_STORAGE_H

#include <string>

class Storage;
#include "Model.h"

class Storage {
public:
    bool loadFromFile(const std::string& path, Model& model);

    bool saveToFile(const std::string& path);
};

#endif //AHR_STORAGE_H
