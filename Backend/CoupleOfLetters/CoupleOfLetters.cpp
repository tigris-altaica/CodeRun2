#include <iostream>
#include <algorithm>
#include <array>

using namespace std;

namespace {
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

int main() {
    array<int, 26 * 26> bigrammFreqs{};

    for (auto word = read<string>(); !word.empty(); word = read<string>()) {
        for (int i = 0; i < word.size() - 1; ++i) {
            bigrammFreqs[26 * (word[i] - 'A') + (word[i + 1] - 'A')]++;
        }
    }

    auto maxFreqIter = ranges::max_element(bigrammFreqs);

    auto riter = ranges::find(bigrammFreqs.rbegin(), bigrammFreqs.rend(), *maxFreqIter);
    auto idx = bigrammFreqs.rend() - riter - 1;
    char first = 'A' + (idx / 26), second = 'A' + (idx % 26);
    writeln(string{first, second});

    return 0;
}
