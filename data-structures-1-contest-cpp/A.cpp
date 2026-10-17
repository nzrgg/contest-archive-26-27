// Yandex Code Style
#include <iostream>
#include <memory>
#include <cstdint>
#include <algorithm>

struct Node {
    Node(uint32_t v)
        : val(v)
        , left()
        , right()
    {
    }
    uint32_t val;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
};

void push(std::unique_ptr<Node>& root, uint32_t key) {
    if (!root) {
        root = std::make_unique<Node>(key);
        return;
    }
    if (key < root->val) {
        push(root->left, key);
    } else if (key > root->val) {
        push(root->right, key);
    }
}

uint32_t getHeight(std::unique_ptr<Node>& root) {
    if (!root) {
        return 0;
    }
    return std::max(getHeight(root->left), getHeight(root->right)) + 1;
}

int main() {
    std::unique_ptr<Node> root;
    uint32_t n = 0;
    while (std::cin >> n && n != 0) {
        push(root, n);
    }
    std::cout << getHeight(root) << std::endl;
    return 0;
}