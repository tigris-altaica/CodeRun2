#include <iostream>
#include <ranges>
#include <algorithm>
#include <vector>

using namespace std;

namespace {
    auto range = [](auto bound) { return views::iota(0, bound); };
    auto rangeFrom = [](auto start, auto bound) { return views::iota(start, bound); };

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
    vector<vector<T>> readMatrix(size_t n, size_t m) {
        vector<vector<T>> mat(n, vector<T>(m));
        ranges::for_each(mat, [m](auto &row) { row = readVector<T>(m); });
        return mat;
    }

    template<typename T>
    void write(const T &val) {
        cout << val << " ";
    }
}

class LongestBeautifulPath {
    int length{0};
    int quantity{0};

public:
    void update(int newLength) {
        if (newLength > length) {
            length = newLength;
            quantity = 1;
        }
        else if (newLength == length) {
            ++quantity;
        }
    }

    int getLength() const {
        return length;
    }

    int getQuantity() const {
        return quantity;
    }
};

void visit(auto& grid, int row, int col, int length, LongestBeautifulPath& lbp) {
    int n = grid.size();

    bool down = row != n - 1 && grid[row + 1][col] < grid[row][col];
    bool up = row != 0 && grid[row - 1][col] < grid[row][col];
    bool right = col != n - 1 && grid[row][col + 1] < grid[row][col];
    bool left = col != 0 && grid[row][col - 1] < grid[row][col];

    if (!down && !up && !right && !left) {
        lbp.update(length);
        return;
    }

    if (down) {
        visit(grid, row + 1, col, length + 1, lbp);
    }
    if (up) {
        visit(grid, row - 1, col, length + 1, lbp);
    }
    if (right) {
        visit(grid, row, col + 1, length + 1, lbp);
    }
    if (left) {
        visit(grid, row, col - 1, length + 1, lbp);
    }
}


int main() {
    auto n = read<int>();
    auto grid = readMatrix<int>(n, n);

    LongestBeautifulPath lbp;

    for (auto col : range(n)) {
        visit(grid, 0, col, 1, lbp);
    }

    if (n > 1) {
        for (auto row : rangeFrom(1, n - 1)) {
            visit(grid, row, 0, 1, lbp);
            visit(grid, row, n - 1, 1, lbp);
        }

        for (auto col : range(n)) {
            visit(grid, n - 1, col, 1, lbp);
        }
    }

    write(lbp.getLength());
    write(lbp.getQuantity());
}