#include <iostream>
#include <ranges>
#include <vector>
#include <algorithm>

using namespace std;

namespace {
    template<typename... Args>
    tuple<Args...> read() requires (sizeof...(Args) > 1) {
        tuple<Args...> t;
        apply([](auto&&... args) { (cin >> ... >> args); }, t);
        return t;
    }
    template<typename T>
    vector<T> readVector(size_t n) {
        vector<T> vec(n);
        ranges::for_each(vec, [](auto &val) { cin >> val; });
        return vec;
    }
    template<typename T>
    void write(const T &val, const string &sep = " ") {
        cout << val << sep;
    }
}

struct Interval {
    int start, end;

    bool operator <(const Interval &rhs) const {
        return start < rhs.start;
    }
};
istream &operator>>(istream &is, Interval &i) {
    is >> i.start >> i.end;
    return is;
}

int overlapLength(const vector<Interval>& blue, const vector<Interval>& red) {
    int totalOverlap = 0;

    for (int i = 0, j = 0; i < blue.size() && j < red.size(); ) {
        if (!(blue[i].end <= red[j].start || red[j].end <= blue[i].start)) {
            totalOverlap += min(blue[i].end, red[j].end) - max(blue[i].start, red[j].start);
        }

        if (blue[i].end < red[j].end) {
            ++i;
        } else {
            ++j;
        }
    }

    return totalOverlap;
}

int overlapWithShift(const vector<Interval> &blue, vector<Interval> &red, int shift) {
    vector<Interval> shiftedRed;
    for (const auto& rr : red) {
        shiftedRed.emplace_back(rr.start + shift, rr.end + shift);
    }

    return overlapLength(blue, shiftedRed);
}

int minCoverLength(vector<Interval>& blue, vector<Interval>& red, int left, int right) {
    ranges::sort(blue, &Interval::operator<);
    ranges::sort(red, &Interval::operator<);

    int minK = left - red.front().start;
    int maxK = right - red.back().end;

    int minLength = right - left;

    minLength = min(minLength, overlapWithShift(blue, red, minK));
    minLength = min(minLength, overlapWithShift(blue, red, maxK));

    for (const auto& b : blue) {
        for (const auto& r : red) {
            for (int shift : { b.start - r.end, b.end - r.start }) {
                if (shift < minK || shift > maxK) {
                    continue;
                }

                minLength = min(minLength, overlapWithShift(blue, red, shift));
            }
        }
    }

    return minLength;
}

int main() {
    auto [numBlue, numRed] = read<int, int>();
    auto [left, right] = read<int, int>();

    auto blue = readVector<Interval>(numBlue);
    auto red = readVector<Interval>(numRed);

    write(minCoverLength(blue, red, left, right));

    return 0;
}