/*
    Author: William Sid (wilsi748)

    Problem solved: Hiding places
*/
#include <bits/stdc++.h>

using namespace std;

int inf = 1e9;

struct position {
    int x;
    int y;
    position() : x(-1), y(-1) {}
    position(int x, int y) : x(x), y(y) {}
};

position add_positions(position& a, position& b) {
    return position(a.x + b.x, a.y + b.y);
}

bool in_bounds(position p) {
    return (p.x >= 0 && p.x <= 7) && (p.y >= 0 && p.y <= 7);
}
void search_bfs(vector<vector<int>>& dists, vector<position>& knight_moves, position& start) {
    queue<position> q;
    q.push(start);
    dists[start.x][start.y] = 0;
    while(!q.empty()) {
        position pos = q.front();
        q.pop();
        for(int i = 0; i < 8; i++) {
            position move = add_positions(pos, knight_moves[i]);
            if(in_bounds(move)) {
                if(dists[move.x][move.y] > dists[pos.x][pos.y] + 1) {
                    dists[move.x][move.y] = dists[pos.x][pos.y] + 1;
                    q.push(move);
                }
            }
        }
    }
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n;
    cin >> n;
    static const std::string_view alphabet = "abcdefghijklmnopqrstuvwxyz";
    vector<position> knight_moves(8);
    knight_moves[0] = position(2, 1);
    knight_moves[1] = position(-2, 1);
    knight_moves[2] = position(2, -1);
    knight_moves[3] = position(-2, -1);
    knight_moves[4] = position(1, 2);
    knight_moves[5] = position(-1, 2);
    knight_moves[6] = position(-1, -2);
    knight_moves[7] = position(1, -2);
    
    for(int i = 0; i < n; i++) {
        char c;
        cin >> c;
        int x;
        cin >> x;
        
        vector<vector<int>> dists(8, vector<int>(8, inf));
        position start = position(int(c-'a'), x-1);
        search_bfs(dists, knight_moves, start);
        
        int best = 0;
        for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) {
                best = max(best, dists[i][j]);
            }
        }
        cout << best << " ";

        for(int i = 7; i >= 0; i--) {
            for(int j = 0; j < 8; j++) {
                if(dists[j][i] == best) {
                    cout << alphabet[j] << i+1 << " ";
                }
            }
        }
        cout << endl;
    }
    return 0;
}