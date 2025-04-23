#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    int l, d, n_birds;
    cin >> l >> d >> n_birds;
    int bird;
    vector<int> positions_of_birds;
    for(int i = 0; i < n_birds; i++) {
        cin >> bird;
        positions_of_birds.push_back(bird);
    }
    sort(positions_of_birds.begin(), positions_of_birds.end()); // smallest bird first.
    int added = 0;
    int start = 6; // 6 cm of the start pole
    for(int i = 0; i < n_birds; i++) {
        // while there is space, add birds.
        while(positions_of_birds[i] - start >= d) {
            start = start + d;
            added++;
        }
        start = positions_of_birds[i] + d;
    }
    // Go from last bird to 6 cm of end pole
    while(start <= l - 6) {
        start = start + d;
        added++;
    }
    printf("%d\n", added);
    return 0;
}