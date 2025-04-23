/*
    Author: William Sid (wilsi748)

    Problem solved: Single source shortest path, time table - Shortestpath2
    (implementing djikstra algorithm with time sensitive traversal of edges)

    Time complexity: O((V+E)logV), where V is vertices (nodes) and E edges in the graph.
*/

#include <bits/stdc++.h>

using namespace std;

int inf = 1e9;

struct edge {
    int _to;
    int _from;
    // variables specific to this problem
    int _t0; // starttime
    int _P; // time interval
    int _d; // cost
    edge() : _to(-1), _from(-1), _t0(-1), _P(-1), _d(-1) {};
    edge (int to, int from, int t0, int P, int d) :  _to(to), _from(from), _t0(t0), _P(P), _d(d)  {}
    //Help function for this problem
    int getNextTime(int currentTime) {
        int dist = 0;
        if(_t0 >= currentTime && _P == 0) {
            return _t0 + _d;
        } else if (_P > 0) { 
            dist = _t0 + max(0, currentTime - _t0) / _P * _P;
            if(dist < currentTime) dist += _P;
            dist += _d;
            return dist;
        }
        return inf;
    }
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
void shortest_path_two(int start, vector<node>& nodes, vector<int>& parent_list) {
    priority_queue<node, vector<node>, greater<node>> pq;
    nodes[start]._dist = 0;
    pq.push(nodes[start]);
    while(!pq.empty()) {
        node k = pq.top();
        pq.pop();
        for(edge e : k._neighbours) {
            int dist = e.getNextTime(k._dist);
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
            int u, v, t0, P, d;
            cin >> u >> v >> t0 >> P >> d;
            nodes[u]._neighbours.push_back(edge(v, u, t0, P, d));
            //nodes[v]._neighbours.push_back(edge(u, v, t0, P, d)); //undirected graphs
        }
        vector<int> parent_list(nodes.size(), -1);
        shortest_path_two(s, nodes, parent_list);
        
        for(int j = 0; j < q; j++) {
            int query;
            cin >> query;
            if (nodes[query]._dist < inf) {
                cout << nodes[query]._dist << endl;
                //vector<int> path;
                //get_path(query, s, nodes, parent_list, path);
                //print_path(path);
            }else{
                cout << "impossible" << endl;
            }
        }
    }
    return 0;
}