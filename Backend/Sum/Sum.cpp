#include <iostream>
#include <ranges>
#include <vector>
#include <algorithm>

using namespace std;

namespace {
    auto rangeFrom = [](int start, int bound) { return views::iota(start, bound); };

    template<typename T>
    T read() {
        T val;
        cin >> val;
        return val;
    }

    template<typename T>
    void writelnVector(const vector<T> &vec, const string &sep = " ") {
        for_each(vec.begin(), vec.end() - 1, [&sep](const auto &val) { cout << val << sep; });
        cout << vec.back() << "\n";
    }
}

void findDecomposition(int n, int maxNumber, vector<int>& state) {
    if (n == 0) {
        writelnVector(state, " + ");
        return;
    }

    for (int i : rangeFrom(1, min(n, maxNumber) + 1)) {
        state.push_back(i);
        findDecomposition(n - i, i, state);
        state.pop_back();
    }
}

void findWaysOfDecomposition(int n) {
    vector<int> state;
    findDecomposition(n, n, state);
}

int main() {
    auto n = read<int>();

    findWaysOfDecomposition(n);

    return 0;
}