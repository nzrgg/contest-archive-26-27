// Yandex Code Style
#include <iostream>
#include <vector>
#include <cstdint>
#include <queue>
#include <limits>
#include <utility>
#include <cmath>
#include <algorithm>

class TGraph {
public:
    TGraph(uint32_t n)
        : CitiesNum_(n)
        , MainCityA_(0)
        , MainCityB_(0)
        , Coords_(n)
        , SpecialCities_(10000)
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
            SpecialCities_[vertex1].push_back({vertex2, distance});
            SpecialCities_[vertex2].push_back({vertex1, distance});
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
        double weight = 0.0;
        const double InfDouble = std::numeric_limits<double>::max() / 2;
        const uint32_t InfInt = std::numeric_limits<uint32_t>::max() / 2;
        std::vector<double> distance(CitiesNum_, InfDouble);
        std::vector<bool> used(CitiesNum_, false);
        distance[start] = 0.0;
        for (uint32_t i = 0; i < CitiesNum_; ++i) {
            uint32_t city = InfInt;

            for (uint32_t j = 0; j < CitiesNum_; ++j) {
                if (!used[j] && (city == InfInt || distance[j] < distance[city])) {
                    city = j;
                }
            }

            if (distance[city] - InfDouble >= 0) {
                break;
            }
            used[city] = true;
            for (uint32_t neighbor = 0; neighbor < CitiesNum_; ++neighbor) {
                if (neighbor == city) {
                    continue;
                }
                dx = static_cast<double>(Coords_[city].first) - static_cast<double>(Coords_[neighbor].first);
                dy = static_cast<double>(Coords_[city].second) - static_cast<double>(Coords_[neighbor].second);
                weight = std::sqrt(dx * dx + dy * dy);
                for (const auto& p : SpecialCities_[neighbor]) {
                    if (p.first == city) {
                        weight = p.second;
                        break;
                    }
                }
                if (distance[neighbor] > weight + distance[city]) {
                    distance[neighbor] = weight + distance[city];
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
    std::vector<std::vector<std::pair<uint32_t, int32_t>>> SpecialCities_;
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