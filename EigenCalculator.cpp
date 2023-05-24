//
// Created by Yulia on 18.05.2023.
//

#include <vector>
#include "EigenCalculator.h"

const EigenCalculator::matrix_t &
EigenCalculator::getPairwiseMatrix() const {
    return pairwiseMatrix;
}

void EigenCalculator::setPairwiseMatrix(
        const matrix_t &pairwiseMatrix) {
    EigenCalculator::pairwiseMatrix = pairwiseMatrix;
    matrixSize = getMatrixSize();
}

int EigenCalculator::getMatrixSize() const {
    return pairwiseMatrix.nRows();
}

void
EigenCalculator::calculateEigenVector
        (EigenCalculator::eigen_vector &vector,
         double &lambdaMax, double eps, int maxIterations) {

    eigen_vector curVec(matrixSize);
    eigen_vector prevVec(matrixSize);

    bool flag = false;
    while (!flag && maxIterations-- > 0) {
        for (int i = 0; i < matrixSize; i++) {
            double rowSum = 0;
            for (auto &colValue: pairwiseMatrix(i)) {
                rowSum += colValue;
            }
            curVec[i] = rowSum;
        }

        double vectorSum = 0;
        for (auto &el: curVec) {
            vectorSum += el;
        }

        for (auto &el: curVec) {
            el /= vectorSum;
        }

        pairwiseMatrix *= pairwiseMatrix;

        flag = true;
        for(int i = 0; i < curVec.size() && flag; i++) {
            if(std::abs(curVec[i] - prevVec[i]) > eps) {
                flag = false;
            }
        }

        prevVec = curVec;
    }

    vector = curVec;
}

double EigenCalculator::getInconsistencyIndex() const {
    return (lambdaMax == -1) ? lambdaMax : (lambdaMax - matrixSize) / (matrixSize - 1);
}

matrix::Matrix<int> EigenCalculator::getBinaryMatrix() {
    matrix::Matrix<int> copy(matrixSize, matrixSize);

    for(int i = 0; i < matrixSize; i++) {
        for(int j = 0; j < matrixSize; j++) {
            if(pairwiseMatrix(i, j) > 0) {
                copy(i, j) = 1;
            }
        }
    }

    return copy;
}
