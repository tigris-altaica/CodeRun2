#include <iostream>
#include <vector>
#include <ranges>
#include <numeric>
#include <iomanip>
#include <sstream>

using namespace std;

template<class... Args>
istream &operator>>(istream &is, tuple<Args...> &t) {
    apply([&is](auto &&... args) { (is >> ... >> args); }, t);
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
    void writeln(const T &val) {
        cout << val << '\n';
    }
}

int toMins(string& s) {
    auto hours = stoi(s.substr(0, 2));
    auto mins = stoi(s.substr(3, 2));

    return hours * 60 + mins;
}

string fromMins(int m) {
    stringstream ss;
    ss << setw(2) << setfill('0') << m / 60 << ":" << setw(2) << setfill('0') << m % 60;
    return ss.str();
}

int main() {
    auto [st1, st2, p1, p2] = Reader::read<tuple<string, string, string, string>>();
    auto startTime1 = toMins(st1), startTime2 = toMins(st2), period1 = toMins(p1), period2 = toMins(p2);

    if (abs(startTime1 - startTime2) % gcd(period1, period2) != 0) {
        Writer::writeln("Never");
        return 0;
    }

    auto [maxPeriodStartTime, maxPeriod] = period1 > period2 ? tie(startTime1, period1) : tie(startTime2, period2);
    auto [minPeriodStartTime, minPeriod] = period1 <= period2 ? tie(startTime1, period1) : tie(startTime2, period2);

    auto curTime = maxPeriodStartTime +
            (max(0, minPeriodStartTime - maxPeriodStartTime) / maxPeriod +
             (max(0, minPeriodStartTime - maxPeriodStartTime) % maxPeriod != 0)) * maxPeriod;
    while ((curTime - minPeriodStartTime) % minPeriod != 0) {
        curTime += maxPeriod;
    }

    vector<string> daysOfWeek = {
            "Saturday",
            "Sunday",
            "Monday",
            "Tuesday",
            "Wednesday",
            "Thursday",
            "Friday"
    };
    constexpr auto minsInDay = 24 * 60;

    auto numDays = curTime / minsInDay;
    auto& dayOfWeek = daysOfWeek[numDays % 7];
    auto time = fromMins(curTime % minsInDay);

    Writer::writeln(dayOfWeek);
    Writer::writeln(time);
    return 0;
}