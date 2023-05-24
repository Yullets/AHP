//
// Created by Yulia on 18.05.2023.
//

#include <map>
#include <cassert>
#include "EigenCalculator.h"
#include "Judgments.h"

EigenCalculator* Judgments::getEigenCalculator() const {
    return eigenCalculator;
}

std::map<ID_t, std::vector<PairwiseJudgment>>& Judgments::getJudgments() {
    return judgments;
}

void Judgments::setJudgments(
        const std::map<ID_t, std::vector<PairwiseJudgment>>& judgments) {
    Judgments::judgments = judgments;
}

matrix::Matrix<double> Judgments::getJudgmentsMatrix(ID_t userID) {
    int n;
    if (parent->getChildren().empty()) n = getParent()->getHierarchy()->getModel()->getAlternatives().size();
    else n = parent->getChildren().size();
    matrix::Matrix<double> m(n, n);

    std::map<ID_t, int> indexes;
    {
        int      index = 0;
        if(parent->getChildren().empty()) {
            for(auto& alternative: getParent()->getHierarchy()->getModel()->getAlternatives()) {
                indexes.insert({alternative.first, index++});
            }
        } else {
            for (auto& child: parent->getChildren()) {
                indexes.insert({child.first, index++});
            }
        }
    }

    for (auto judgment: getJudgments()) {
        for (auto& j: judgment.second) {
            auto index_1 = indexes[j.getFirstNodeId()];
            auto index_2 = indexes[j.getSecondNodeId()];
            if (j.getValue() > 0) {
                m[index_1][index_2] = j.getValue();
                m[index_2][index_1] = 1 / j.getValue();
            } else if (j.getValue() < 0) {
                m[index_2][index_1] = -j.getValue();
                m[index_1][index_2] = -1 / j.getValue();
            }
        }
    }

    for (int i = 0; i < m.nRows(); i++) {
        m(i, i) = 1;
    }

    eigenCalculator->setPairwiseMatrix(m);

    return m;
}

Judgments::Judgments(Node* parent) : parent(parent) {
    eigenCalculator = new EigenCalculator();
}

Node *Judgments::getParent() const {
    return parent;
}

void Judgments::setParent(Node *parent) {
    Judgments::parent = parent;
}
