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
    cout << val;
}

int eulerPhiFunction(int n) {
    int result = n;

    for (int p = 2; p * p <= n; ++p) {
        if (n % p == 0) {
            while (n % p == 0) {
                n /= p;
            }
            result -= result / p;
        }
    }

    if (n > 1) {
        result -= result / n;
    }

    return result;
}

int main() {
    auto n = read<int>();

    write(eulerPhiFunction(n));

    return 0;
}
