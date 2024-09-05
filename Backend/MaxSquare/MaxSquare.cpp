#include <iostream>
#include <ranges>
#include <algorithm>
#include <vector>

using namespace std;

namespace {
    auto range = [](auto bound) { return views::iota(0, bound); };
    using BigInt = long long;

    template<class... Args>
    istream& operator>>(istream& is, tuple<Args...>& t) {
        apply([&is](auto&&... args){ ((is >> args), ...); }, t);
        return is;
    }

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

    template<typename T>
    void writeln(const T &val) {
        cout << val << "\n";
    }
}

pair<int, pair<int, int>> maximalSquare(vector<vector<int>>& matrix) {
    if (matrix.empty()) {
        return {0, {-1, -1}};
    }
    int m = matrix.size(), n = matrix[0].size(), sz = 0, pre;
    int topLeftI = -1, topLeftJ = - 1;
    vector<int> cur(n, 0);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int temp = cur[j];
            if (!i || !j || matrix[i][j] == 0) {
                cur[j] = matrix[i][j] - 0;
            } else {
                cur[j] = min(pre, min(cur[j], cur[j - 1])) + 1;
            }
            if (cur[j] > sz) {
                sz = cur[j];
                topLeftI = i - (sz - 1);
                topLeftJ = j - (sz - 1);
            }
            pre = temp;
        }
    }
    return {sz, {topLeftI, topLeftJ}};
}

int main() {
    auto [n, m] = read<tuple<int, int>>();

    vector<vector<int>> matrix;
    for (int i : range(n)) {
        matrix.push_back(readVector<int>(m));
    }

    auto [size, topLeft] = maximalSquare(matrix);
    auto [i, j] = topLeft;
    writeln(size);
    write(i + 1);
    writeln(j + 1);
}