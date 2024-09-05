#include <iostream>
#include <algorithm>
#include <vector>
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
    void writeln(const T &val) {
        cout << val << "\n";
    }
}

pair<string, vector<int>> extractPattern(string_view sv) {
    string pattern(1, sv[0]);
    vector<int> nums{1};
    for (int i = 1; i < sv.size(); ++i) {
        if (sv[i] != sv[i - 1]) {
            pattern += sv[i];
            nums.push_back(0);
        }
        nums.back()++;
    }
    return {pattern, nums};
}

int mid(int a, int b, int c) {
    array arr{a, b, c};
    ranges::nth_element(arr, arr.begin() + 1);
    return arr[1];
}

int main() {
    auto [str1, str2, str3] = readTuple<string, 3>();

    auto [pattern1, nums1] = extractPattern(str1);
    auto [pattern2, nums2] = extractPattern(str2);
    auto [pattern3, nums3] = extractPattern(str3);

    if (pattern1 != pattern2 || pattern2 != pattern3) {
        writeln("IMPOSSIBLE");
        return 0;
    }

    string result;
    for (int i = 0; i < nums1.size(); ++i) {
        result += string(mid(nums1[i], nums2[i], nums3[i]), pattern1[i]);
    }

    writeln(result);

    return 0;
}