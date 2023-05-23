//
// Created by Yulia on 18.05.2023.
//

#ifndef AHR_ALTERNATIVE_H
#define AHR_ALTERNATIVE_H

class Alternative;

#include <map>

#include "CommonObject.h"
#include "Node.h"

class Alternative : public CommonObject {
public:
    const std::map<ID_t, Node*>& getParents() const;

    void setParents(const std::map<ID_t, Node*>& parents);

private:
    std::map<ID_t, Node*> parents;
};


#endif //AHR_ALTERNATIVE_H
