#include <iostream>

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

int main() {
    auto black = read<int>();
    auto white = read<int>();

    for (int m = 1; ; ++m) {
        int n = (black + white) / m;
        if ((black + white) % m == 0 && (m - 2) * (n - 2) == white) {
            write(n);
            write(m);
            break;
        }
    }

    return 0;
}