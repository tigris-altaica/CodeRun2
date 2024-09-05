#include <numeric>
#include <vector>
#include <ranges>
#include <algorithm>
#include <iostream>

using namespace std;
using BigInt = long long;
auto range = [](auto bound) { return views::iota(0, bound); };

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
    void writeln(const T &val) {
        cout << val << "\n";
    }
}

template <typename T>
class SubmatrixSums {
    int n;
    int m;
    vector<vector<T>> sums;

public:
    SubmatrixSums(vector<vector<T>>& matrix) : n(matrix.size()), m(matrix[0].size()),
                                             sums(n + 1, vector<T>(m + 1, 0))
    {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                sums[i + 1][j + 1] = sums[i][j + 1] + sums[i + 1][j] - sums[i][j] + matrix[i][j];
            }
        }
    }

    T sumRegion(int row1, int col1, int row2, int col2) {
        return sums[row2 + 1][col2 + 1] -
               sums[row2 + 1][col1] -
               sums[row1][col2 + 1] +
               sums[row1][col1];
    }
};

pair<BigInt, BigInt> reduceGCD(BigInt numerator, BigInt denominator) {
    auto divisor = gcd(numerator, denominator);
    numerator /= divisor;
    denominator /= divisor;
    return {numerator, denominator};
}

BigInt getNumberOfSquares(int n, int size, int row, int col) {
    auto maxNumSquares = (n - size + 1) * (n - size + 1);
    auto numIntersectingSquares = (min(row + (size - 1), n - size) - max(0, row - (size - 1)) + 1) *
                                  (min(col + (size - 1), n - size) - max(0, col - (size - 1)) + 1);
    return maxNumSquares - numIntersectingSquares;
}

BigInt getNumberOfSquaresGT(int n, int size, int row, int col) {
    auto maxNumSquares = max(0, n - row - size) * (n - size + 1) + max(0, n - col - size + 1);
    auto numIntersectingSquares = (min(row + (size - 1), n - size) - (row + 1) + 1) *
                                  (min(col + (size - 1), n - size) - max(0, col - (size - 1)) + 1) +
                                  (min(col + (size - 1), n - size) - col + 1);
    return maxNumSquares - numIntersectingSquares;
}

int main() {
    auto n = Reader::read<int>();
    auto k = Reader::read<int>();

    auto matrix = Reader::readMatrix<BigInt>(n, n);
    SubmatrixSums submatrixSums(matrix);

    auto size = 2 * k - 1;

    BigInt totalSum = 0;
    BigInt totalNum = 0;

    for (auto row : range(n - (size - 1))) {
        for (auto col : range(n - (size - 1))) {
            auto sum = submatrixSums.sumRegion(row, col, row + size - 1, col + size - 1);

            auto numSquares = getNumberOfSquares(n, size, row, col);
            auto numSquaresGT = getNumberOfSquaresGT(n, size, row, col);

            totalSum += sum * numSquares;
            totalNum += numSquaresGT;
        }
    }

    auto [num, denum] = reduceGCD(totalSum, totalNum);
    Writer::writeln(to_string(num) + "/" + to_string(denum));

    return 0;
}

