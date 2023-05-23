//
// Created by Yulia on 18.05.2023.
//

#include "User.h"

User::User(ID_t id,
           const std::string &name,
           const std::string &comment) :
    CommonObject(id, name, comment) {

}

double User::getWeight() const {
    return weight;
}

void User::setWeight(double weight) {
    User::weight = weight;
}

const std::string& User::getEmail() const {
    return email;
}

void User::setEmail(const std::string& email) {
    User::email = email;
}


