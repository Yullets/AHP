//
// Created by vladv on 16.03.2023.
//

#ifndef IO_4_GRAPH_HPP
#define IO_4_GRAPH_HPP

#include <set>
#include <vector>
#include <map>
#include <functional>

#include "matrix.hpp"

template<typename T>
class Graph {
public:
    using SizeType = std::size_t;
    using Edge = std::pair<T, T>;
    using Matrix = matrix::Matrix<int>;
    using MatrixRow = Matrix::Row;

    Graph() = default;

    explicit
    Graph(const std::set<T>& vertexes,
          const std::set<Edge>& edges = std::vector<Edge>(0)) {

        validateData(vertexes, edges);

        m_vertexes = vertexes;
        m_edges    = edges;
        indexing();
        updateIncidenceMatrix();
        updateAdjacencyMatrix();
    }

    explicit
    Graph(const matrix::Matrix<int>& adjacencyMatrix) {
        std::set<int>  vertexes;
        std::set<Edge> edges;
        for (int       i = 1; i <= adjacencyMatrix.nCols(); i++) {
            vertexes.insert(i);
        }

        for (int row = 1; row <= adjacencyMatrix.nRows(); row++) {
            for (int col = 1; col <= adjacencyMatrix.nCols(); col++) {
                if (adjacencyMatrix(row - 1, col - 1) > 0) {
                    edges.insert({row, col});
                }
            }
        }

        validateData(vertexes, edges);

        m_vertexes = vertexes;
        m_edges    = edges;
        indexing();
        updateIncidenceMatrix();
        updateAdjacencyMatrix();
    }

    [[nodiscard]]
    const Matrix& getIncidenceMatrix() const {
        return m_incidenceMatrix;
    }

    [[nodiscard]]
    const Matrix& getAdjacencyMatrix() const {
        return m_adjacencyMatrix;
    }


    void addEdge(const Edge& edge) {
        m_edges.push_back(edge);
        std::sort(m_edges.begin(), m_edges.end());

        updateAdjacencyMatrix();
        updateIncidenceMatrix();
    }

    void addVertex(const T& vertex) {
        m_vertexes.push_back(vertex);
        std::sort(m_vertexes.begin(), m_vertexes.end());

        indexing();
        updateAdjacencyMatrix();
        updateIncidenceMatrix();
    }

    void removeEdge(const Edge& edge) {
        std::remove(m_edges.begin(), m_edges.end(),
                    [&edge](auto ed) -> bool {
                        return ed == edge;
                    }
                   );
        updateAdjacencyMatrix();
        updateIncidenceMatrix();
    }

    void removeVertex(const T& vertex) {
        std::remove_if(m_edges.begin(), m_edges.end(),
                       [&vertex](const Edge& edge) -> bool {
                           return edge.first == vertex ||
                                  edge.second == vertex;
                       }
                      );


        indexing();
        updateAdjacencyMatrix();
        updateIncidenceMatrix();
    }


    std::vector<std::vector<T>> getSimpleCyclesFromVertex(
            const T& vertex) {
    }


    std::vector<T> getSimpleCycleFromVertex(
            const T& vertex) {
        std::vector<T> minCycle;
        std::vector<T> curCycle = {vertex};
        std::set<T>    includedVertexes;

        auto pred = [](auto v, auto pos, auto cur) -> bool {
            return true;
        };

        getSimpleCycleFromVertex(minCycle,
                                 curCycle,
                                 1,
                                 includedVertexes,
                                 pred);
        return minCycle;
    }

    std::vector<T> getSimpleCycleFromVertex(
            const T& vertex,
            const std::function<bool(std::vector<T>&, int, T)>& pred) {

        std::vector<T> minCycle;
        std::vector<T> curCycle = {vertex};
        std::set<T>    includedVertexes;
        getSimpleCycleFromVertex(minCycle,
                                 curCycle,
                                 1,
                                 includedVertexes,
                                 pred);

        return minCycle;
    }


    ~Graph() = default;

    matrix::Matrix<int> kruskal_alg(int &count) {
        matrix::Matrix<int> res(m_adjacencyMatrix.nRows(), m_adjacencyMatrix.nCols());
        std::vector<int> bouquet(m_adjacencyMatrix.nRows());

        count = m_adjacencyMatrix.nRows();

        for (int i = 0; i < m_adjacencyMatrix.nRows(); i++) {
            bouquet[i] = i;
        }

        for (int i = 0; i < m_adjacencyMatrix.nRows(); i++) {
            for (int j = 0; j < m_adjacencyMatrix.nCols(); j++) {
                if (m_adjacencyMatrix[i][j] && bouquet[i] != bouquet[j]) {
                    auto removedBouquet = bouquet[j];
                    auto newBouquet = bouquet[i];
                    for (auto &v: bouquet) {
                        if (v == removedBouquet)
                            v = newBouquet;
                    }
                    res[i][j] = true;
                    count--;
                }
            }
        }

        return res;
    }

    bool isConnectedGraph() {
        int count;
        kruskal_alg(count);
        return count == 1;
    }

private:
    Matrix m_incidenceMatrix;
    Matrix m_adjacencyMatrix;

    std::map<int, T> m_vertexIndex;
    std::map<T, int> m_indexVertex;

    std::set<T>    m_vertexes;
    std::set<Edge> m_edges;

    static void validateData(const std::set<T>& vertexes,
                             const std::set<Edge>& edges) {

        for (const auto& edge: edges) {
            const auto& vertex1 = edge.first;
            const auto& vertex2 = edge.second;

            if (!vertexes.contains(vertex1) ||
                !vertexes.contains(vertex2)) {
                throw std::invalid_argument("vertex not in graph");
            }
        }

    }

    void indexing() {
        m_vertexIndex.clear();
        m_indexVertex.clear();

        int       index = 0;
        for (auto val: m_vertexes) {
            m_indexVertex[val]   = index;
            m_vertexIndex[index] = val;
            index++;
        }
    }

    void updateIncidenceMatrix() {
        m_incidenceMatrix =
                matrix::Matrix<int>(m_vertexes.size(), m_edges.size());

        int       edgeIndex = 0;
        for (auto edge: m_edges) {
            auto v1Index = index(edge.first);
            auto v2Index = index(edge.second);
            m_incidenceMatrix(v1Index, edgeIndex) = -1;
            m_incidenceMatrix(v2Index, edgeIndex) = 1;
            edgeIndex++;
        }
    }

    void updateAdjacencyMatrix() {
        m_adjacencyMatrix =
                matrix::Matrix<int>(m_vertexes.size(), m_vertexes.size());
        for (const auto& edge: m_edges) {
            auto v1Index = index(edge.first);
            auto v2Index = index(edge.second);
            m_adjacencyMatrix(v1Index, v2Index) = 1;
        }
    }

    std::set<T> G(const T& vertex) {
        std::set<T> vertexes;
        auto        vertexIndex = m_indexVertex[vertex];

        for (auto i = 0; i < m_vertexes.size(); i++) {
            if (m_adjacencyMatrix(vertexIndex, i) > 0) {
                vertexes.insert(m_vertexIndex[i]);
            }
        }

        return vertexes;
    }

    auto index(const T& vertex) -> int {
        return m_indexVertex[vertex];
    }

    auto vertexByIndex(const int index) -> const T& {
        return m_vertexIndex[index];
    }


    void getSimpleCyclesFromVertex(std::vector<std::vector<T>>& cycles,
                                   std::vector<T>& currentCycle,
                                   int index,
                                   std::set<T>& includedVertexes) {
        auto g = G(currentCycle[index - 1]);
        {
            std::set<T> diff;
            std::set_difference(g.begin(), g.end(),
                                includedVertexes.begin(),
                                includedVertexes.end(),
                                std::inserter(diff, diff.begin()));
            g = diff;
        }


        for (auto val: g) {
            currentCycle.push_back(val);
            includedVertexes.insert(val);

            if (val == currentCycle.front() && index > 2) {
                cycles.push_back(currentCycle);
            } else {
                getSimpleCycleFromVertex(
                        cycles,
                        currentCycle,
                        index + 1,
                        includedVertexes);
            }

            currentCycle.pop_back();
            includedVertexes.erase(val);
        }
    }

    void getSimpleCycleFromVertex(
            std::vector<T>& minCycle,
            std::vector<T>& currentCycle,
            int index,
            std::set<T>& includedVertexes,
            const std::function<bool(std::vector<T>&, int, T)>& pred) {
        auto g = G(currentCycle[index - 1]);
        {
            std::set<T> diff;
            std::set_difference(g.begin(), g.end(),
                                includedVertexes.begin(),
                                includedVertexes.end(),
                                std::inserter(diff, diff.begin()));
            g = diff;
        }

        for (auto val: g) {
            if (pred(currentCycle, index, val) == false) continue;

            currentCycle.push_back(val);
            includedVertexes.insert(val);

            if (val == currentCycle.front() &&
                index > 2 && (
                        currentCycle.size() < minCycle.size() ||
                        minCycle.empty())
                    ) {
                minCycle = currentCycle;
            } else {
                getSimpleCycleFromVertex(
                        minCycle,
                        currentCycle,
                        index + 1,
                        includedVertexes,
                        pred);
            }

            currentCycle.pop_back();
            includedVertexes.erase(val);
        }
    }
};

#endif //IO_4_GRAPH_HPP