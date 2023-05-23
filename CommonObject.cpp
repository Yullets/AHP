
#include <guiddef.h>
#include "CommonObject.h"

ID_t CommonObject::getId() const {
    return ID;
}

const std::string &CommonObject::getName() const {
    return name;
}

const std::string &CommonObject::getComment() const {
    return comment;
}

void CommonObject::setId(const ID_t &id) {
    ID = id;
}

void CommonObject::setName(const std::string &name) {
    CommonObject::name = name;
}

void CommonObject::setComment(const std::string &comment) {
    CommonObject::comment = comment;
}

CommonObject::CommonObject(ID_t id) : ID(id) {

}

CommonObject::CommonObject(ID_t id,
                           const std::string &name,
                           const std::string &comment) : ID(id), name(name),
                                                         comment(comment) {}

CommonObject::CommonObject() {}
