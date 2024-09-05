#include <iostream>
#include <vector>
#include <array>

using namespace std;

template<typename T>
T read() {
    T val;
    cin >> val;
    return val;
}

template<typename T>
void write(const T &val) {
    cout << val << " ";
}

class FreqCounter {
    static constexpr size_t numDistinctChars = 26;
    array<int, numDistinctChars> freqs{};

    static int idx(char ch) {
        return ch - 'a';
    }

public:
    FreqCounter() = default;

    void inc(char ch) {
        freqs[idx(ch)]++;
    }

    FreqCounter operator - (const FreqCounter &rhs) const {
        FreqCounter res;
        for (auto i = 0; i < numDistinctChars; ++i) {
            res.freqs[i] = freqs[i] - rhs.freqs[i];
        }
        return res;
    }

    bool operator == (const FreqCounter &rhs) const {
        for (auto i = 0; i < numDistinctChars; ++i) {
            if (freqs[i] != rhs.freqs[i]) {
                return false;
            }
        }
        return true;
    }
};

vector<int> getDivisors(int n) {
    vector<int> divisors;
    for (int i = 1; i <= n / 2; ++i) {
        if (n % i == 0) {
            divisors.push_back(i);
        }
    }
    return divisors;
}

auto getFrequenciesPrefixSums(string_view sv) {
    vector<FreqCounter> prefixSums{{}};
    for (auto ch : sv) {
        prefixSums.push_back(prefixSums.back());
        prefixSums.back().inc(ch);
    }
    return prefixSums;
}

bool allFrequenciesAreEqual(auto& freqsPrefixSums, int step) {
    FreqCounter current = freqsPrefixSums[step] - freqsPrefixSums[0];
    for (int start = step; start + step < freqsPrefixSums.size(); start += step) {
        if (freqsPrefixSums[start + step] - freqsPrefixSums[start] != current) {
            return false;
        }
    }
    return true;
}

int main() {
    auto s = read<string>();

    auto frequenciesPrefixSums = getFrequenciesPrefixSums(s);
    auto divisors = getDivisors(s.size());

    for (auto divisor : divisors) {
        if (allFrequenciesAreEqual(frequenciesPrefixSums, divisor)) {
            write(s.size() / divisor);
            return 0;
        }
    }

    write(1);
    return 0;
}