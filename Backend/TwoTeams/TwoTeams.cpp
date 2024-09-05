#include <iostream>
#include <algorithm>
#include <array>

using namespace std;

template<typename T, size_t N>
auto readTuple() {
    array<T, N> arr{};
    ranges::for_each(arr, [](auto &val) { cin >> val; });
    return arr;
}

template<typename T>
void writeln(const T &val) {
    cout << val << "\n";
}

int main() {
    auto [a, b, n] = readTuple<int, 3>();

    bool cond = a > (b / n + (b % n != 0));

    writeln(cond ? "Yes" : "No");

    return 0;
}
