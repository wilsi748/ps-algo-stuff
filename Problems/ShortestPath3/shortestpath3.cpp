/*
    Author: William Sid (wilsi748)

    Problem solved: Single source shortest path, negative weights, shortest path 3 (implementing Bellman-ford)

    Time complexity: O(|V| * |E|), where V is vertices (nodes) and E edges in the graph.
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
    vector<edge> _neighbours; // adjacency for lower time complexity
    int _dist;
    node() :  _neighbours(0), _dist(inf) {};
    node( vector<edge> neighbours, int dist) :  _neighbours(neighbours), _dist(dist) {} 
};
bool operator > (const node& n1, const node& n2) {
    return (n1._dist > n2._dist); 
}


// Bellman-ford  O(|V| * |E|)
void shortest_path_three(int start, vector<node>& nodes, vector<edge>& edges, vector<int>& parent_list) {
    nodes[start]._dist = 0;
    // |V|-1 relaxations
    for(int it = 1; it < nodes.size(); it++) {
        for(int i = 0; i < edges.size(); i++) {
            edge& e = edges[i];
            if(nodes[e._from]._dist != inf) {
                nodes[e._to]._dist = min(nodes[e._to]._dist, nodes[e._from]._dist + e._cost);
                parent_list[e._to] = e._from;
            }
        }   
    }
    // Handle negative costs
    for(int it = 1; it < nodes.size(); it++) {
        for(int i = 0; i < edges.size(); i++) {
            edge& e = edges[i];
            if(nodes[e._from]._dist == inf) continue;
            if(nodes[e._from]._dist + e._cost < nodes[e._to]._dist) {
                nodes[e._to]._dist = -inf;
            }
        }
    }
}

/****
 * Function to get the path.
*/
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

/****
 * Function to print the path.
*/
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
        vector<edge> edges;
        for(int i = 0; i < m; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            // Maybe time to just do a graph struct
            edges.push_back(edge(v, u, w));
            nodes[u]._neighbours.push_back(edge(v, u, w));
            //nodes[v]._neighbours.push_back(edge(u, v, w)); //undirected graphs
        }
        vector<int> parent_list(nodes.size(), -1);
        shortest_path_three(s, nodes, edges, parent_list);
        
        for(int j = 0; j < q; j++) {
            int query;
            cin >> query;
            if (nodes[query]._dist == inf) {
                cout << "Impossible" << endl;
            }else if (nodes[query]._dist == -inf) {
                cout << "-Infinity" << endl;;
            }else {
                cout << nodes[query]._dist << endl;
                //vector<int> path;
                //get_path(query, s, nodes, parent_list, path); 
                //print_path(path);
            }
        }
    }
    return 0;
}