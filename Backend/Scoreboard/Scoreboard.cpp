#include <iostream>
#include <ranges>
#include <algorithm>
#include <unordered_map>

using namespace std;

auto range = [](auto bound) { return views::iota(0, bound); };

template<class... Args>
istream &operator>>(istream &is, tuple<Args...> &t) {
    apply([&is](auto &&... args) { ((is >> args), ...); }, t);
    return is;
}

namespace Reader {
    template<typename T>
    T read() {
        T val;
        cin >> val;
        return val;
    }
}

namespace Writer {
    template<typename T>
    void write(const T &val, const string &sep = " ") {
        cout << val << sep;
    }
}

int main() {
    unordered_map<string, int> topScorers;

    auto numPlayers = Reader::read<int>();
    for (auto i : range(numPlayers)) {
        Reader::read<string>();
    }

    auto numHighlights = Reader::read<int>();

    int score1Total = 0, score2Total = 0;

    for (auto _ : range(numHighlights)) {
        auto [scoreStr, player] = Reader::read<tuple<string, string>>();
        auto sep = scoreStr.find(':');
        int score1 = stoi(scoreStr.substr(0, sep)), score2 = stoi(scoreStr.substr(sep + 1));
        topScorers[player] += (score1 - score1Total) + (score2 - score2Total);
        tie(score1Total, score2Total) = tie(score1, score2);
    }

    auto topScorerIter = ranges::max_element(topScorers, [](auto& lhs, auto& rhs){
        return tie(lhs.second, lhs.first) < tie(rhs.second, rhs.first);
    });

    Writer::write(topScorerIter->first);
    Writer::write(topScorerIter->second);

    return 0;
}