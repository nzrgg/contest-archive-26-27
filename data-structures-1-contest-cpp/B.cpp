// Yandex Code Style
#include <iostream>
#include <vector>
#include <cstdint>

void siftDown(std::vector<int32_t>& data, size_t n, size_t i) {
    while (true) {
        size_t largest = i;
        size_t l = 2 * i + 1;
        size_t r = 2 * i + 2;

        if (l < n && data[l] > data[largest]) {
            largest = l;
        }
        if (r < n && data[r] > data[largest]) {
            largest = r;
        }
        if (largest == i) {
            return;
        }
        std::swap(data[i], data[largest]);
        i = largest;
    }
}

void heapSort(std::vector<int32_t>& data) {
    int32_t n = data.size();
    for (int32_t i = n / 2 - 1; i > -1; --i) {
        siftDown(data, n, i);
    }
    for (int32_t i = n - 1; i > 0; --i) {
        std::swap(data[0], data[i]);
        siftDown(data, i, 0);
    }
}

int main() {
    uint32_t n;
    std::cin >> n;
    std::vector<int32_t> data(n);
    for (uint32_t i = 0; i < n; ++i) {
        std::cin >> data[i];
    }
    heapSort(data);
    for (uint32_t i = 0; i < n; ++i) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}