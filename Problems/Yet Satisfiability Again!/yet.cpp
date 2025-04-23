/*
    Author: William Sid (wilsi748)

    Problem solved: 
*/
#include <bits/stdc++.h>

using namespace std;


void printClauses(const vector<bitset<20>>& clauses) {
    for (int i = 0; i < clauses.size(); i++) {
        cout << "Clause " << i << ": ";
        for (int j = 0; j < 20; j++) {
            if (clauses[i][j]) {
                cout << j+1 << " ";
            } else {
                cout << "~" << j+1 << " ";
            }
        }
        cout << endl;
    }
}


bitset<20> getbits(int bits, int n) {
    bitset<20> res;
    for(int i = 0; i < bits; i++) {
        res[i] = (n % 2);
        n /= 2;
    }
    return res;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int t;
    cin >> t;
    while(t--) {
        int n, m;
        cin >> n >> m;
        cin.ignore();
        vector<bitset<20>> clauses(m);
        bool satisfiable = false;
        // read the clauses and set the bitsets accordingly
        for (int i = 0; i < m; i++) {
            string s;
            getline(cin, s);
            bitset<20> var;
            
            int j = 0;
            cout << "current s " << s << endl; 
            while(j < s.length()) {
                if(s[j] == ' ') {
                    j++;
                    continue;
                }
                if(s[j] == 'v') {
                    j++;
                    continue;
                }
                if(s[j] == '~') {
                    j++;
                    var.set(stoi(s.substr(j+1, s.find_first_of("v ", j+1) - j-1)) - 1, 0);
                } else {
                    var.set(stoi(s.substr(j+1, s.find_first_of("v ", j+1) - j-1)) - 1, 1);
                }
                j = s.find_first_of("v ", j);
                if(j == -1) {
                    break;
                }
                j++;
            }
            clauses[i] = var;
        }

        for (int i = 0; i < (1 << n); i++) { 
            bool satisfies_all_clauses = true;
            for(int j = 0; j < m; j++) { 
                bool satisfies_clause = false;
                for(int k = 0; k < n;  k++) { 
                    if (clauses[j][k] == 1 && ((i >> k) & 1)) {
                        satisfies_clause = true;
                        break;
                    } else if (clauses[j][k] == 0 && !((i >> k) & 1)) {
                        satisfies_clause = true;
                        break;
                    }
                }
                if(!satisfies_clause) { 
                    satisfies_all_clauses = false;
                    break;
                }
            }
            if(satisfies_all_clauses) { 
                satisfiable = true;
                break;
            }
        }

        if (satisfiable) {
            cout << "satisfiable" << endl;
        } else {
            cout << "unsatisfiable" << endl;
        }
    }

    return 0;
}