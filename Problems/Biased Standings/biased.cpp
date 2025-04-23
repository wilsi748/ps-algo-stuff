/*
    Author: William Sid (wilsi748)

    Problem solved: 
*/
#include <bits/stdc++.h>

using namespace std;

int inf = 1e9;

struct team {
    int current_place;
    string name;
    int wanted_place;
    int dist;
    team(int current_place, string name, int wanted_place, int dist) : current_place(current_place), name(name), wanted_place(wanted_place), dist(dist) {};
    bool operator < (const team& t) const { return ( wanted_place < t.wanted_place); }
};

/*
For each team, compute the distance between their preferred place and their place in the ranklist.
The sum of these distances will be called the badness of this ranklist.

*/


int solve(vector<team> rank_list) {
    int bad = 0;
    for(team& t : rank_list) {
        cout << t.name << " " << t.current_place << " " << t.wanted_place << " " << t.dist << endl;
        
    }
    vector<int> done;
    sort(rank_list.begin(), rank_list.end());
    queue<team> q;
    //q.push(rank_list[0]);
    while(done.size() < rank_list.size()) {
        //team& t = q.front();
        for(team& t : rank_list) {
            if(t.current_place == t.wanted_place) {
                bad += t.dist;
                cout << "adding" << endl;
                done.push_back(t.current_place);
                continue;
            } else if(t.current_place > t.wanted_place) {
                if(find(done.begin(), done.end(), t.wanted_place) != done.end()) {
                    t.wanted_place++;
                    t.dist++;
                } else {
                    t.dist = abs(t.current_place - t.wanted_place);
                    t.current_place = t.wanted_place;
                }
            }else if(t.current_place < t.wanted_place) {
                if(find(done.begin(), done.end(), t.wanted_place) != done.end()) {
                    t.wanted_place--;
                    t.dist--;
                } else {
                    t.dist = abs(t.current_place - t.wanted_place);
                    t.current_place = t.wanted_place;
                }   
            }
        }
    }
        
    

    for(team& t : rank_list) {
        cout << t.name << " " << t.current_place << " " << t.wanted_place << " " << t.dist << endl;
    }


    return bad;
}


int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);


    int tests, badness;
    cin >> tests;
    for(int i = 0; i < tests; i++) {
        int n_teams;
        cin >> n_teams;
        vector<team> rank_list;
        for(int j = 0; j < n_teams; j++) {
            string team_name;
            cin >> team_name;
            int place;
            cin >> place;
            rank_list.push_back(team(j+1, team_name, place, 0));
        }
        badness = solve(rank_list);

        cout << badness << endl;
    }

    return 0;
}