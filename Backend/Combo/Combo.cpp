#include <iostream>
#include <ranges>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

auto range = [](auto bound) { return views::iota(0, bound); };

namespace Reader {
    template<typename T>
    T read() {
        T val;
        cin >> val;
        return val;
    }
    template<typename T>
    auto readArray() {
        array<T, 4> val{};
        cin >> val[0] >> val[1] >> val[2] >> val[3];
        return val;
    }
    template<typename T>
    vector<T> readVector(size_t n) {
        vector<T> vec(n);
        ranges::for_each(vec, [](auto &val) { cin >> val; });
        return vec;
    }
}

namespace Writer {
    template<typename T>
    void write(const T &val, const string &sep = " ") {
        cout << val << sep;
    }
}

int main() {
    auto numProducts = Reader::read<int>();
    auto productPrices = Reader::readVector<int>(numProducts);
    auto comboPrice = Reader::read<int>();
    auto comboProducts = Reader::readArray<int>();
    auto numDesiredProducts = Reader::read<int>();
    vector<int> desiredProductsQuantity(numProducts, 0);
    for (auto _ : range(numDesiredProducts)) {
        desiredProductsQuantity[Reader::read<int>() - 1]++;
    }

    int numCombos = 0;
    while (true) {
        int sumWithoutCombo = 0;
        for (auto comboProduct : comboProducts) {
            sumWithoutCombo += productPrices[comboProduct - 1] * (desiredProductsQuantity[comboProduct - 1] > 0);
        }

        if (sumWithoutCombo < comboPrice) {
            break;
        }

        for (auto comboProduct : comboProducts) {
            desiredProductsQuantity[comboProduct - 1] -= 1 * (desiredProductsQuantity[comboProduct - 1] > 0);
        }
        ++numCombos;
    }

    auto finalSum = numCombos * comboPrice + inner_product(productPrices.begin(), productPrices.end(),
                                                           desiredProductsQuantity.begin(),
                                                           0);
    Writer::write(finalSum);

    return 0;
}