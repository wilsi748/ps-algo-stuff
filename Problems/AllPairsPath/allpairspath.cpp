/*
    Author: William Sid (wilsi748)

    Problem solved: Shortest path all pairs, (implementing FLoyd Warshall )

    Time complexity: O(V^3), where V is vertices (nodes)
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


// FLoyd Warshall  
void shortest_path_all_pairs(vector<vector<int>>& dist, vector<node>& nodes, vector<edge>& edges) {
    
    // Setup distance matrix
    dist.resize(nodes.size());
    for (int i = 0; i < nodes.size(); i++) {
        dist[i].resize(nodes.size(), inf);
    }
    // Set path to itself to 0
    for (int i = 0; i < nodes.size(); i++) {
        dist[i][i] = 0;
    }

    // For each edge add its corresponding weight
    for (int i  = 0; i < edges.size(); i++) {
        edge& e = edges[i];
        if(e._from == e._to && e._cost > 0) continue;
        dist[e._from][e._to] = min(dist[e._from][e._to], e._cost);
    }

    // Tripple nested looops, the algo, :S
    for(int k = 0; k < nodes.size(); k++){
        for(int i = 0; i < nodes.size(); i++) {
            for(int j = 0; j < nodes.size(); j++) {
                if(dist[i][j] > dist[i][k] + dist[k][j] && dist[i][k] != inf && dist[k][j] != inf) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Handle negative cycles
    for(int k = 0; k < nodes.size(); k++){
        for(int i = 0; i < nodes.size(); i++) {
            for(int j = 0; j < nodes.size(); j++) {
                if(dist[k][k] < 0 && dist[i][k] != inf && dist[k][j] != inf) {
                    dist[i][j] = -inf;
                }
            }
        }
    }

    
}

int main() {
    int n, m, q;
    while(cin >> n && cin >> m && cin >> q) {
        if(n == 0 && m == 0 && q == 0) {
            break;
        }
        vector<node> nodes(n);
        vector<edge> edges;

        for(int i = 0; i < m; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            
            edges.push_back(edge(v, u, w));
            nodes[u]._neighbours.push_back(edge(v, u, w));
            //nodes[v]._neighbours.push_back(edge(u, v, w)); //undirected graphs
        }
        vector<vector<int>> dist; // distance table 
        shortest_path_all_pairs(dist, nodes, edges);
        
        for(int j = 0; j < q; j++) {
            int u, v;
            cin >> u >> v;
            if (dist[u][v] == inf) {
                cout << "Impossible" << endl;
            }else if (dist[u][v] == -inf) {
                cout << "-Infinity" << endl;;
            }else {
                cout << dist[u][v] << endl;
            }
        }
    }
    return 0;
}