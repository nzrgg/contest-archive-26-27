// Yandex Code Style
#include <iostream>
#include <cstdint>
#include <vector>
#include <stack>
#include <algorithm>
#include <limits>

const uint32_t UNVISITED = std::numeric_limits<int32_t>::max();

class TGraph {
public:
    TGraph(uint32_t n)
        : NumVertices_(n)
        , Timer_(0)
        , SCCNum_(1)
        , Adj_(n)
        , Low_(n)
        , Tin_(n, UNVISITED)
        , SCCMarker_(n)
        , OnStack_(n)
        , Stack_()
    {
    }
    void ReadFromStream(std::istream& stream) {
        uint32_t edgesQtty = 0;
        uint32_t vertex1 = 0;
        uint32_t vertex2 = 0;
        stream >> edgesQtty;
        for (uint32_t i = 0; i < edgesQtty; ++i) {
            stream >> vertex1 >> vertex2;
            --vertex1;
            --vertex2;
            Adj_[vertex1].push_back(vertex2);
        }
    }
    void GrapCondensation() {
        for (uint32_t i = 0; i < NumVertices_; ++i) {
            if (Tin_[i] == UNVISITED) {
                DepthFirstSearch(i);
            }
        }
    }
    void PrintCondensedGraph() {
        std::cout << SCCNum_ - 1 << std::endl;
        for (uint32_t i = 0; i < NumVertices_; ++i) {
            std::cout << SCCMarker_[i] + SCCNum_ << " ";
        }
        std::cout << std::endl;
    }
    void DepthFirstSearch(const uint32_t vertex) {
        Low_[vertex] = Timer_;
        Tin_[vertex] = Timer_;
        ++Timer_;
        Stack_.push(vertex);
        OnStack_[vertex] = true;
        for (uint32_t next : Adj_[vertex]) {
            if (Tin_[next] == UNVISITED) {
                DepthFirstSearch(next);
                Low_[vertex] = std::min(Low_[vertex], Low_[next]);
            }
            if (Tin_[next] != UNVISITED && OnStack_[next]) {
                Low_[vertex] = std::min(Low_[vertex], Tin_[next]);
            }
        }
        if (Low_[vertex] == Tin_[vertex]) {
            while (true) {
                uint32_t u = Stack_.top();
                Stack_.pop();
                OnStack_[u] = false;
                SCCMarker_[u] = -SCCNum_;
                if (u == vertex) {
                    break;
                }
            }
            ++SCCNum_;
        }
        return;
    }
private:
    uint32_t NumVertices_, Timer_;
    int32_t SCCNum_;
    std::vector<std::vector<uint32_t>> Adj_;
    std::vector<uint32_t> Low_, Tin_;
    std::vector<int32_t> SCCMarker_;
    std::vector<bool> OnStack_;
    std::stack<uint32_t> Stack_; 
};

int main() {
    uint32_t numVertices = 0;
    std::cin >> numVertices;
    TGraph graph(numVertices);
    graph.ReadFromStream(std::cin);
    graph.GrapCondensation();
    graph.PrintCondensedGraph();
    return 0;
}