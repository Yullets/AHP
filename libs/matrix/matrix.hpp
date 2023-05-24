#ifndef MATRIX_MATRIX_HPP
#define MATRIX_MATRIX_HPP

#include <vector>
#include <stdexcept>
#include <iostream>
#include <iomanip>

namespace matrix {
    template<class T>
    concept ArithmeticOperations = requires(T m){
        m + m;
        m - m;
        m / m;
        m * m;
    };

    using Pos_t = std::pair<int, int>;

    template<class T, std::size_t H = 0, std::size_t W = 0> requires ArithmeticOperations<T>
    class Matrix : private std::vector<std::vector<T>> {
    public:
        using ValueType = T;
        using Reference = ValueType &;
        using ConstReference = const ValueType &;

        using Pointer = ValueType *;
        using ConstPointer = const ValueType *;

        using ValuesContainer = std::vector<std::vector<ValueType>>;
        using Row = std::vector<ValueType>;
        using SizeType = std::size_t;

        //region ctors
        explicit Matrix() : Matrix(H, W) {

        }

        Matrix(const SizeType nRows,
               const SizeType nCols) : ValuesContainer(nRows, Row(nCols)) {
            m_nRows = nRows;
            m_nCols = nCols;
//            (*this).assign(nRows, Row(nCols));
        }

        Matrix(const Row &data,
               const SizeType nRows,
               const SizeType nCols) : Matrix(data.begin(),
                                              data.end(),
                                              nRows,
                                              nCols) {
        }

        Matrix(const ValuesContainer &data,
               const SizeType nRows,
               const SizeType nCols) : Matrix(nRows,
                                              nCols) {

            // TODO: maybe copy function?
            for (auto row = 0; row < data.size(); row++) {
                for (auto col = 0; col < data[row].size(); col++) {
                    (*this)[row][col] = data[row][col];
                }
            }
        }

        Matrix(const std::initializer_list<T> &data,
               const SizeType nRows,
               const SizeType nCols) : Matrix(data.begin(),
                                              data.end(),
                                              nRows,
                                              nCols) {
        }

        template<class It = std::iterator<std::forward_iterator_tag, T>>
        Matrix(It begin,
               It end,
               SizeType nRows,
               SizeType nCols): Matrix(nRows,
                                       nCols) {
            auto &tmp = *this;
            for (int i = 0; i < nRows; i++) {
                for (int j = 0; j < nCols && begin != end; j++, begin++) {
                    tmp(i, j) = *begin;
                }
            }
        }

//        Matrix(const Matrix& matrix):Matrix(matrix.nRows(), matrix.nCols()) {
//            for(auto rowIndex = 0; rowIndex < matrix.nRows(); rowIndex++){
//                for(auto colIndex = 0; colIndex < matrix.nCols(); colIndex++){
//                    (*this)(rowIndex, colIndex) = matrix(rowIndex, colIndex);
//                }

//            }
//        }



        //endregion

        [[nodiscard]] SizeType nRows() const {
            return m_nRows;
        }

        [[nodiscard]] SizeType nCols() const {
            return m_nCols;
        }

        Row &operator[](SizeType index) noexcept {
            return ValuesContainer::operator[](index);
        }

        const Row &operator[](SizeType index) const noexcept {
            return ValuesContainer::operator[](index);
        }

        Row &operator()(SizeType row) {
            return (*this).at(row);
        }

        const Row &operator()(SizeType row) const {
            return (*this).at(row);
        }

        Reference operator()(SizeType row, SizeType col) {
            return (*this).at(row).at(col);
        }

        const T &operator()(SizeType row, SizeType col) const {
            return ValuesContainer::at(row).at(col);
        }

        void swapRows(const SizeType i, const SizeType j) {
            auto &tmp = *this;
            std::swap(tmp(i), tmp(j));
        }

        Matrix operator+(const Matrix &other) const {
            auto tmp = *this;
            tmp += other;
            return tmp;
        }

        Matrix &operator+=(const Matrix &other) {
            if (nCols() != other.nCols() ||
                nRows() != other.nRows()) {
                throw std::invalid_argument("it is impossible to add "
                                            "matrices of different orders");
            }

            auto &tmp = *this;

            for (int i = 0; i < nRows(); i++) {
                for (int j = 0; j < nCols(); j++) {
                    tmp(i, j) = tmp(i, j) + other(i, j);
                }
            }

            return tmp;
        }

        Matrix operator-(const Matrix &other) const {
            auto tmp = *this;
            tmp -= other;
            return tmp;
        }

        Matrix &operator-=(const Matrix &other) {
            auto &tmp = *this;
            tmp += (-other);
            return tmp;
        }

        Matrix operator-() const noexcept {
            auto tmp = *this;

            for (int i = 0; i < nRows(); i++) {
                for (int j = 0; j < nCols(); j++) {
                    tmp(i, j) = -tmp(i, j);
                }
            }

            return tmp;
        }

        Matrix &operator=(const Matrix &other) = default;

        bool operator==(const Matrix &rhs) const {
            return static_cast<const std::vector<std::vector<T>>>(*this) ==
                   static_cast<const std::vector<std::vector<T>>>(rhs) &&
                   m_nRows == rhs.m_nRows &&
                   m_nCols == rhs.m_nCols;
        }

        bool operator!=(const Matrix &rhs) const {
            return !(rhs == *this);
        }

        Matrix &operator*=(const Matrix &other) {
            if (nCols() != other.nRows())
                throw std::invalid_argument(
                        "invalid mul matrices: need n * m and m * k");

            auto &tmp = *this;
            Matrix res(nRows(), other.nCols());
            for (int i = 0; i < nRows(); i++) {
                for (int j = 0; j < other.nCols(); j++) {
                    for (int k = 0; k < nCols(); k++) {
                        res(i, j) += tmp(i, k) * other(k, j);
                    }
                }
            }
            return tmp = res;
        }

        Matrix operator*(Matrix &other) const {
            auto tmp = *this;
            return tmp *= other;
        }

        Matrix &operator*=(int value) {
            auto &tmp = *this;

            for (int i = 0; i < nRows(); i++) {
                for (int j = 0; j < nCols(); j++) {
                    tmp(i, j) *= value;
                }
            }
            return tmp;
        }

        Matrix operator*(int value) const {
            auto tmp = *this;
            return tmp *= value;
        }

        std::vector<T> column(SizeType col) {
            std::vector<T> column(nRows());

            auto &tmp = *this;
            for (auto row = 0; row < nRows(); row++) {
                column[row] = tmp(row, col);
            }

            return column;
        }

        std::vector<T> row(SizeType row) {
            auto &tmp = *this;
            return tmp(row);
        }

        void setColumn(const std::vector<T> &values, SizeType col) {
            auto &tmp = *this;
            for (auto row = 0; row < nRows(); row++) {
                tmp(row, col) = values[row];
            }
        }

        void setRow(const std::vector<T> &values, SizeType row) {
            auto &tmp = *this;
            for (auto col = 0; col < nCols(); col++) {
                tmp(row, col) = values[col];
            }
        }

        void removeRow(SizeType row) {
            if (row >= nRows()) {
                throw std::out_of_range("");
            }

            auto &tmp = *this;
            tmp.erase(tmp.begin() + row);
            m_nRows--;
        }

        void removeColumn(SizeType col) {
            if (col >= nCols()) {
                throw std::out_of_range("");
            }

            auto &tmp = *this;

            for (auto &row: tmp) {
                row.erase(row.begin() + col);
            }
            m_nCols--;
        }

        ValueType determinant() {
            if (!isSquare()) {
                throw std::invalid_argument("matrix_t not square");
            }

            SizeType countSwaps = 0;
            Matrix triangleMatrix = triangleGauss(countSwaps);

            T result = triangleMatrix(0, 0);

            for (int row = 1; row < nRows(); row++) {
                result *= triangleMatrix(row, row);
            }

            if (countSwaps % 2) {
                result = -result;
            }

            return result;
        }

        bool isSquare() {
            return nRows() == nCols();
        }

        Matrix triangle() {
            SizeType tmp;
            return triangleGauss(tmp);
        }

        Matrix inverse() {
            if (!isSquare()) throw std::invalid_argument("matrix_t not square");
            auto additional = getAdditionalWithIdentityPart(*this);

            auto triangle = additional.triangle();

            auto v = triangle.nCols();
            triangle.m_nCols = triangle.nRows();
            auto det = triangle.determinant();
            if (det == 0) throw std::invalid_argument("determinant is zero");
            triangle.m_nCols = v;

            auto &tmp = *this;
            Matrix koefMatrix(nRows(), nRows());

            for (auto row = 0; row < nRows(); row++) {
                for (auto col = 0; col < nRows(); col++) {
                    koefMatrix(row, col) = triangle(row, col);
                }
            }

            Matrix inverse(nRows(), nRows());

            for (auto col = additional.nRows();
                 col < additional.nCols();
                 col++) {
                auto column = triangle.column(col);

                auto inverseMatrixColumn = reverseGaussianStroke(koefMatrix,
                                                                 column);
                inverse.setColumn(inverseMatrixColumn, col % nCols());
            }

            return inverse;
        }

        void removeZeroRows() {
            std::vector<int> zeroRows;

            for (int row = 0; row < nRows(); row++) {
                if (isZeroRow(row)) {
                    removeRow(row);
                    row--;
                }
            }
        }

        bool isZeroRow(SizeType row) {
            auto &tmp = *this;
            for (int col = 0; col < nCols(); col++) {
                if (tmp(row, col) != 0) return false;
            }

            return true;
        }

        bool isIdentity() {
            if (!isSquare()) return false;
            auto &tmp = *this;
            for (int row = 0; row < nRows(); row++) {
                if (tmp(row, row) != 1) return false;
                for (int col = row + 1; col < nCols(); col++) {
                    if (tmp(row, col) != 0 || tmp(col, row) != 0) return false;
                }
            }
            return true;
        }

        //возвращает индекс минимального элемента последней строки
        SizeType getMinRowElIndex(SizeType row) {
            auto &tmp = *this;
            T minEl = 0;
            SizeType minIndex = 0;

            for (int j = 1; j < nCols(); j++) {
                if (tmp(row, j) < minEl) {
                    minEl = tmp(row, j);
                    minIndex = j;
                }
            }

            return minIndex;
        }

        friend std::ostream &operator<<(std::ostream &out, Matrix &matr) {
            for (int row = 0; row < matr.nRows(); row++) {
                out << "(";
                for (int col = 0; col < matr.nCols(); col++) {
                    out << std::setw(5) << matr(row, col);
                }
                out << ")\n";
            }
            return out;
        }

        //TODO: create matrix_row class
        static Row &plus(const Row &lhs, const Row &rhs) {
            if (lhs.size() != rhs.size())
                throw std::invalid_argument("lhs and rhs different sizes");

            auto lhsCopy = lhs;


            for (auto i = 0; i < lhs.size(); i++) {
                lhsCopy.at(i) = lhs.at(i) + rhs.at(i);
            }

            return lhsCopy;
        }

        static Row minus(const Row &lhs, const Row &rhs) {
            if (lhs.size() != rhs.size())
                throw std::invalid_argument("lhs and rhs different sizes");

            auto lhsCopy = lhs;

            for (auto i = 0; i < lhs.size(); i++) {
                lhsCopy.at(i) = lhs.at(i) - rhs.at(i);
            }

            return lhsCopy;
        }

        static Row mul(const Row &lhs, const T value) {
            auto lhsCopy = lhs;

            for (auto i = 0; i < lhs.size(); i++) {
                lhsCopy.at(i) = lhs.at(i) * value;
            }

            return lhsCopy;
        }

    private:
        SizeType m_nRows;
        SizeType m_nCols;

        SizeType maxElInColumn(SizeType column) {
            auto &tmp = *this;
            SizeType index = 0;
            auto maxEl = tmp(0, column);

            for (int row = 1; row < nRows(); row++) {
                if (tmp(row, column) > maxEl) {
                    maxEl = tmp(row, column);
                    index = row;
                }
            }

            return index;
        }

        SizeType maxAbsElInColumn(SizeType column) {
            auto &tmp = *this;
            SizeType index = 0;
            auto maxEl = abs(tmp(0, column));

            for (int row = 1; row < nRows(); row++) {
                if (abs(tmp(row, column)) > maxEl) {
                    maxEl = abs(tmp(row, column));
                    index = row;
                }
            }

            return index;
        }

        SizeType maxAbsElInColumnAfterRow(SizeType column, SizeType row) {
            auto &tmp = *this;
            SizeType index = row;
            auto maxEl = abs(tmp(row, column));

            for (int rowI = row; rowI < nRows(); rowI++) {
                if (abs(tmp(rowI, column)) > maxEl) {
                    maxEl = abs(tmp(rowI, column));
                    index = rowI;
                }
            }

            return index;
        }

        Matrix triangleGauss(SizeType &countSwaps) {
            Matrix tmp = *this;
            int maxElIndex;
            countSwaps = 0;

            for (int selectedRow = 0; selectedRow < nRows(); selectedRow++) {
                maxElIndex = tmp.maxAbsElInColumnAfterRow(selectedRow,
                                                          selectedRow);

                if (selectedRow < maxElIndex) {
                    tmp.swapRows(selectedRow, maxElIndex);
                    countSwaps++;
                }

                auto &subtractedRow = tmp[selectedRow];

                for (int index = selectedRow + 1; index < nRows(); index++) {

                    auto &curRow = tmp[index];

                    int colOffset = 0;
                    while (subtractedRow[selectedRow + colOffset] == 0 &&
                           selectedRow + colOffset < nCols()) {
                        colOffset++;
                    }

                    if (selectedRow + colOffset == nCols()) continue;

//                    if(curRow[selectedRow] == 0) continue;

                    T k = curRow[selectedRow + colOffset] /
                          subtractedRow[selectedRow + colOffset];


                    if (k == 0) continue;

                    auto subtr = mul(subtractedRow, k);

                    curRow = minus(curRow, subtr);
                }
            }

            return tmp;
        }
    };

    template<class T>
    requires ArithmeticOperations<T>
    std::vector<T> reverseGaussianStroke(Matrix<T> &koefMatrix,
                                         std::vector<T> additionalColumn) {
        std::vector<T> values(koefMatrix.nRows());

        for (int row = koefMatrix.nRows() - 1; row >= 0; row--) {
            for (int col = koefMatrix.nCols() - 1; col > row; col--) {
                additionalColumn[row] -= koefMatrix(row, col) * values[col];
            }

            auto val = additionalColumn[row];
            auto koef = koefMatrix(row, row) == 0 ? 1 : koefMatrix(row,
                                                                   row);
            values[row] = val / koef;
        }

        return values;
    }

    template<class T>
    requires ArithmeticOperations<T>
    Matrix<T> getAdditionalWithIdentityPart(Matrix<T> &matrix) {
        Matrix<T> additional(matrix.nRows(), matrix.nRows() * 2);
        for (auto row = 0; row < matrix.nRows(); row++) {
            for (auto col = 0; col < matrix.nRows(); col++) {
                additional(row, col) = matrix(row, col);
            }

            for (auto col = matrix.nRows(); col < additional.nCols(); col++) {
                additional(row, col) = col % matrix.nRows() == row ? 1 : 0;
            }
        }

        return additional;
    }
};

#endif //MATRIX_MATRIX_HPP
