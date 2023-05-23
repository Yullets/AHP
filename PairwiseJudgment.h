//
// Created by Yulia on 18.05.2023.
//

#ifndef AHR_PAIRWISEJUDGMENT_H
#define AHR_PAIRWISEJUDGMENT_H

#include "Judgment.h"

class PairwiseJudgment: public Judgment {
public:
    const ID_t &getFirstNodeId() const;

    void setFirstNodeId(const ID_t &firstNodeId);

    const ID_t &getSecondNodeId() const;

    void setSecondNodeId(const ID_t &secondNodeId);

    double getValue() const;

    void setValue(double value);

private:
    ID_t firstNodeID;
    ID_t secondNodeID;
    double value;
};

#endif //AHR_PAIRWISEJUDGMENT_H
