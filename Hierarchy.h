//
// Created by Yulia on 18.05.2023.
//

#ifndef AHR_HIERARCHY_H
#define AHR_HIERARCHY_H

class Hierarchy;

#include <map>
#include "CommonObject.h"
#include "Node.h"
#include "IDGenerator.hpp"

class Hierarchy : public CommonObject {
public:
    Node *addNode(Node *parent);

    bool deleteNode(ID_t id);

    [[nodiscard]]
    Node *getNodeByID(ID_t id);

    [[nodiscard]]
    const std::map<ID_t, Node *> & getNodes() const;

    void setNodes(const std::map<ID_t, Node *> &nodes);
    void setNodes(const std::vector<Node*>& nodes);

    void setRoot(ID_t id);
    [[nodiscard]]
    Node* getRoot();

    void calculateGlobalPriorities(Node *node);

private:
    std::map<ID_t, Node *> nodes;
    Node *root = nullptr;
};

#endif //AHR_HIERARCHY_H
