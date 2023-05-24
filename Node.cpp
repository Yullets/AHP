//
// Created by Yulia on 18.05.2023.
//

#include <map>

#include "Node.h"

Node *Node::getParent() const {
    return parent;
}

void Node::setParent(Node *parent) {
    Node::parent = parent;
}

const std::map<ID_t, Node *> &Node::getChildren() const {
    return children;
}

void Node::setChildren(const std::map<ID_t, Node *> &children) {
    Node::children = children;
}

void Node::setChildren(const std::vector<Node *> children)
{
    std::map<ID_t, Node*> childrenMap;
    for(auto& child : children){
        childrenMap[child->getId()] = child;
    }
    Node::children = childrenMap;
}

Judgments& Node::getJudgments() {
    return *judgments;
}

void Node::removeChild(const ID_t id) {
    children.erase(id);
}

void Node::addChild(Node *child) {
    children.insert({child->getId(), child});
}

Node::Node(ID_t id, Node* parent, Hierarchy* hierarchy) :
    CommonObject(id),
    parent(parent),
    hierarchy(hierarchy) {
    judgments = std::make_shared<Judgments>(this);
}

void Node::calculateLocalPriorities(ID_t UserID) {
    matrix::Matrix<double> m = judgments->getJudgmentsMatrix(UserID);
    judgments->getEigenCalculator()->setPairwiseMatrix(m);

    matrix::Matrix<int> res = judgments->getEigenCalculator()->getBinaryMatrix();
    Graph<int> g(res);
    std::vector<double> eigenVector;
    double lambda;
//    if(g.isConnectedGraph()) {
//        judgments->getEigenCalculator()->calculateEigenVector(eigenVector, lambda, 0.1, 50);
//    }

    judgments->getEigenCalculator()->calculateEigenVector(eigenVector, lambda, 0.1, 50);
    if(!getChildren().empty()) {
        setLocalPrioritiesForChildren(eigenVector);
    } else {
        setLocalPrioritiesForAlternative(eigenVector);
    }
}

void Node::setLocalPrioritiesForChildren(std::vector<double> &eigenVector) {
    int index = 0;
    for(auto &child: this->getChildren()) {
        child.second->localPriority = eigenVector[index++];
    }
}

void Node::setLocalPrioritiesForAlternative(std::vector<double> &eigenVector) {
    std::map<ID_t, Alternative> &alternative = this->getHierarchy()->getModel()->getAlternatives();
    ID_t nodeID = getId();

    int index = 0;
    for(auto &pair: alternative) {
        std::pair<ID_t, double> onePriority = {nodeID, eigenVector[index++]};
//        pair.second.getLocalPriorities().insert(onePriority);
        pair.second.setOneLocalPriority(onePriority);
    }
}

Hierarchy *Node::getHierarchy() const
{
    return hierarchy;
}

void Node::setHierarchy(Hierarchy *newHierarchy)
{
    hierarchy = newHierarchy;
}

double Node::getGlobalPriority() const {
    return globalPriority;
}

void Node::setGlobalPriority(double globalPriority) {
    Node::globalPriority = globalPriority;
}

double Node::getLocalPriority() const {
    return localPriority;
}

void Node::setLocalPriority(double localPriority) {
    Node::localPriority = localPriority;
}
