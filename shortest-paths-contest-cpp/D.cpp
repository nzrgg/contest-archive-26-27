// Yandex Code Style
#include <iostream>
#include <cstdint>
#include <vector>
#include <tuple>
#include <numeric>

class TDisjointSetUnion {
public:
    TDisjointSetUnion(uint32_t n)
        : Rank_(n, 0)
        , Parent_(n)
    {
        std::iota(Parent_.begin(), Parent_.end(), 0);
    }
    uint32_t FindSet(uint32_t v) {
        return (Parent_[v] == v) ? v : Parent_[v] = FindSet(Parent_[v]);
    }
    void UnionSets(uint32_t a, uint32_t b) {
        uint32_t leaderA = FindSet(a);
        uint32_t leaderB = FindSet(b);
        if (Rank_[leaderA] > Rank_[leaderB]) {
            std::swap(leaderA, leaderB);
        }
        Rank_[leaderB] = std::max(Rank_[leaderB], Rank_[leaderA] + 1);
        Parent_[leaderA] = leaderB;
    }
private:
    std::vector<uint32_t> Rank_;
    std::vector<uint32_t> Parent_;
};

int main() {
    uint32_t n = 0;
    uint32_t m = 0;
    uint32_t d = 0;
    uint32_t v = 0;
    std::cin >> n >> m;
    std::vector<std::tuple<uint32_t, uint32_t, uint32_t>> newEdges;
    TDisjointSetUnion dsu(n * m);
    auto Id = [m](uint32_t i, uint32_t j) -> uint32_t {
        return i * m + j;
    };
    for (uint32_t i = 0; i < n; ++i) {
        for (uint32_t j = 0; j < m; ++j) {
            std::cin >> d;
            if (d == 1) {
                dsu.UnionSets(Id(i, j), Id(i + 1, j));
            } else if (d == 2) {
                dsu.UnionSets(Id(i, j), Id(i, j + 1));
            } else if (d == 3) {
                dsu.UnionSets(Id(i, j), Id(i + 1, j));
                dsu.UnionSets(Id(i, j), Id(i, j + 1));  
            }
        }
    }
    for (uint32_t j = 0; j < m; ++j) { // Вертикальные перемычки
        for (uint32_t i = 0; i < n - 1; ++i) {
            if (dsu.FindSet(Id(i, j)) != dsu.FindSet(Id(i + 1, j))) { // Если концы перемычек не в одной КСС, то соединяем их
                dsu.UnionSets(Id(i, j), Id(i + 1, j));
                newEdges.push_back(std::make_tuple(i + 1, j + 1, 1));
                ++v;
            }
        }
    }
    for (uint32_t i = 0; i < n; ++i) { // Горизонтальные перемычки
        for (uint32_t j = 0; j < m - 1; ++j) {
            if (dsu.FindSet(Id(i, j)) != dsu.FindSet(Id(i, j + 1))) { // Если концы перемычек не в одной КСС, то соединяем их
                dsu.UnionSets(Id(i, j), Id(i, j + 1));
                newEdges.push_back(std::make_tuple(i + 1, j + 1, 2));
                v += 2;
            }
        }
    }
    std::cout << newEdges.size() << " " << v << std::endl;
    for (const auto& [x, y, w] : newEdges) {
        std::cout << x << " " << y << " " << w << std::endl;
    }
    return 0;
}