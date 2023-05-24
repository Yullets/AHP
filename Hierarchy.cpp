//
// Created by Yulia on 18.05.2023.
//

#include "Hierarchy.h"

Node *Hierarchy::addNode(Node *parent) {
    if (parent == nullptr && root != nullptr) {
        throw std::invalid_argument("root has already been added");
    }

    if (parent != nullptr && !nodes.contains(parent->getId())) {
        throw std::invalid_argument("parent is not found");
    }

    Node *createdNode = new Node(IDGenerator::getNewId(), parent, this);

    if (root == nullptr) {
        root = createdNode;
    }

    if (parent != nullptr) {
        parent->addChild(createdNode);
    }

    return createdNode;
}

bool Hierarchy::deleteNode(ID_t id) {
    if (!getNodeByID(id)) {
        return false;
    }

    Node *curNode = getNodeByID(id);

    for (auto &child: curNode->getChildren()) {
        deleteNode(child.first);
        curNode->removeChild(child.first);
        Node *parent = curNode->getParent();

        for (auto &judgments: parent->getJudgments().getJudgments()) {
            erase_if(judgments.second, [id](PairwiseJudgment &judgment) -> bool {
                return judgment.getFirstNodeId() == id ||
                        judgment.getSecondNodeId() == id;
            });
        }
    }

    nodes.erase(id);
    if (id == root->getId()) {
        root = nullptr;
    }

    delete curNode;

    return true;
}

Node *Hierarchy::getNodeByID(ID_t id) {
    return nodes.contains(id) ? nodes[id] : nullptr;
}

const std::map<ID_t, Node *> &Hierarchy::getNodes() const {
    return nodes;
}

void Hierarchy::setNodes(const std::map<ID_t, Node *> &nodes) {
    Hierarchy::nodes = nodes;
}

void Hierarchy::setNodes(const std::vector<Node *> &nodes)
{
    std::map<ID_t, Node*> nodesMap;
    for(auto& node: nodes){
        nodesMap[node->getId()] = node;
    }

    Hierarchy::nodes = nodesMap;
}

void Hierarchy::setRoot(ID_t id)
{
    if(nodes.contains(id)){
        Hierarchy::root =  nodes[id];
        return;
    }

    throw std::invalid_argument("node is not in hierarchy");
}

Node *Hierarchy::getRoot()
{
    return root;
}

void Hierarchy::calculateGlobalPriorities(Node *node) {
    if(node->getId() == root->getId()) {
        root->setGlobalPriority(1);
    } else {
        node->setGlobalPriority(node->getLocalPriority() * node->getParent()->getGlobalPriority());
    }

    for(auto &child: node->getChildren()) {
        calculateGlobalPriorities(child.second);
    }
}

Hierarchy::Hierarchy(Model* m) {
    model = m;
}

Model *Hierarchy::getModel() {
    return model;
}

std::map<ID_t, Node *> Hierarchy::getTerminalNodes() {
    std::map<ID_t, Node*> terminalNodes;

    for(auto &node: nodes) {
        if(node.second->getChildren().empty()) {
            terminalNodes.insert(node);
        }
    }

    return terminalNodes;
}

void Hierarchy::calculateLocalPriorities(Node *node)
{
    node->calculateLocalPriorities(1);
    for(auto &child: node->getChildren()) {
        child.second->calculateLocalPriorities(1);
    }
}

