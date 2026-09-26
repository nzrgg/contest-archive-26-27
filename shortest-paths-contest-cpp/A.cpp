// Yandex Code Style
#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>

class TGraph {
public:
    TGraph(uint32_t n)
        : NumVertices_(n)
        , Matrix_(n, std::vector<int32_t>(n, 0))
    {
    }
    void ReadFromStream(std::istream& stream) {
        for (uint32_t i = 0; i < NumVertices_; ++i) {
            for (uint32_t j = 0; j < NumVertices_; ++j) {
                stream >> Matrix_[i][j];
            }
        }
    }
    void Floyd() {
        for (uint32_t k = 0; k < NumVertices_; ++k) {
            for (uint32_t i = 0; i < NumVertices_; ++i) {
                for (uint32_t j = 0; j < NumVertices_; ++j) {
                    Matrix_[i][j] = std::min(Matrix_[i][j], Matrix_[i][k] + Matrix_[k][j]);
                }
            }
        }
    }
    void PrintToStream(std::ostream& stream) {
        for (uint32_t i = 0; i < NumVertices_; ++i) {
            for (uint32_t j = 0; j < NumVertices_; ++j) {
                stream << Matrix_[i][j] << " ";
            }
            stream << std::endl;
        }
    }
private:
    uint32_t NumVertices_;
    std::vector<std::vector<int32_t>> Matrix_;
};

int main() {
    uint32_t n = 0;
    std::cin >> n;
    TGraph g(n);
    g.ReadFromStream(std::cin);
    g.Floyd();
    g.PrintToStream(std::cout);
    return 0;
}