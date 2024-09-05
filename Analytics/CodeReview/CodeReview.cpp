#include <iostream>
#include <ranges>
#include <algorithm>
#include <vector>

using namespace std;

namespace {
    auto range = [](auto bound){ return views::iota(0, bound); };

    template<typename T>
    T read() {
        T val;
        cin >> val;
        return val;
    }

    template<typename T>
    vector<T> readVector(size_t n) {
        vector<T> vec(n);
        ranges::for_each(vec, [](auto &val) { cin >> val; });
        return vec;
    }

    template<typename T>
    void writeln(const T &val) {
        cout << val << "\n";
    }
}

bool visit(auto& redirects, int i) {
    if (redirects[i] == 0) {
        return false;
    }

    if (redirects[i] == -1) {
        return true;
    }

    int nextTeam = redirects[i];
    redirects[i] = 0;

    return visit(redirects, nextTeam);
}

int main() {
    auto n = read<int>();

    auto redirects = readVector<int>(n);

    writeln(visit(redirects, 0) ? "NO" : "YES");

    return 0;
}