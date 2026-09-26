// Yandex Code Style
#include <iostream>
#include <cstdint>
#include <vector>
#include <queue>

const uint32_t UNVISITED = 0;
const uint32_t INPROGRESS = 1;
const uint32_t VISITED = 2;

class TGraph {
public:
    TGraph(uint32_t n)
        : NumVertices_(n)
        , Adj_(n)
    {
    }
    void ReadFromStream(std::istream& stream) {
        bool edge = false;
        for (uint32_t i = 0; i < NumVertices_; ++i) {
            for (uint32_t j = 0; j < NumVertices_; ++j) {
                stream >> edge;
                if (edge) {
                    Adj_[i].push_back(j);
                }
            }
        }
    }
    bool HasCycle() const {
        std::vector<uint32_t> status(NumVertices_, UNVISITED);
        for (uint32_t i = 0; i < NumVertices_; ++i) {
            if (status[i] == UNVISITED && DepthFirstSearch(i, status)) {
                return true;
            }
        }
        return false;
    }
private:
    bool DepthFirstSearch(const uint32_t vertex, std::vector<uint32_t>& status) const {
        status[vertex] = INPROGRESS;
        for (uint32_t next : Adj_[vertex]) {
            if (status[next] == INPROGRESS) { // Если мы попали в вершину которая в обработке, то получился цикл
                return true;
            }
            if (status[next] == UNVISITED && DepthFirstSearch(next, status)) { // Прогоняем непосещенные вершины
                return true;
            }
        }
        status[vertex] = VISITED;
        return false;
    }
private:
    uint32_t NumVertices_;
    std::vector<std::vector<uint32_t>> Adj_;
};

int main() {
    uint32_t numVertices = 0;
    std::cin >> numVertices;
    TGraph graph(numVertices);
    graph.ReadFromStream(std::cin);
    std::cout << graph.HasCycle() << std::endl;
    return 0;
}