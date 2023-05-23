//
// Created by vladv on 18.05.2023.
//

#ifndef AHR_IDGENERATOR_HPP
#define AHR_IDGENERATOR_HPP


#include <cstddef>

using ID_t = std::size_t;

class IDGenerator {
public:
    static ID_t getNewId() {
        static ID_t nextId = 0;
        return nextId++;
    }
};


#endif //AHR_IDGENERATOR_HPP
