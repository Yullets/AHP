//
// Created by Yulia on 18.05.2023.
//

#ifndef AHR_MODEL_H
#define AHR_MODEL_H

class Model;

#include "Hierarchy.h"
#include "Alternative.h"
#include "User.h"
#include "Storage.h"

class Model : public CommonObject {
public:
    Model();

    Model(ID_t id, const std::string &name, const std::string &comment);

    Hierarchy* getHierarchy() const;

    void setHierarchy(Hierarchy* hierarchy);

    std::map<ID_t, Alternative>& getAlternatives() ;

    void setAlternatives(const std::map<ID_t, Alternative>& alternatives);
    void addElternative(const Alternative& alternative);


    const std::map<ID_t, User*>& getUsers() const;

    void setUsers(const std::map<ID_t, User*>& users);

    //    Storage* getStorage() const;

    //    void setStorage(Storage* storage);

    void calculateGlobalPrioritiesForAlternatives();

private:
    Hierarchy* hierarchy;
    std::map<ID_t, Alternative> alternatives;
    std::map<ID_t, User*>       users;
};

#endif //AHR_MODEL_H
