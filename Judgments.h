//
// Created by Yulia on 18.05.2023.
//

#ifndef AHR_JUDGMENTS_H
#define AHR_JUDGMENTS_H

class Judgments;

#include "EigenCalculator.h"
#include "PairwiseJudgment.h"
#include "Node.h"


class Judgments {
public:
    Judgments(Node* parent);

    EigenCalculator* getEigenCalculator() const;

    void setEigenCalculator(EigenCalculator* eigenCalculator);

    std::map<ID_t, std::vector<PairwiseJudgment>>& getJudgments();

    void setJudgments(
            const std::map<ID_t, std::vector<PairwiseJudgment>>& judgments);

    matrix::Matrix<double> getJudgmentsMatrix(ID_t userID);

private:
    EigenCalculator                               * eigenCalculator;
    std::map<ID_t, std::vector<PairwiseJudgment>> judgments;
    Node                                          * parent;
};

#endif //AHR_JUDGMENTS_H
