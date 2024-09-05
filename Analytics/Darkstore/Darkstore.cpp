#include <iostream>
#include <ranges>
#include <algorithm>
#include <vector>
#include <numeric>

using namespace std;

namespace {
    auto range = [](auto bound) { return views::iota(0, bound); };
    auto rangeFrom = [](auto start, auto bound) { return views::iota(start, bound); };

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
    void writeln(const T &val) {
        cout << val << "\n";
    }
}

int maxSubarraySum(vector<int>& nums) {
    int curSum = 0;

    int minSum = 0;
    int maxDiff = nums[0];

    for (auto num : nums) {
        curSum += num;
        int diff = curSum - minSum;
        maxDiff = max(diff, maxDiff);
        minSum = min(curSum, minSum);
    }

    return maxDiff;
}

int main() {
    auto [n, m] = read<tuple<int, int>>();
    vector<vector<int>> matrix;

    for (auto row : range(n)) {
        matrix.push_back(readVector<int>(m));
    }

    auto maxSum = numeric_limits<int>::min();

    for (auto upperRow : range(n)) {
        vector<int> currentRowSums(m, 0);

        for (auto lowerRow : rangeFrom(upperRow, n)) {
            for (auto col : range(m)) {
                currentRowSums[col] += matrix[lowerRow][col];
            }
            auto currentSum = maxSubarraySum(currentRowSums);
            maxSum = max(currentSum, maxSum);
        }
    }

    writeln(maxSum);
}