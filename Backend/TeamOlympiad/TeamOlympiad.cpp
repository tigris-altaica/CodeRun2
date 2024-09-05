#include <iostream>
#include <ranges>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

namespace {
    auto range = [](int bound) { return views::iota(0, bound); };

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
    void write(const T &val, const string &sep = " ") {
        cout << val << sep;
    }
}

pair<int, int> minSumIdxs(const vector<int>& a, const vector<int>& b) {
    int minFirst = 5;
    int minSum = minFirst + 5;
    int minIdx = 0;
    int minFirstIdx = -1, minSecondIdx = -1;

    for (auto idx : range(a.size())) {
        if (a[idx] < minFirst) {
            minFirst = a[idx];
            minIdx = idx;
        }
        if (minFirst + b[idx] < minSum) {
            minSum = minFirst + b[idx];
            minFirstIdx = minIdx;
            minSecondIdx = idx;
        }
    }

    return { minFirstIdx, minSecondIdx };
}

int minSumTripartition(const vector<int>& a, const vector<int>& b, const vector<int>& c) {
    vector<int> diffAB, diffBC;
    transform(a.begin() + 1, a.end() - 2, b.begin() + 1, back_inserter(diffAB), minus{});
    transform(b.begin() + 2, b.end() - 1, c.begin() + 2, back_inserter(diffBC), minus{});

    vector<int> prefixSumsDiffAB, prefixSumsDiffBC;
    partial_sum(diffAB.begin(), diffAB.end(), back_inserter(prefixSumsDiffAB));
    partial_sum(diffBC.begin(), diffBC.end(), back_inserter(prefixSumsDiffBC));

    auto [i, j] = minSumIdxs(prefixSumsDiffAB, prefixSumsDiffBC);
    i += 2;
    j += 3;
    auto aSum = accumulate(a.begin(), a.begin() + i, 0);
    auto bSum = accumulate(b.begin() + i, b.begin() + j, 0);
    auto cSum = accumulate(c.begin() + j, c.end(), 0);

    return aSum + bSum + cSum;
}

int main() {
    auto n = read<int>();
    auto a = readVector<int>(n);
    auto b = readVector<int>(n);
    auto c = readVector<int>(n);

    int minSum = n * 5;
    minSum = min(minSumTripartition(a, b, c), minSum);
    minSum = min(minSumTripartition(a, c, b), minSum);
    minSum = min(minSumTripartition(b, a, c), minSum);
    minSum = min(minSumTripartition(b, c, a), minSum);
    minSum = min(minSumTripartition(c, a, b), minSum);
    minSum = min(minSumTripartition(c, b, a), minSum);

    write(minSum);

    return 0;
}