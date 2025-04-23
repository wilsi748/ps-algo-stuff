/*
    Author: William Sid (wilsi748)

    Problem solved: Suffix Array Re-construction
*/

#include <bits/stdc++.h>

using namespace std;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int t, l, s;
    cin >> t;
    while(t--) {
        cin >> l >> s;
        string res(l, ' ');
        bool impossible = false;
        for (int i = 0; i < s; i++) {
            int pos;
            string suffix;
            cin >> pos >> suffix;
            
            bool asterisk = false;
        
            pos--;
            for (int i = pos; i < l; i++) {
                if (suffix[i-pos] == '*') {
                    asterisk = true;
                    break;
                } else if (res[i] == ' ') {
                    res[i] = suffix[i-pos];
                } else if (res[i] != suffix[i-pos]) {
                    impossible = true;
                }
            }
            if(asterisk){
                for(int i = l-1, j = suffix.size() - 1; j >= 0; i--, j--) {
                    if (suffix[j] == '*') break;
                    else if (res[i] != ' ' && res[i] != suffix[j]) impossible = true;
                    else res[i] = suffix[j];
                }
            }
        }
        
        for(int i = 0; i < l; i++) {
            if(res[i] == ' ') impossible = true;
        }

        if (impossible) cout << "IMPOSSIBLE" << endl;
        else cout << res << endl;

    }

    return 0;
}