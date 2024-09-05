#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <cmath>
#include <stack>

using namespace std;
namespace {
    auto Inf = numeric_limits<double>::max();
    
    auto range = [](auto bound) { return views::iota(0, bound); };
    auto rangeFrom = [](auto start, auto bound) { return views::iota(start, bound); };

    template<typename... Args>
    tuple<Args...> read() requires (sizeof...(Args) > 1) {
        tuple<Args...> t;
        apply([](auto&&... args) { (cin >> ... >> args); }, t);
        return t;
    }

    template<typename... Args>
    vector<tuple<Args...>> readVector(size_t n) requires (sizeof...(Args) > 1) {
        vector<tuple<Args...>> vec(n);
        ranges::for_each(vec, [](auto& t){
            apply([](auto&&... args){ (cin >> ... >> args); }, t);
        });
        return vec;
    }

    template<typename T>
    void write(const T &val) {
        cout << val;
    }
}

array<array<bool, 4>, 4> makeCornerConnections(auto& wc) {
    const auto [bottom, right, top, left] = array{0, 1, 2, 3};
    array<bool, 4> fromBottomLeft {
            true,
            !(wc[bottom][left] || wc[bottom][right] || wc[bottom][top]),
            !(wc[bottom][top] || wc[left][right] || wc[right][top] || wc[left][bottom]),
            !(wc[left][bottom] || wc[left][right] || wc[left][top])
    };
    array<bool, 4> fromBottomRight {
            !(wc[bottom][left] || wc[bottom][right] || wc[bottom][top]),
            true,
            !(wc[right][top] || wc[right][left] || wc[right][bottom]),
            !(wc[right][bottom] || wc[top][bottom] || wc[left][right] || wc[left][top])
    };
    array<bool, 4> fromTopRight {
            !(wc[bottom][top] || wc[left][right] || wc[right][top] || wc[left][bottom]),
            !(wc[right][top] || wc[right][left] || wc[right][bottom]),
            true,
            !(wc[top][left] || wc[top][right] || wc[top][bottom])
    };
    array<bool, 4> fromTopLeft {
            !(wc[left][bottom] || wc[left][right] || wc[left][top]),
            !(wc[right][bottom] || wc[top][bottom] || wc[left][right] || wc[left][top]),
            !(wc[top][left] || wc[top][right] || wc[top][bottom]),
            true,
    };
    return { fromBottomLeft, fromBottomRight, fromTopRight, fromTopLeft };
}

array<array<bool, 4>, 4> makeWallConnections(const auto &maximalDiameters, int diameter) {
    array<array<bool, 4>, 4> wallConnections{};
    for (int wall1 : range(4)) {
        for (int wall2 : rangeFrom(wall1, 4)) {
            wallConnections[wall1][wall2] = wallConnections[wall2][wall1] = diameter > maximalDiameters[wall1][wall2];
        }
    }
    return wallConnections;
}

void dfs(const auto& adjMatrix, int source, double threshold, auto& visited) {
    stack<int> s;
    s.push(source);

    while (!s.empty()) {
        auto u = s.top();
        s.pop();

        if (visited[u]) { continue; }
        visited[u] = true;

        for (auto v : range(int(adjMatrix.size()))) {
            if (adjMatrix[u][v] < threshold && !visited[v]) {
                s.push(v);
            }
        }
    }
}

double calcDistance(auto circle1, auto circle2) {
    auto [x1, y1, radius1] = circle1;
    auto [x2, y2, radius2] = circle2;
    return max(0.0, sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)) - (radius1 + radius2));
}

double findMaxDiameter(const auto& adjMatrix, int width, int height, int wall1, int wall2) {
    double left = 0.0;
    double right = min(width, height);

    while (right - left >= 0.1) {
        vector<bool> visited(adjMatrix.size(), false);
        double mid = (right + left) / 2.0;

        dfs(adjMatrix, wall1, mid, visited);

        if (visited[wall2]) {
            right = mid;
        }
        else {
            left = mid;
        }
    }

    return floor(right);
}

vector<vector<double>> createAdjacencyMatrix(const auto &obstacles, int width, int height) {
    int numObstacles = obstacles.size();
    vector<vector<double>> adjMatrix(numObstacles + 4, vector<double>(numObstacles + 4, Inf));
    const auto [bottomWall, rightWall, topWall, leftWall] = array{0, 1, 2, 3};

    adjMatrix[bottomWall + numObstacles][bottomWall + numObstacles] =
        adjMatrix[rightWall + numObstacles][rightWall + numObstacles] =
            adjMatrix[topWall + numObstacles][topWall + numObstacles] =
                adjMatrix[leftWall + numObstacles][leftWall + numObstacles] = 0.0;

    for (auto i : range(numObstacles)) {
        for (auto j : rangeFrom(i, numObstacles)) {
            adjMatrix[i][j] = adjMatrix[j][i] = calcDistance(obstacles[i], obstacles[j]);
        }

        auto [x, y, radius] = obstacles[i];
        adjMatrix[i][bottomWall + numObstacles] = adjMatrix[bottomWall + numObstacles][i] = y - radius;
        adjMatrix[i][rightWall + numObstacles] = adjMatrix[rightWall + numObstacles][i] = width - (x + radius);
        adjMatrix[i][topWall + numObstacles] = adjMatrix[topWall + numObstacles][i] = height - (y + radius);
        adjMatrix[i][leftWall + numObstacles] = adjMatrix[leftWall + numObstacles][i] = x - radius;
    }

    return adjMatrix;
}

array<array<double, 4>, 4> findMaximalDiameters(int width, int height, const auto &adjMatrix) {
    int numObstacles = adjMatrix.size() - 4;
    array<array<double, 4>, 4> maximalDiameters{};
    maximalDiameters.fill({Inf, Inf, Inf, Inf});
    for (int wall1 : range(4)) {
        for (int wall2 : rangeFrom(wall1 + 1, 4)) {
            maximalDiameters[wall1][wall2] = maximalDiameters[wall2][wall1] =
                    findMaxDiameter(adjMatrix, width, height, wall1 + numObstacles, wall2 + numObstacles);
        }
    }
    return maximalDiameters;
}

int main() {
    auto [numObstacles, numQueries] = read<int, int>();
    auto [width, height] = read<int, int>();
    auto obstacles = readVector<int, int, int>(numObstacles);

    auto adjMatrix = createAdjacencyMatrix(obstacles, width, height);

    auto maximalDiameters = findMaximalDiameters(width, height, adjMatrix);

    for (auto _ : range(numQueries)) {
        auto [radius, corner] = read<int, int>();

        auto wallConnections = makeWallConnections(maximalDiameters, 2 * radius);
        auto cornerConnections = makeCornerConnections(wallConnections);

        for (auto targetCorner : range(4)) {
            if (cornerConnections[corner - 1][targetCorner]) {
                write(targetCorner + 1);
            }
        }

        write('\n');
    }
}