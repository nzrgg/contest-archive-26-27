// Yandex Code Style
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <cstdint>
#include <cstddef>

class TStringSet {
public:
    TStringSet()
        : Buckets_(1024)
        , Count_(0)
    {
    }
    void Insert(const std::string& s) {
        std::list<std::string>& bucket = Buckets_[Hash(s)];
        for (const std::string& x : bucket) {
            if (x == s) {
                return;
            }
        }
        bucket.push_back(s);
        ++Count_;
        if (static_cast<double>(Count_) / Buckets_.size() > 1.0) {
            Rehash();
        }
    }
    void Erase(const std::string& s) {
        std::list<std::string>& bucket = Buckets_[Hash(s)];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (*it == s) {
                bucket.erase(it);
                return;
            }
        }
    }
    bool Contains(const std::string& s) const {
        const std::list<std::string>& bucket = Buckets_[Hash(s)];
        for (const std::string& x : bucket) {
            if (x == s) {
                return true;
            }
        }
        return false;
    }
private:
    std::size_t Hash(const std::string& s) const {
        uint64_t h = 0;
        for (unsigned char c : s) {
            h = h * 131 + c;
        }
        return h % Buckets_.size();
    }
    void Rehash() {
        std::vector<std::list<std::string>> old = std::move(Buckets_);
        Buckets_.assign(old.size() * 2, {});
        Count_ = 0;
        for (const std::list<std::string>& bucket : old) {
            for (const std::string& s : bucket) {
                Insert(s);
            }
        }
    }
private:
    std::vector<std::list<std::string>> Buckets_;
    std::size_t Count_;
};

int main() {
    TStringSet set;
    char op;
    std::string s;
    while (std::cin >> op && op != '#') {
        std::cin >> s;
        if (op == '+') {
            set.Insert(s);
        } else if (op == '-') {
            set.Erase(s);
        } else if (op == '?') {
            std::cout << (set.Contains(s) ? "YES" : "NO") << '\n';
        }
    }
    return 0;
}