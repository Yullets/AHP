//
// Created by Yulia on 18.05.2023.
//

#include "Alternative.h"

const std::map<ID_t, Node*>& Alternative::getParents() const {
    return parents;
}

void Alternative::setParents(const std::map<ID_t, Node*>& parents) {
    Alternative::parents = parents;
}
