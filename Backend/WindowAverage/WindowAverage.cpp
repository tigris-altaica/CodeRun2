#include <iostream>
#include <ranges>
#include <format>
#include <vector>
#include <algorithm>
#include <numeric>

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

double maximumWindowAverage(vector<int>& arr, int windowSize) {
    auto exists = [&](double val) {
        double sum = accumulate(arr.begin(), arr.begin() + windowSize, 0.0, [val](auto accum, auto& cur){
            return accum + (cur - val);
        });
        if (sum >= 0) {
            return true;
        }
        double windowOffsetSum = 0.0;
        double minWindowOffsetSum = 0.0;
        for (auto i : rangeFrom(windowSize, arr.size())) {
            sum += arr[i] - val;
            windowOffsetSum += arr[i - windowSize] - val;
            minWindowOffsetSum = min(minWindowOffsetSum, windowOffsetSum);
            if (sum >= minWindowOffsetSum) {
                return true;
            }
        }
        return false;
    };

    double left = *ranges::min_element(arr);
    double right = *ranges::max_element(arr);

    while (right - left >= 1e-6) {
        double mid = (left + right) / 2;
        if (exists(mid)) {
            left = mid;
        }
        else {
            right = mid;
        }
    }

    return left;
}

int main() {
    auto size = read<int>();
    auto windowSize = read<int>();
    auto arr = readVector<int>(size);

    write(format("{:.6f}", maximumWindowAverage(arr, windowSize)));

    return 0;
}