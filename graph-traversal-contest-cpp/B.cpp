// Yandex Code Style
#include <iostream>
#include <vector>
#include <cstdint>
#include <queue>
#include <algorithm>
#include <limits>

const uint32_t INF = std::numeric_limits<int32_t>::max();

class TGraph {
public:
    TGraph(uint32_t n, uint32_t k)
        : N_(n)
        , ExitsQtty_(k)
        , TunnelsQtty_(0)
        , Exits_(k)
        , Adj_(n)
    {
    }
    void ReadFromStream(std::istream& stream) {
        stream >> TunnelsQtty_;
        uint32_t vertex1 = 0;
        uint32_t vertex2 = 0;
        for (uint32_t i = 0; i < TunnelsQtty_; ++i) {
            stream >> vertex1 >> vertex2;
            --vertex1;
            --vertex2;
            Adj_[vertex1].push_back(vertex2);
            Adj_[vertex2].push_back(vertex1);
        }
    }
    std::vector<int32_t> BreadthFirstSearch(const std::vector<uint32_t>& startVertices) const {
        std::vector<int32_t> distances(N_, -1);
        std::queue<uint32_t> q;
        for (uint32_t startVertex : startVertices) {
            distances[startVertex] = 0;
            q.push(startVertex);
        }
        while (!q.empty()) { // Поиск в ширину
                uint32_t vertex = q.front();
                q.pop();
                for (uint32_t neighbor : Adj_[vertex]) {
                    if (distances[neighbor] == -1) {
                        distances[neighbor] = distances[vertex] + 1;
                        q.push(neighbor);
                    }
                }
            }
        return distances;
    }
    std::vector<uint32_t> ReadExits(std::istream& stream) {
        std::vector<uint32_t> exits(ExitsQtty_);
        for (uint32_t i = 0; i < ExitsQtty_; ++i) {
            stream >> exits[i];
            --exits[i];
        }
        return exits;
    }
private:
    uint32_t N_, ExitsQtty_, TunnelsQtty_;
    std::vector<uint32_t> Exits_;
    std::vector<std::vector<uint32_t>> Adj_;
};

int main() {
    uint32_t n = 0;
    uint32_t exitsQtty = 0;
    std::cin >> n >> exitsQtty;
    TGraph g(n, exitsQtty);
    std::vector<uint32_t> exits = g.ReadExits(std::cin);
    g.ReadFromStream(std::cin);
    std::vector<int32_t> distancesToExit = g.BreadthFirstSearch(exits);
    for (uint32_t i = 0; i < n; ++i) {
        std::cout << distancesToExit[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}