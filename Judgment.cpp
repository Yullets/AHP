//
// Created by Yulia on 18.05.2023.
//

#include "Judgment.h"

const ID_t &Judgment::getUserId() const {
    return userID;
}

void Judgment::setUserId(const ID_t &userId) {
    userID = userId;
}

time_t Judgment::getModifyDate() const {
    return modifyDate;
}

void Judgment::setModifyDate(time_t modifyDate) {
    Judgment::modifyDate = modifyDate;
}

const std::string &Judgment::getComment() const {
    return comment;
}

void Judgment::setComment(const std::string &comment) {
    Judgment::comment = comment;
}

