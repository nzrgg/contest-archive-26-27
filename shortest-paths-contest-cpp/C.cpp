// Yandex Code Style
#include <iostream>
#include <cstdint>
#include <utility>
#include <vector>
#include <algorithm>
#include <numeric>

class TDisjointSetUnion {
public:
    TDisjointSetUnion(uint32_t n)
        : Rank_(n, 0)
        , Parent_(n)
        , Components_(n)
    {
        std::iota(Parent_.begin(), Parent_.end(), 0);
    }
    uint32_t FindSet(uint32_t v, std::vector<uint32_t>& parent) const {
        return (parent[v] == v) ? v : parent[v] = FindSet(parent[v], parent);
    }
    void UnionSets(uint32_t a, uint32_t b) {
        uint32_t leaderA = FindSet(a, Parent_);
        uint32_t leaderB = FindSet(b, Parent_);
        if (Rank_[leaderA] > Rank_[leaderB]) {
            std::swap(leaderA, leaderB);
        }
        Rank_[leaderB] = std::max(Rank_[leaderB], Rank_[leaderA] + 1);
        Parent_[leaderA] = leaderB;
        if (leaderA != leaderB) {
            --Components_;
        }
    }
    uint32_t GetComponents() const {
        return Components_;
    }
private:
    std::vector<uint32_t> Rank_;
    std::vector<uint32_t> Parent_;
    uint32_t Components_;
};

int main() {
    uint32_t m = 0;
    uint32_t n = 0;
    uint32_t x = 0;
    uint32_t y = 0;
    std::cin >> n >> m;
    TDisjointSetUnion dsu(n);
    for (uint32_t i = 0; i < m; ++i) {
        std::cin >> x >> y;
        dsu.UnionSets(x, y);
        if (dsu.GetComponents() == 1) {
            std::cout << i + 1 << std::endl;
            return 0;
        }
    }
    return 0;
}