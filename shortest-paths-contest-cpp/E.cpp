// Yandex Code Style
#include <iostream>
#include <vector>
#include <deque>
#include <cstdint>
#include <vector>
#include <limits>
#include <set>
#include <algorithm>

const uint32_t Inf = std::numeric_limits<uint32_t>::max() - 1;

class TGraph {
public:
    TGraph(uint32_t n, uint32_t k)
        : N_(n)
        , MapsQtty_(k)
        , Adj_(k + 1, std::vector<std::vector<uint32_t>>(n))
        , MapsHasBuilding_(n)
    {
    }
    void ReadMaps(std::istream& stream, uint32_t mapNum) {
        uint32_t edgesQtty = 0;
        stream >> edgesQtty;
        uint32_t vertex1 = 0;
        uint32_t vertex2 = 0;
        for (uint32_t i = 0; i < edgesQtty; ++i) {
            stream >> vertex1 >> vertex2;
            --vertex1;
            --vertex2;
            Adj_[mapNum][vertex1].push_back(vertex2);
            Adj_[mapNum][vertex2].push_back(vertex1);
            MapsHasBuilding_[vertex1].push_back(mapNum);
            MapsHasBuilding_[vertex2].push_back(mapNum);
        }
    }
    uint32_t BreadthFirstSearch(uint32_t startVertex) {
        std::vector<std::vector<uint32_t>> distances(N_, std::vector<uint32_t>(MapsQtty_ + 1, Inf));
        std::deque<std::pair<uint32_t, uint32_t>> dq;
        distances[startVertex][0] = 0;
        dq.push_back({startVertex, 0});
        while (!dq.empty()) {
            auto [vertex, map] = dq.front();
            dq.pop_front();
            if (map == 0) {
                for (uint32_t m : MapsHasBuilding_[vertex]) {
                    if (distances[vertex][m] > distances[vertex][map] + 1) {
                        distances[vertex][m] = distances[vertex][map] + 1;
                        dq.push_back({vertex, m});
                    }
                }
            } else {
                for (uint32_t neighbor : Adj_[map][vertex]) {
                    if (distances[neighbor][map] > distances[vertex][map]) {
                        distances[neighbor][map] = distances[vertex][map];
                        dq.push_front({neighbor, map});
                    }
                }
                if (distances[vertex][0] > distances[vertex][map]) {
                    distances[vertex][0] = distances[vertex][map];
                    dq.push_front({vertex, 0});
                }
            }
        }
        uint32_t res = Inf;
        for (uint32_t m = 0; m < MapsQtty_ + 1; ++m) {
            res = std::min(res, distances[N_ - 1][m]);
        }
        return res;
    }
private:
    uint32_t N_, MapsQtty_;
    std::vector<std::vector<std::vector<uint32_t>>> Adj_;
    std::vector<std::vector<uint32_t>> MapsHasBuilding_;
};

int main() {
    uint32_t buildingsNum = 0;
    uint32_t mapsNum = 0;
    std::cin >> buildingsNum >> mapsNum;
    TGraph g(buildingsNum, mapsNum);
    for (uint32_t i = 0; i < mapsNum; ++i) {
        g.ReadMaps(std::cin, i + 1);
    }
    uint32_t res = g.BreadthFirstSearch(0);
    if (res == Inf) {
        std::cout << "-1";
    } else {
        std::cout << res;
    }
    std::cout << std::endl;
    return 0;
}