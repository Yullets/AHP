//
// Created by Yulia on 18.05.2023.
//

#ifndef AHR_COMMONOBJECT_H
#define AHR_COMMONOBJECT_H

#include <windows.h>
#include <string>
#include "IDGenerator.hpp"

class CommonObject {
public:
    CommonObject();

    explicit CommonObject(ID_t id);

    CommonObject(ID_t id,
                 const std::string &name,
                 const std::string &comment);

    ID_t getId() const;

    const std::string &getName() const;

    const std::string &getComment() const;

    void setId(const ID_t &id);

    void setName(const std::string &name);

    void setComment(const std::string &comment);

private:
    ID_t ID;
    std::string name = "";
    std::string comment = "";
};

#endif //AHR_COMMONOBJECT_H
