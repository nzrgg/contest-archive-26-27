// Yandex Code Style
#include <iostream>
#include <vector>
#include <cstdint>
#include <queue>
#include <limits>
#include <utility>
#include <cmath>
#include <map>

class TGraph {
public:
    TGraph(uint32_t n)
        : CitiesNum_(n)
        , MainCityA_(0)
        , MainCityB_(0)
        , Coords_(n, {0, 0})
        , SpecialCities_()
    {
    }
    void ReadCitiesCoords(std::istream& stream) {
        int32_t x = 0;
        int32_t y = 0;
        for (uint32_t i = 0; i < CitiesNum_; ++i) {
            stream >> x >> y;
            Coords_[i] = {x, y};
        }
    }
    void ReadSpecialCities(std::istream& stream) {
        uint32_t m = 0;
        uint32_t vertex1 = 0;
        uint32_t vertex2 = 0;
        uint32_t distance = 0;
        stream >> m;
        for (uint32_t i = 0; i < m; ++i) {
            stream >> vertex1 >> vertex2 >> distance;
            --vertex1;
            --vertex2;
            SpecialCities_[uint64_t(vertex1) << 32 | vertex2] = distance;
            SpecialCities_[uint64_t(vertex2) << 32 | vertex1] = distance;
        }
    }
    void ReadMainCities(std::istream& stream) {
        stream >> MainCityA_ >> MainCityB_;
        --MainCityA_;
        --MainCityB_;
    }
    double GetShortestPath() const {
        std::vector<double> distance = Dijkstra(MainCityA_);
        return distance[MainCityB_];
    }
private:
    std::vector<double> Dijkstra(uint32_t start) const {
        double dx = 0.0;
        double dy = 0.0;
        double w = 0.0;
        const double INF = std::numeric_limits<double>::max();
        std::vector<double> distance(CitiesNum_, INF);
        distance[start] = 0;
        std::priority_queue<std::pair<double, uint32_t>, std::vector<std::pair<double, uint32_t>>, std::greater<std::pair<double, uint32_t>>> pq;
        pq.push({0, start});
        while (!pq.empty()) {
            auto [dist, city] = pq.top();
            pq.pop();
            if (dist > distance[city]) {
                continue;
            }
            for (uint32_t v = 0; v < CitiesNum_; ++v) {
                if (v == city) {
                    continue;
                }
                uint64_t key = (uint64_t(city) << 32) | v;
                if (auto search = SpecialCities_.find(key); search != SpecialCities_.end()) {
                    w = search->second;
                } else {
                    dx = Coords_[city].first - Coords_[v].first;
                    dy = Coords_[city].second - Coords_[v].second;
                    w = std::sqrt(dx * dx + dy * dy);
                }
                if (distance[v] > w + dist) {
                    distance[v] = w + dist;
                    pq.push({distance[v], v});
                }
            }
        }
        return distance;
    }
private:
    uint32_t CitiesNum_;
    uint32_t MainCityA_;
    uint32_t MainCityB_;
    std::vector<std::pair<int32_t, int32_t>> Coords_;
    std::map<uint64_t, int32_t> SpecialCities_;
};

int main() {
    uint32_t n = 0;
    std::cin >> n;
    TGraph graph(n);
    graph.ReadCitiesCoords(std::cin);
    graph.ReadSpecialCities(std::cin);
    graph.ReadMainCities(std::cin);
    std::cout << graph.GetShortestPath() << std::endl;
    return 0;
}