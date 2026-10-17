// Yandex Code Style
#include <iostream>
#include <vector>
#include <cstdint>
#include <limits>

int main() {
    uint32_t n = 0;
    uint32_t k = 0;
    std::cin >> n >> k;
    std::vector<uint32_t> wires(n);
    uint32_t maxWire = 0;
    for (uint32_t i = 0; i < n; ++i) {
        std::cin >> wires[i];
        maxWire = std::max(maxWire, wires[i]);
    }
    auto f = [&wires](uint32_t len) -> uint32_t {
        uint32_t parts = 0;
        for (uint32_t w : wires) {
            parts += w / len;
        }
        return parts;
    };
    uint32_t l = 1;
    uint32_t r = maxWire;
    uint32_t mid = 0;
    uint32_t res = 0;
    while (l <= r) {
        mid = (l + r) / 2;
        if (f(mid) < k) {
            r = mid - 1;
        } else if (f(mid) >= k) {
            res = mid;
            l = mid + 1;
        }
    }
    std::cout << res << std::endl;
    return 0;
}