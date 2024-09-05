#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

namespace {
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

int main() {
    auto n = read<int>();

    auto algorithms = readVector<int>(n);

    ranges::sort(algorithms, greater{});

    if (algorithms.front() == 0) {
        writeln(0);
        return 0;
    }

    long long linearComplexityIndex = 0;
    for (auto algorithm : algorithms) {
        if (algorithm < (linearComplexityIndex + 1) * (linearComplexityIndex + 1)) {
            break;
        }
        ++linearComplexityIndex;
    }

    writeln(linearComplexityIndex);
    return 0;
}