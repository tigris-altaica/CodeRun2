#include <iostream>
#include <ranges>

using namespace std;

namespace {
    auto range = [](auto bound){ return views::iota(0, bound); };
    auto rangeFrom = [](auto start, auto bound){ return views::iota(start, bound); };
    using BigInt = long long;

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

using BitMask = unsigned short;

BitMask extract(int val) {
    BitMask mask = 0;

    do {
        mask |= (1 << (val % 10));
        val /= 10;
    } while (val);

    return mask;
}

BigInt Cn2(BigInt n) {
    return n * (n - 1) / 2;
}

int main() {
    auto n = read<int>();

    array<BigInt, 1024> uniqueDigitsNumVals{};
    for (auto _ : range(n)) {
        auto val = read<int>();
        uniqueDigitsNumVals[extract(val)]++;
    }

    BigInt numPairs = 0;

    for (BitMask i : range(1024)) {
        if (uniqueDigitsNumVals[i] == 0) {
            continue;
        }

        numPairs += Cn2(uniqueDigitsNumVals[i]);
        for (BitMask j : rangeFrom(i + 1, 1024)) {
            if (i & j) {
                numPairs += uniqueDigitsNumVals[i] * uniqueDigitsNumVals[j];
            }
        }
    }

    writeln(numPairs);
}