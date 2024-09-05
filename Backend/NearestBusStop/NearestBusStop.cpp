#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <array>

using namespace std;

namespace {
    template<typename T, size_t N>
    auto readTuple() {
        array<T, N> arr{};
        ranges::for_each(arr, [](auto &val) { cin >> val; });
        return arr;
    }

    template<typename T>
    vector<T> readVector(size_t n) {
        vector<T> vec(n);
        ranges::for_each(vec, [](auto &val) { cin >> val; });
        return vec;
    }

    template<typename T>
    class FileReader {
    public:
        auto begin() {
            return istream_iterator<T>(cin);
        }

        auto end() {
            return istream_iterator<T>();
        }
    };

    template<typename T>
    void writeln(const T &val) {
        cout << val << "\n";
    }
}

int main() {
    auto [n, k] = readTuple<int, 2>();

    auto stops = readVector<int>(n);

    for (auto query : FileReader<int>()) {
        auto nextStop = ranges::lower_bound(stops, query);
        if (nextStop == stops.end() || nextStop != stops.begin() && query - *prev(nextStop) <= *nextStop - query) {
            --nextStop;
        }

        writeln(nextStop - stops.begin() + 1);
    }

    return 0;
}