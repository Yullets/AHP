//
// Created by Yulia on 18.05.2023.
//

#ifndef AHR_EIGENCALCULATOR_H
#define AHR_EIGENCALCULATOR_H

class EigenCalculator;

#include <vector>

#include "matrix.hpp"

class EigenCalculator {
public:
    using matrix_t = matrix::Matrix<double>;
    using math_vector = matrix_t::Row;
    using eigen_vector = math_vector;

    const matrix_t& getPairwiseMatrix() const;

    void setPairwiseMatrix(const matrix_t& pairwiseMatrix);

    int getMatrixSize() const;

    void setMatrixSize(int matrixSize);

    void calculateEigenVector(eigen_vector& vector, double& lambdaMax, double eps, int maxIterations);

    double getInconsistencyIndex() const;

    matrix::Matrix<int> getBinaryMatrix();

private:
    matrix_t pairwiseMatrix;
    int    matrixSize;

    double lambdaMax          = -1;
    double inconsistencyIndex = -1;


};

#endif //AHR_EIGENCALCULATOR_H
