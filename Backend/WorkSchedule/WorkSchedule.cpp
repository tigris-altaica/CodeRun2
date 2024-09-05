#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <ranges>

using namespace std;

namespace {
    template<typename T>
    vector<T> readVector(size_t n) {
        vector<T> vec(n);
        ranges::for_each(vec, [](auto &val) { cin >> val; });
        return vec;
    }

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

struct Task {
    int lastDay;
    int stress;
};

istream &operator>>(istream &is, Task &t) {
    is >> t.lastDay >> t.stress;
    return is;
}

int main() {
    auto n = read<int>();

    vector<Task> tasks = readVector<Task>(n);

    ranges::sort(tasks, greater{}, &Task::stress);

    long long totalStress{0};

    auto days = views::iota(1, ranges::max_element(tasks, less{}, &Task::lastDay)->lastDay + 1);
    set<int, greater<>> availableDays(days.begin(), days.end());

    for (auto& [lastDay, stress] : tasks) {
        if (auto iter = availableDays.lower_bound(lastDay); iter != availableDays.end()) {
            availableDays.erase(iter);
            continue;
        }

        totalStress += stress;
    }

    writeln(totalStress);

    return 0;
}