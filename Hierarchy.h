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
#include "Model.h"

class Hierarchy : public CommonObject {
public:
    Hierarchy(Model *m);

    Hierarchy();

    Node *addNode(Node *parent);

    bool deleteNode(ID_t id);

    [[nodiscard]]
    Node *getNodeByID(ID_t id);

    [[nodiscard]]
    const std::map<ID_t, Node *> & getNodes() const;

    void setNodes(const std::map<ID_t, Node *> &nodes);
    void setNodes(const std::vector<Node*>& nodes);

    Model *getModel();

    void setModel(Model *model);

    void setRoot(ID_t id);
    [[nodiscard]]
    Node* getRoot();

    void calculateGlobalPriorities(Node *node);

    std::map<ID_t, Node*> getTerminalNodes();

    void calculateLocalPriorities(Node *node);

private:
    std::map<ID_t, Node *> nodes;
    Node *root = nullptr;
    Model *model = nullptr;
};

#endif //AHR_HIERARCHY_H
