#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    int n, k;
    while(cin >> k >> n) {
        vector<vector<double>> alphabet;
        alphabet.resize(n+1, vector<double>(k+1, 0.0));
        
        /*
        We say that a word of length over this alphabet is tight
        if any two neighbour digits in the word do not differ by more than 1.
        */

        // n = 1
        for (int i = 0; i < k+1; i++) {
            alphabet[1][i] = 100.0/(k+1);
        }
        // n = 2 -> n
        for(int i = 2; i < n + 1; i++) {
            // första
            alphabet[i][0] = (alphabet[i-1][0] + alphabet[i-1][1]) / (k+1);

            for(int j = 1; j < k; j++){
                alphabet[i][j] = (alphabet[i-1][j-1] + alphabet[i-1][j] + alphabet[i-1][j+1]) / (k+1);
            }

            // sista
            alphabet[i][k] = (alphabet[i-1][k-1] + alphabet[i-1][k]) / (k+1);
        }
        
        double percentage = 0.0;
        for(int i = 0; i < k+1; i++) {
            percentage += alphabet[n][i];
        }
        printf("%.9f\n", percentage);

        /*
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < k; j++) {
                cout << alphabet[i][j] << endl;
            }
        }*/
        
    }
    return 0;
}