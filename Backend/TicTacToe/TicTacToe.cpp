#include <iostream>
#include <ranges>
#include <algorithm>
#include <vector>

using namespace std;

auto range = [](auto bound) { return views::iota(0, bound); };

template<class... Args>
istream &operator>>(istream &is, tuple<Args...> &t) {
    apply([&is](auto &&... args) { ((is >> args), ...); }, t);
    return is;
}

namespace Reader {
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
    vector<vector<T>> readMatrix(size_t n, size_t m) {
        vector<vector<T>> mat(n, vector<T>(m));
        ranges::for_each(mat, [m](auto &row) { row = readVector<T>(m); });
        return mat;
    }
}

namespace Writer {
    template<typename T>
    void write(const T &val, const string &sep = " ") {
        cout << val << sep;
    }
}

bool checkHor(int i, int j, auto& matrix) {
    if (j + 4 >= matrix[0].size()) {
        return false;
    }

    return (matrix[i][j] == matrix[i][j + 1] &&
            matrix[i][j] == matrix[i][j + 2] &&
            matrix[i][j] == matrix[i][j + 3] &&
            matrix[i][j] == matrix[i][j + 4]) &&
            matrix[i][j] != '.';
}

bool checkVer(int i, int j, auto& matrix) {
    if (i + 4 >= matrix.size()) {
        return false;
    }

    return (matrix[i][j] == matrix[i + 1][j] &&
            matrix[i][j] == matrix[i + 2][j] &&
            matrix[i][j] == matrix[i + 3][j] &&
            matrix[i][j] == matrix[i + 4][j]) &&
            matrix[i][j] != '.';
}

bool checkDiagPrimary(int i, int j, auto& matrix) {
    if (i + 4 >= matrix.size() || j + 4 >= matrix[0].size()) {
        return false;
    }

    return (matrix[i][j] == matrix[i + 1][j + 1] &&
            matrix[i][j] == matrix[i + 2][j + 2] &&
            matrix[i][j] == matrix[i + 3][j + 3] &&
            matrix[i][j] == matrix[i + 4][j + 4]) &&
            matrix[i][j] != '.';
}

bool checkDiagSecondary(int i, int j, auto& matrix) {
    if (i + 4 >= matrix.size() || j + 4 >= matrix[0].size()) {
        return false;
    }

    return (matrix[i][j + 4] == matrix[i + 1][j + 3] &&
            matrix[i][j + 4] == matrix[i + 2][j + 2] &&
            matrix[i][j + 4] == matrix[i + 3][j + 1] &&
            matrix[i][j + 4] == matrix[i + 4][j]) &&
            matrix[i][j + 4] != '.';
}

int main() {
    auto [n, m] = Reader::read<tuple<int, int>>();
    if (n < 5 && m < 5) {
        Writer::write("No");
        return 0;
    }
    auto matrix = Reader::readMatrix<char>(n, m);

    for (auto i : range(n)) {
        for (auto j : range(m)) {
            if (checkHor(i, j, matrix) ||
                checkVer(i, j, matrix) ||
                checkDiagPrimary(i, j, matrix) ||
                checkDiagSecondary(i, j, matrix))
            {
                Writer::write("Yes");
                return 0;
            }
        }
    }

    Writer::write("No");
    return 0;
}