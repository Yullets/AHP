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

    const std::map<ID_t, double> &getLocalPriorities() const;

    void setLocalPriorities(const std::map<ID_t, double> &localPriorities);

    double getGlobalPriority() const;

    void setGlobalPriority(double globalPriority);

    void setOneLocalPriority(std::pair<ID_t, double> &localPriority);

private:
    std::map<ID_t, Node*> parents;
    std::map<ID_t, double> localPriorities = {};
    double globalPriority = 0;
};


#endif //AHR_ALTERNATIVE_H
