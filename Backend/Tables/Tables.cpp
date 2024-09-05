#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <unordered_map>
#include <stack>
#include <numeric>
#include <unordered_set>

using namespace std;
namespace {
    auto range = [](auto bound) { return views::iota(0, bound); };

    template<typename T>
    T read() {
        T val;
        cin >> val;
        return val;
    }

    template<typename... Args>
    tuple<Args...> read() requires (sizeof...(Args) > 1) {
        tuple<Args...> t;
        apply([](auto&&... args) { (cin >> ... >> args); }, t);
        return t;
    }

    template<typename T>
    void write(const T &val) {
        cout << val;
    }
}

struct Row {
    vector<int> numbers;
    int numZeroes{0};

    bool operator == (const Row& rhs) const {
        return numbers == rhs.numbers;
    }
};

bool dfs(const auto& adjList, int source, auto& visited, const vector<Row>& table) {
    stack<int> s;
    s.push(source);
    bool wasZero = false;

    while (!s.empty()) {
        auto u = s.top();
        s.pop();

        if (visited[u]) { continue; }
        visited[u] = true;

        wasZero |= (table[u].numZeroes > 0);

        for (auto v : adjList.at(u)) {
            if (!visited[v]) {
                s.push(v);
            }
        }
    }

    return !wasZero;
}

vector<Row> readTable(int n, int m) {
    vector<Row> table;
    for (auto i : range(n)) {
        Row row;
        for (auto j : range(m)) {
            auto number = read<int>();
            if (number == 0) {
                row.numZeroes++;
                continue;
            }
            row.numbers.push_back(number);
        }
        table.push_back(row);
    }
    return table;
}

unordered_map<int, int> createMapping(vector<Row> &table) {
    int n = table.size();
    unordered_map<int, int> mapping;
    for (auto i : range(n)) {
        for (auto num : table[i].numbers) {
            mapping[num] = i;
        }
    }
    return mapping;
}

vector<int> findLIS(const vector<int>& arr) {
    if (arr.empty()) return {};

    vector<int> lis; // Вспомогательный массив для хранения концов подпоследовательностей
    vector<int> prev(arr.size(), -1); // Массив для восстановления последовательности
    vector<int> indices; // Массив для хранения индексов элементов в LIS

    for (int i = 0; i < arr.size(); ++i) {
        // Используем двоичный поиск для нахождения позиции вставки
        auto it = lower_bound(lis.begin(), lis.end(), arr[i]);
        int pos = it - lis.begin();

        // Если элемент больше всех текущих, добавляем его
        if (it == lis.end()) {
            lis.push_back(arr[i]);
            indices.push_back(i);
        } else {
            *it = arr[i];
            indices[pos] = i;
        }

        // Запоминаем индекс предыдущего элемента в последовательности
        if (pos > 0) {
            prev[i] = indices[pos - 1];
        }
    }

    // Восстанавливаем последовательность
    vector<int> result;
    for (int i = indices.back(); i >= 0; i = prev[i]) {
        result.push_back(arr[i]);
    }

    reverse(result.begin(), result.end()); // Обратим порядок, чтобы получить правильную последовательность

    return result;
}

vector<int> findLCS(const vector<int> &a, const vector<int> &b) {
    //Define a sequence C. C[i] is the index of B[i] in A. (A[C[i]] = B[i])
    //LCS of A and B is the longest increasing subsequence of C.
    unordered_map<int, int> m;
    for (int i = 0; i < a.size(); ++i) {
        m[a[i]] = i;
    }
    vector<int> c;
    for (int i = 0; i < b.size(); ++i) {
        if (!m.contains(b[i])) {
            continue;
        }
        c.push_back(m[b[i]]);
    }

    auto cLIS = findLIS(c);
    vector<int> LCS;
    for (int i = 0; i < cLIS.size(); ++i) {
        LCS.push_back(a[cLIS[i]]);
    }

    return LCS;
}

int main() {
    auto [n, m] = read<int, int>();

    auto table1 = readTable(n, m);
    auto table2 = readTable(n, m);

    if (table1 == table2) {
        write(0);
        return 0;
    }

    int totalNumZeroes = accumulate(table1.begin(), table1.end(), 0, [](auto accum, Row& row){
        return accum + row.numZeroes;
    });
    if (totalNumZeroes == 0) {
        write(-1);
        return 0;
    }

    auto valueToTargetRow = createMapping(table2);

    unordered_map<int, vector<int>> adjList;
    int numEdges = 0;

    for (auto curRow : range(n)) {
        auto lcs = findLCS(table1[curRow].numbers, table2[curRow].numbers);
        unordered_set lcsSet(lcs.begin(), lcs.end());

        for (auto num : table1[curRow].numbers) {
            if (lcsSet.contains(num)) {
                continue;
            }
            adjList[curRow].push_back(valueToTargetRow[num]);
            numEdges++;
        }
    }

    int extraMoves = 0;
    vector<bool> visited(n, false);
    for (const auto& [vertex, _] : adjList) {
        if (!visited[vertex]) {
            extraMoves += dfs(adjList, vertex, visited, table1);
        }
    }

    write(numEdges + extraMoves);
}