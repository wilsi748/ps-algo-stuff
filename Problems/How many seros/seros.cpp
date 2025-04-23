/*
    Author: William Sid (wilsi748)

    Problem solved: How many 0's?
*/
#include <bits/stdc++.h>

using namespace std;

unsigned int countto(unsigned int n) {
    // left side of n, middle digit of n, right side of n
    unsigned int seros = 0, middle, left, right, i = 1;
    while(true) {
        middle = n / i % 10;
        right = n % i;
        left = n / i / 10;
        
        if (left == 0) {
            return seros;
        }
        if (middle == 0) {
            seros += (left - 1) * i + right + 1;
        } else {
            seros += left * i;
        }
        i *= 10;
    }
}

unsigned int countseros(unsigned int n) {
    unsigned int seros = 0;
    if(n == 0) return 1;
    while(n > 0) {
        if(n%10 == 0) {
            seros++;
        }
        n /= 10;
    }
    return seros;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    while(true) {
        unsigned int m, n;
        cin >> m >> n;
        if(m == -1 && n == -1) break;
        unsigned int seros = countseros(m) + countto(n) - countto(m);
        cout << seros << endl;
    }
    return 0;
}