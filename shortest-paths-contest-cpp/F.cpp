// Yandex Code Style
#include <iostream>
#include <vector>
#include <cstdint>
#include <queue>
#include <limits>

class TGraph {
public:
    TGraph(uint32_t n, uint32_t k)
        : CitiesNum_(n)
        , MainCityA_(0)
        , MainCityB_(0)
        , RoadsNum_(k)
        , Adj_(n)
    {
    }
    void ReadRoads(std::istream& stream) {
        uint32_t vertex1 = 0;
        uint32_t vertex2 = 0;
        uint32_t distance = 0;
        for (uint32_t i = 0; i < RoadsNum_; ++i) {
            stream >> vertex1 >> vertex2 >> distance;
            --vertex1;
            --vertex2;
            Adj_[vertex1].push_back({vertex2, distance});
            Adj_[vertex2].push_back({vertex1, distance});
        }
    }
    void ReadMainCities(std::istream& stream) {
        stream >> MainCityA_ >> MainCityB_;
        --MainCityA_;
        --MainCityB_;
    }
    uint64_t GetShortestPath() const {
        std::vector<uint64_t> distance = Dijkstra(MainCityA_);
        return distance[MainCityB_];
    }
private:
    std::vector<uint64_t> Dijkstra(uint32_t start) const {
        const uint64_t Inf = std::numeric_limits<uint64_t>::max();
        std::vector<uint64_t> distance(CitiesNum_, Inf);
        std::priority_queue<std::pair<uint64_t, uint32_t>, std::vector<std::pair<uint64_t, uint32_t>>, std::greater<std::pair<uint64_t, uint32_t>>> pq;
        distance[start] = 0;
        pq.push({0, start});
        while (!pq.empty()) {
            auto [dist, city] = pq.top();
            pq.pop();
            if (dist > distance[city]) {
                continue;
            }
            for (const auto& [neighbour, weight] : Adj_[city]) {
                if (distance[neighbour] > weight + distance[city]) {
                    distance[neighbour] = weight + distance[city];
                    pq.push({distance[neighbour], neighbour});
                }
            }
        }
        return distance;
    }
private:
    uint32_t CitiesNum_;
    uint32_t MainCityA_;
    uint32_t MainCityB_;
    uint32_t RoadsNum_;
    std::vector<std::vector<std::pair<uint32_t, uint64_t>>> Adj_;
};

int main() {
    const uint64_t Inf = std::numeric_limits<uint64_t>::max();
    uint32_t VerticesNum = 0;
    uint32_t Edges = 0;
    std::cin >> VerticesNum >> Edges;
    TGraph graph(VerticesNum, Edges);
    graph.ReadRoads(std::cin);
    graph.ReadMainCities(std::cin);
    uint64_t res = graph.GetShortestPath();
    if (res == Inf) {
        std::cout << -1;
    } else {
        std::cout << res;
    }
    std::cout << std::endl;
    return 0;
}   