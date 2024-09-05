#include <iostream>
#include <array>
#include <algorithm>

using namespace std;

template<typename T>
T read() {
    T val{};
    cin >> val[0] >> val[1] >> val[2] >> val[3];
    return val;
}

template<typename T>
void writeln(const T &val) {
    cout << val << "\n";
}

int main() {
    auto queens = read<array<int, 4>>();

    ranges::sort(queens);

    int totalSum = 0;
    int sum = 4;
    for (int i = 0; i < 4; ++i) {
        if (sum < queens[i]) {
            writeln(4 - i);
            return 0;
        }
        sum -= queens[i];
        totalSum += queens[i];
    }

    writeln(totalSum < 2 ? 1 : 0);

    return 0;
}