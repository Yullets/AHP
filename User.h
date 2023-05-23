//
// Created by Yulia on 18.05.2023.
//

#ifndef AHR_USER_H
#define AHR_USER_H

#include "CommonObject.h"

class User : public CommonObject {
public:
   User(ID_t id, const std::string &name, const std::string &comment);

    double getWeight() const;

    void setWeight(double weight);

    const std::string& getEmail() const;

    void setEmail(const std::string& email);

private:
    double      weight;
    std::string email;
};

#endif //AHR_USER_H
