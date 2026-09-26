// Yandex Code Style
#include <iostream>
#include <cstdint>
#include <vector>
#include <queue>
#include <algorithm>

const uint32_t UNVISITED = 0;
const uint32_t INPROGRESS = 1;
const uint32_t VISITED = 2;

class TGraph {
public:
    TGraph(uint32_t n)
        : NumVertices_(n)
        , PairsQtty_(0)
        , Adj_(n)
    {
    }
    void ReadFromStream(std::istream& stream) {
        stream >> PairsQtty_;
        uint32_t vertex1 = 0;
        uint32_t vertex2 = 0;
        for (uint32_t i = 0; i < PairsQtty_; ++i) {
            stream >> vertex1 >> vertex2;
            --vertex1;
            --vertex2;
            Adj_[vertex1].push_back(vertex2);
        }
    }
    std::vector<uint32_t> TopologicalSort() const {
        std::vector<uint32_t> path;
        std::vector<uint32_t> status(NumVertices_, UNVISITED);
        for (uint32_t i = 0; i < NumVertices_; ++i) {
            if (status[i] == UNVISITED && DepthFirstSearch(i, status, path)) {
                return {};
            }
        }
        std::reverse(path.begin(), path.end());
        return path;
    }
private:
    bool DepthFirstSearch(const uint32_t vertex, std::vector<uint32_t>& status, std::vector<uint32_t>& path) const {
        status[vertex] = INPROGRESS;
        for (uint32_t next : Adj_[vertex]) {
            if (status[next] == INPROGRESS) { // Если мы попали в вершину которая в обработке, то получился цикл
                return true;
            }
            if (status[next] == UNVISITED && DepthFirstSearch(next, status, path)) { // Прогоняем непосещенные вершины
                return true;
            }
        }
        status[vertex] = VISITED;
        path.push_back(vertex + 1);
        return false;
    }
private:
    uint32_t NumVertices_, PairsQtty_;
    std::vector<std::vector<uint32_t>> Adj_;
};

int main() {
    uint32_t numVertices = 0;
    std::cin >> numVertices;
    TGraph graph(numVertices);
    graph.ReadFromStream(std::cin);
    std::vector<uint32_t> path = graph.TopologicalSort();
    if (path.empty()) {
        std::cout << "No\n";
    } else {
        std::cout << "Yes\n";
        for (size_t i = 0; i < path.size(); ++i) {
            std::cout << path[i] << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}