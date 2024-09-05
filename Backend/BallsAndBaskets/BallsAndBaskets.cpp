#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

using namespace std;

namespace {
    using BigInt = long long;
    constexpr BigInt modulo = 1'000'000'000 + 7;

    istream &operator>>(istream &is, tuple<int,int,int> &t) {
        is >> get<0>(t) >> get<1>(t) >> get<2>(t);
        return is;
    }

    template<typename T>
    vector<T> readVector(size_t n) {
        vector<T> vec(n);
        ranges::for_each(vec, [](auto &val) { cin >> val; });
        return vec;
    }

    template<typename T>
    T read() {
        T val;
        cin >> val;
        return val;
    }

    template<typename T>
    void writeln(const T &val) {
        cout << val << "\n";
    }
}

BigInt modInv(BigInt a) {
    BigInt m = modulo;
    BigInt y = 0;
    BigInt x = 1;

    while (a > 1) {
        BigInt q = a / m;
        BigInt t = m;

        m = a % m;
        a = t;
        t = y;

        y = x - q * y;
        x = t;
    }

    if (x < 0) {
        x = x + modulo;
    }

    return x;
}

BigInt divide(BigInt a, BigInt b) {
    return (a * modInv(b)) % modulo;
}

int main() {
    auto n = read<int>();

    auto nums = readVector<BigInt>(n);
    vector<BigInt> prefixProducts{1};
    partial_sum(nums.begin(), nums.end(), back_inserter(prefixProducts), [](auto accum, auto &num) {
        return (accum * num) % modulo;
    });

    auto q = read<int>();

    for (int i = 0; i < q; ++i) {
        auto [type, left, right] = read<tuple<int,int,int>>();

        if (type == 0) {
            for (int cur = left; cur <= n; ++cur) {
                nums[cur - 1] += cur <= right;
                prefixProducts[cur] = (prefixProducts[cur - 1] * nums[cur - 1]) % modulo;
            }
        }
        else {
            writeln(divide(prefixProducts[right], prefixProducts[left - 1]));
        }
    }

    return 0;
}