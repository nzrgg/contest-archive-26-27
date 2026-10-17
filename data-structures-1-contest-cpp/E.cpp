// Yandex Code Style
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <limits>

int main() {
    uint32_t n = 0;
    std::cin >> n;
    std::vector<uint32_t> x(n);
    for (uint32_t i = 0; i < n; ++i) {
        std::cin >> x[i];
    }
    std::sort(x.begin(), x.end());
    const uint32_t Inf = std::numeric_limits<uint32_t>::max() / 4;
    uint32_t prev2 = Inf;
    uint32_t prev1 = x[1] - x[0];
    for (uint32_t i = 2; i < n; ++i) {
        uint32_t cur = std::min(prev1, prev2) + (x[i] - x[i-1]);
        prev2 = prev1;
        prev1 = cur;
    }
    std::cout << prev1 << std::endl;
    return 0;
}