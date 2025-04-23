#include <iostream>
#include <algorithm>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

int INF = 1e9;

struct edge {
    int n;
    double dist;
    edge (int n, double dist) : n(n), dist(dist) {}
};

struct node {
    int _cost;
    int _fuel;
    int _id;
    node(int cost, int fuel, int id) : _cost(cost), _fuel(fuel), _id(id) {}
    string toString() { return to_string(_cost) + " " + to_string(_fuel) + " " + to_string(_id); } 
};
bool operator > (const node& n1, const node& n2) {
    return (n1._cost > n2._cost); 
}

int find_path_cost(vector<int>& fuel_prices, vector<vector<edge>>& roads, int cap, int start, int goal) {
    vector<vector<int>> tree_graph(roads.size(), vector<int>(cap + 1, INF));
    vector<vector<bool>> visited(roads.size(), vector<bool>(cap + 1, false));
    priority_queue<node, vector<node>, greater<node>> pq;
    
    pq.push(node(0, 0, start));
    tree_graph[start][0] = 0;

    while(!pq.empty()) {
        node n = pq.top();
        //cout << n.toString() << endl;
        pq.pop();
        if(visited[n._id][n._fuel]) continue;
        
        if(goal == n._id) break;

        if(n._fuel < cap && n._cost + fuel_prices[n._id] < tree_graph[n._id][n._fuel+1]) {
            tree_graph[n._id][n._fuel+1] = n._cost + fuel_prices[n._id];
            pq.push(node(n._cost + fuel_prices[n._id], n._fuel+1, n._id));
        }

        for(edge& e : roads[n._id]) {
            if(n._fuel >= e.dist && tree_graph[n._id][n._fuel] < tree_graph[e.n][n._fuel - e.dist]) {
                tree_graph[e.n][n._fuel - e.dist] = tree_graph[n._id][n._fuel];
                pq.push(node(tree_graph[e.n][n._fuel-e.dist], n._fuel-e.dist, e.n));
            }
        }
        visited[n._id][n._fuel] = true;
    }
    return tree_graph[goal][0];
}

int main() {
    int n, m;
    cin >> n >> m;
    
    vector<int> fuel_prices(n);
    for(int i = 0; i < n; i++) {
        cin >> fuel_prices[i];
    }

    vector<vector<edge>> roads(m);
    for(int i = 0; i < m; i++) {
        int u, v, d;
        cin >> u >> v >> d;
        roads[u].emplace_back(v, d);
        roads[v].emplace_back(u, d);
    }
    
    int q;
    cin >> q;

    for(int i = 0; i < q; i++) {
        int cap, start, end;
        cin >> cap >> start >> end;
        int path_cost = find_path_cost(fuel_prices, roads, cap, start, end);
        if(path_cost < INF) {
            cout << path_cost << endl;
        } else {
            cout << "impossible" << endl;
        }
    }

    return 0;
}