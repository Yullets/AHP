//
// Created by Yulia on 18.05.2023.
//

#include "PairwiseJudgment.h"

const ID_t &PairwiseJudgment::getFirstNodeId() const {
    return firstNodeID;
}

void PairwiseJudgment::setFirstNodeId(const ID_t &firstNodeId) {
    firstNodeID = firstNodeId;
}

const ID_t &PairwiseJudgment::getSecondNodeId() const {
    return secondNodeID;
}

void PairwiseJudgment::setSecondNodeId(const ID_t &secondNodeId) {
    secondNodeID = secondNodeId;
}

double PairwiseJudgment::getValue() const {
    return value;
}

void PairwiseJudgment::setValue(double value) {
    PairwiseJudgment::value = value;
}
