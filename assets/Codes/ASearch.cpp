#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <functional>
#include <algorithm>

using namespace std;

struct Node {
    int x, y;
    double f_cost;
    bool operator==(const Node& other) const {
        return x == other.x && y == other.y;
    }
};

struct NodeHash {
    size_t operator()(const Node& node) const {
        return hash<int>()(node.x) ^ hash<int>()(node.y);
    }
};

double euclideanDistance(const Node& a, const Node& b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));

vector<Node> reconstructPath(unordered_map<Node, Node, NodeHash>& cameFrom, const Node& start, const Node& goal) {
    vector<Node> path;
    Node current = goal;
    while (!(current == start)) {
        path.push_back(current);
        current = cameFrom[current];
    }
    path.push_back(start);
    reverse(path.begin(), path.end());
    return path;
}

vector<Node> aStarSearch(const unordered_map<Node, vector<pair<Node, double>>, NodeHash>& graph, const Node& start, const Node& goal) {
    priority_queue<pair<double, Node>, vector<pair<double, Node>>, greater<>> openList;
    unordered_map<Node, double, NodeHash> gCost;
    unordered_map<Node, Node, NodeHash> cameFrom;

    openList.emplace(0, start);
    gCost[start] = 0;
    cameFrom[start] = start;

    while (!openList.empty()) {
        Node current = openList.top().second;
        openList.pop();

        if (current == goal) {
            break;
        }

        for (const auto& neighbor : graph.at(current)) {
            Node next = neighbor.first;
            double cost = neighbor.second;
            double newGCost = gCost[current] + cost;

            if (gCost.find(next) == gCost.end() || newGCost < gCost[next]) {
                gCost[next] = newGCost;
                double fCost = newGCost + euclideanDistance(next, goal);
                openList.emplace(fCost, next);
                cameFrom[next] = current;
            }
        }
    }

    return reconstructPath(cameFrom, start, goal);
}

int main() {

    unordered_map<Node, vector<pair<Node, double>>, NodeHash> graph;
    Node a{0, 0}, b{1, 0}, c{1, 1}, d{0, 1}, e{2, 1};

    graph[a] = {{b, 1.0}, {d, 1.0}};
    graph[b] = {{a, 1.0}, {c, 1.0}};
    graph[c] = {{b, 1.0}, {e, 1.0}};
    graph[d] = {{a, 1.0}, {e, 1.0}};
    graph[e] = {{c, 1.0}, {d, 1.0}};

    Node start{0, 0};
    Node goal{2, 1};

    vector<Node> path = aStarSearch(graph, start, goal);

    cout << "Optimal Path:";
    for (const auto& node : path) {
        cout << " (" << node.x << "," << node.y << ")";
    }
    cout << endl;

    return 0;
}
