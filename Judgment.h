//
// Created by Yulia on 18.05.2023.
//

#ifndef AHR_JUDGMENT_H
#define AHR_JUDGMENT_H

class Judgment;

#include <windows.h>
#include <chrono>
#include <string>

#include "IDGenerator.hpp"

class Judgment {
public:
    const ID_t& getUserId() const;

    void setUserId(const ID_t& userId);

    time_t getModifyDate() const;

    void setModifyDate(time_t modifyDate);

    const std::string& getComment() const;

    void setComment(const std::string& comment);

private:
    ID_t        userID;
    time_t      modifyDate;
    std::string comment;
};

#endif //AHR_JUDGMENT_H
