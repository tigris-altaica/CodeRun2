#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <limits>
#include <queue>

using namespace std;
using BigInt = long long;

auto range = [](auto bound) { return views::iota(0, bound); };
auto rangeFrom = [](auto start, auto bound) { return views::iota(start, bound); };

namespace Reader {
    template<typename T>
    T read() {
        T val;
        cin >> val;
        return val;
    }

    template<typename T>
    vector <T> readVector(size_t n) {
        vector <T> vec(n);
        ranges::for_each(vec, [](auto &val) { cin >> val; });
        return vec;
    }

    template<typename T>
    vector <vector<T>> readMatrix(size_t n, size_t m) {
        vector <vector<T>> mat(n, vector<T>(m));
        ranges::for_each(mat, [m](auto &row) { row = readVector<T>(m); });
        return mat;
    }
}

namespace Writer {
    template<typename T>
    void write(const T &val, const string &sep = " ") {
        cout << val << sep;
    }
}

vector<BigInt> dijkstra(vector<vector<int>>& graph, int source) {
    int n = graph.size();
    vector<BigInt> distance(n, numeric_limits<BigInt>::max());
    distance[source] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.emplace(0, source);

    while (!pq.empty()) {
        auto [current_distance, current_vertex] = pq.top();
        pq.pop();

        if (current_distance > distance[current_vertex]) {
            continue;
        }

        for (auto neighbor : range(n)) {
            if (graph[current_vertex][neighbor] == -1) {
                continue;
            }

            int weight = graph[current_vertex][neighbor];
            BigInt new_distance = current_distance + weight;

            if (new_distance < distance[neighbor]) {
                distance[neighbor] = new_distance;
                pq.emplace(new_distance, neighbor);
            }
        }
    }

    return distance;
}

int main() {
    auto n = Reader::read<int>();
    auto adjMatrix = Reader::readMatrix<int>(n, n);

    const auto originalDists = dijkstra(adjMatrix, 0);

    auto maxModifiedDists = 0;

    for (auto vertex : rangeFrom(1, n)) {
        if (adjMatrix[0][vertex] == -1) {
            continue;
        }

        auto temp = adjMatrix[0][vertex];
        tie(adjMatrix[0][vertex], adjMatrix[vertex][0]) = make_tuple(-1, -1);

        auto dists = dijkstra(adjMatrix, 0);

        auto modifiedDists = inner_product(dists.begin(), dists.end(), originalDists.begin(), 0, plus{}, [](auto dist, auto origDist){
            return dist != origDist;
        });
        maxModifiedDists = max(modifiedDists, maxModifiedDists);

        tie(adjMatrix[0][vertex], adjMatrix[vertex][0]) = tie(temp, temp);
    }

    Writer::write(maxModifiedDists);
}