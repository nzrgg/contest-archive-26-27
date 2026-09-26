// Yandex Code Style
#include <iostream>
#include <cstdint>
#include <vector>

class TGraph {
public:
    TGraph(uint32_t num)
        : NumVertices_(num)
        , Adj_(num) 
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
    
    uint32_t GetConnectedComponent(const uint32_t vertex) const {
        std::vector<bool> usedVertices(NumVertices_, false);
        DepthFirstSearch(vertex, usedVertices);
        uint32_t count = 0;
        for (uint32_t v = 0; v < NumVertices_; ++v) {
            if (usedVertices[v]) {
                ++count;
            }
        }
        return count;
    }

private:
    void DepthFirstSearch(const uint32_t vertex, std::vector<bool>& usedVertices) const {
        usedVertices[vertex] = true;
        for (uint32_t next : Adj_[vertex]) {
            if (!usedVertices[next]) {
                DepthFirstSearch(next, usedVertices);
            }
        }
    }

private:
    uint32_t NumVertices_;
    std::vector<std::vector<uint32_t>> Adj_;
};

int main() {
    uint32_t numVertices = 0;
    uint32_t startVertex = 0;
    std::cin >> numVertices >> startVertex;
    TGraph graph(numVertices);
    graph.ReadFromStream(std::cin);
    std::cout << graph.GetConnectedComponent(startVertex - 1) << std::endl;
    return 0;
}
