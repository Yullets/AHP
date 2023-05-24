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

const std::map<ID_t, double> &Alternative::getLocalPriorities() const {
    return localPriorities;
}

void Alternative::setLocalPriorities(const std::map<ID_t, double> &localPriorities) {
    Alternative::localPriorities = localPriorities;
}

double Alternative::getGlobalPriority() const {
    return globalPriority;
}

void Alternative::setGlobalPriority(double globalPriority) {
    Alternative::globalPriority = globalPriority;
}

void Alternative::setOneLocalPriority(std::pair<ID_t, double> &localPriority) {
    localPriorities.insert(localPriority);
}
