#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

bool senseTrap(int x, int y, vector<vector<char>>& map) {
    return map[y+1][x] == 'T' || map[y-1][x] == 'T' || map[y][x+1] == 'T' || map[y][x-1] == 'T';
}

void searchMap(int x, int y, vector<vector<char>>& map, vector<vector<bool>>& v, int& golds) {
    if(x < 1 || y < 1 || x > map[0].size() || y > map.size()) {return;}   
    if(v[y][x]) {return;}
    if(map[y][x] == '#') {return;}
    if(map[y][x] == 'G') {golds++; map[y][x] = '.';}
    v[y][x] = true;
    bool draft = senseTrap(x, y, map);
    if(!draft) { searchMap(x, y+1, map, v, golds); }
    if(!draft) { searchMap(x, y-1, map, v, golds); }
    if(!draft) { searchMap(x+1, y, map, v, golds); }
    if(!draft) { searchMap(x-1, y, map, v, golds); }

}

int main() {
    int w, h, sp_x, sp_y, golds;
    cin >> w >> h;
    vector<vector<char>> map;
    vector<vector<bool>> v;
    map.resize(h, vector<char>(w, ' '));
    v.resize(h, vector<bool>(w, false));
    char c;
    for(int y = 0; y < h; y++) {
        for(int x = 0; x < w; x++) {
            cin >> c;
            map[y][x] = c;
            if(c == 'P') {
                sp_y = y;
                sp_x = x;
            }
        }
    }
    golds = 0;
    searchMap(sp_x, sp_y, map, v, golds);
    printf("%d", golds);
    return 0;
}