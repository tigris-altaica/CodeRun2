#include <iostream>
#include <ranges>
#include <cmath>

using namespace std;

namespace {
    auto rangeFrom = [](auto start, auto bound) { return views::iota(start, bound); };
    template<typename T>
    T read() {
        T val;
        cin >> val;
        return val;
    }
    template<typename T>
    void writeln(const T &val) {
        cout << val << '\n';
    }
}

int countDivisors(int x) {
    int count = 0;
    for (int i : rangeFrom(1, int(sqrt(x)) + 1)) {
        if (x % i == 0) {
            count++;
            if (i != x / i) {
                count++;
            }
        }
    }
    return count;
}

pair<int, int> numberWithMaxDivisors(int n) {
    int maxDivisors = 0;
    int resultNumber = 0;

    for (int i : rangeFrom(1, n + 1)) {
        int divisorsCount = countDivisors(i);
        if (divisorsCount >= maxDivisors) {
            maxDivisors = divisorsCount;
            resultNumber = i;
        }
    }

    return { resultNumber, maxDivisors };
}

int main() {
    auto n = read<int>();

    auto [number, divisors] = numberWithMaxDivisors(n);

    writeln(number);
    writeln(divisors);

    return 0;
}