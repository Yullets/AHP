//
// Created by Yulia on 18.05.2023.
//

#include "Model.h"

Model::Model() {
    hierarchy = new Hierarchy(this);
}

Model::Model(ID_t id, const std::string &name, const std::string &comment) : CommonObject(id, name, comment) {
    Model();
}

Hierarchy* Model::getHierarchy() const {
    return hierarchy;
}

void Model::setHierarchy(Hierarchy* hierarchy) {
    Model::hierarchy = hierarchy;
}

std::map<ID_t, Alternative>& Model::getAlternatives(){
    return alternatives;
}

void Model::setAlternatives(const std::map<ID_t, Alternative>& alternatives) {
    Model::alternatives = alternatives;
}

void Model::addElternative(const Alternative &alternative)
{
    alternatives.insert({alternative.getId(), alternative});
}

const std::map<ID_t, User*>& Model::getUsers() const {
    return users;
}

void Model::setUsers(const std::map<ID_t, User*>& users) {
    Model::users = users;
}

//Storage* Model::getStorage() const {
//    return storage;
//}

//void Model::setStorage(Storage* storage) {
//    Model::storage = storage;
//}

void Model::calculateGlobalPrioritiesForAlternatives() {
    std::map<ID_t, Node*> terminateNodes = hierarchy->getTerminalNodes();

    for(auto &alternative: alternatives) {
        double globalPriority = 0;
        std::map<ID_t, double> alternativeLocalPriorities = alternative.second.getLocalPriorities();
        for(auto &terminateNode: terminateNodes) {
            globalPriority += alternativeLocalPriorities[terminateNode.first] * terminateNode.second->getGlobalPriority();
        }
        alternative.second.setGlobalPriority(globalPriority);
    }
}
