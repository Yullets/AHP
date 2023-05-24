//
// Created by Yulia on 18.05.2023.
//

#ifndef AHR_NODE_H
#define AHR_NODE_H

#include <memory>
#include <memory>

class Node;
#include <map>
#include "CommonObject.h"
#include "Judgments.h"
#include "Hierarchy.h"
#include "graph.hpp"
#include "Alternative.h"

class Node : public CommonObject {
public:
    explicit Node(ID_t id,
                  Node* parent = nullptr,
                  Hierarchy* hierarchy = nullptr);

    [[nodiscard]] Node* getParent() const;

    void setParent(Node* parent);

    [[nodiscard]] const std::map<ID_t, Node*>& getChildren() const;

    void setChildren(const std::map<ID_t, Node*>& children);
    void setChildren(const std::vector<Node*> children);

    double getLocalPriority() const;

    void setLocalPriority(double localPriority);

    double getGlobalPriority() const;

    void setGlobalPriority(double globalPriority);

    void addChild(Node* child);

    void removeChild(ID_t id);



    [[nodiscard]]
    Judgments& getJudgments();

    void calculateLocalPriorities(ID_t UserID);

    Hierarchy *getHierarchy() const;
    void setHierarchy(Hierarchy *newHierarchy);

    void getLocalPriorities(ID_t UserID);

    void setLocalPrioritiesForChildren(std::vector<double> &eigenVector);

    void setLocalPrioritiesForAlternative(std::vector<double> &eigenVector);

private:
    Node* parent;
    std::map<ID_t, Node*> children;
    Hierarchy* hierarchy;
    double localPriority = 0;
    double globalPriority = 0;

    std::shared_ptr<Judgments> judgments;
};

#endif //AHR_NODE_H
