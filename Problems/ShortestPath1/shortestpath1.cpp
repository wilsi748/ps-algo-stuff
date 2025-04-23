/*
    Author: William Sid (wilsi748)

    Problem solved: Single source shortest path, non-negative weights, shortest path 1 
                    (implementing djikstra algorithm)

    Time complexity: O((V+E)logV), where V is vertices (nodes) and E edges in the graph.
*/

#include <bits/stdc++.h>

using namespace std;

int inf = 1e9;

struct edge {
    int _to;
    int _from;
    int _cost;
    edge() : _to(-1), _from(-1), _cost(inf) {};
    edge (int to, int from, int cost) :  _to(to), _from(from), _cost(cost) {}
};

struct node {
    int _index;
    vector<edge> _neighbours; // adjacency for lower time complexity
    int _dist;
    node() :  _index(0), _neighbours(0), _dist(inf) {};
    node(int index, vector<edge> neighbours, int dist) : _index(index), _neighbours(neighbours), _dist(dist) {} 
};
bool operator > (const node& n1, const node& n2) {
    return (n1._dist > n2._dist); 
}


// Djikstra
void shortest_path_one(int start, vector<node>& nodes, vector<int>& parent_list) {
    priority_queue<node, vector<node>, greater<node>> pq;
    nodes[start]._dist = 0;
    pq.push(nodes[start]);
    while(!pq.empty()) {
        node k = pq.top();
        pq.pop();
        for(edge e : k._neighbours) {
            int dist = nodes[e._from]._dist + e._cost;
            if(dist < nodes[e._to]._dist) {
                nodes[e._to]._dist = dist;
                pq.push(nodes[e._to]);
                parent_list[e._to] = e._from;
            }
        }
    }
}

vector<int> get_path(int query, int start, vector<node>& nodes, vector<int>& parent_list, vector<int>& path) {
    while(true) {
        path.push_back(query);
        int prev = parent_list[query];
        if(prev == -1 && query == start) break;
        if(prev == -1) break;
        query = prev;
    }
    return path;
}

void print_path(vector<int>& path) {
    for(int i = 0; i < path.size(); i++) {
        cout << path[i] << "<";
    }
    cout << endl;
}

int main() {
    int n, m, q, s;
    while(cin >> n && cin >> m && cin >> q && cin >> s) {
        if(n == 0 && m == 0 && q == 0 && s == 0) {
            break;
        }
        node temp;
        vector<node> nodes(n, temp);
        
        for(int i = 0; i < m; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            nodes[u]._neighbours.push_back(edge(v, u, w));
            nodes[u]._index = u;
            //nodes[v]._neighbours.push_back(edge(u, v, w)); //undirected graphs
        }
        vector<int> parent_list(nodes.size(), -1);
        shortest_path_one(s, nodes, parent_list);
        
        for(int j = 0; j < q; j++) {
            int query;
            cin >> query;
            
            if (nodes[query]._dist < inf) {
                cout << nodes[query]._dist << endl;
                //vector<int> path;
                //get_path(query, s, nodes, parent_list, path); 
                //print_path(path);
            }else {
                cout << "impossible" << endl;
            }
        }
    }
    return 0;
}