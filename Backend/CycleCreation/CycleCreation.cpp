#include <iostream>
#include <vector>
#include <ranges>


using namespace std;
using BigInt = long long;
auto range = [](auto bound) { return views::iota(0, bound); };

namespace Reader {
    template<typename... Args>
    tuple<Args...> read() requires (sizeof...(Args) > 1) {
        tuple<Args...> t;
        apply([](auto &&... args) { (cin >> ... >> args); }, t);
        return t;
    }
}
namespace Writer {
    template<typename T>
    void write(const T &val, const string &sep = " ") {
        cout << val << sep;
    }
}

class UnionFind {
public:
    explicit UnionFind(int sz) : parent(sz), size(sz) {
        for (auto i : range(sz)) {
            parent[i] = i;
            size[i] = 1;
        }
    }

    int find(int x) {
        if (x == parent[x]) {
            return x;
        }
        return parent[x] = find(parent[x]);
    }

    void unionSet(int x, int y) {
        x = find(x);
        y = find(y);
        if (x != y) {
            if (size[x] < size[y]) {
                swap(x, y);
            }
            parent[y] = x;
            size[x] += size[y];
        }
    }

    int componentSize(int x) {
        return size[x];
    }

private:
    vector<int> parent;
    vector<int> size;
};

class Graph {
public:
    explicit Graph(int vertices) : vertices(vertices),
                                   adjList(vertices),
                                   disc(vertices, -1),
                                   low(vertices, -1),
                                   bridges(vertices) { };

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    BigInt countPossibleOneCycleEdges()  {
        for (auto i : range(vertices)) {
            if (disc[i] == -1) {
                dfs(i, -1);
            }
        }

        BigInt result = 0;
        vector<bool> visited(vertices, false);
        for (auto i : range(vertices)) {
            auto root = bridges.find(i);
            if (visited[root]) {
                continue;
            }
            visited[root] = true;

            BigInt sz = bridges.componentSize(root);
            result += sz * (sz - 1) / 2 - (sz - 1);
        }

        return result;
    }

private:
    void dfs(int u, int parent)  {
        disc[u] = low[u] = ++time;

        for (int v : adjList[u]) {
            if (disc[v] == -1) {
                dfs(v, u);

                low[u] = min(low[u], low[v]);

                if (low[v] > disc[u]) {
                    bridges.unionSet(u, v);
                }
            }
            else if (v != parent) {
                low[u] = min(low[u], disc[v]);
            }
        }
    }

    int vertices;
    vector<vector<int>> adjList;
    vector<int> disc;
    vector<int> low;
    UnionFind bridges;
    int time{0};
};

int main() {
    auto [numVertices, numEdges] = Reader::read<int, int>();
    Graph graph(numVertices);

    for (auto _ : range(numEdges)) {
        auto [from, to] = Reader::read<int, int>();
        graph.addEdge(from - 1, to - 1);
    }

    Writer::write(graph.countPossibleOneCycleEdges());
}