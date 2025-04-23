/*
    Author: William Sid (wilsi748)

    Problem solved: Linear Equation Solver
*/
#include <bits/stdc++.h>

using namespace std;

template<typename T>
class LinearEquationSolver{
public:
    LinearEquationSolver(vector<vector<T>>& _matrix, vector<T>& _b) : matrix(_matrix), b(_b) {
        n = matrix.size();
    }
        
    vector<T> gauss() {
        for (int i = 0; i < n; i++) {
            matrix[i][n] = b[i];
        }
        for (int i = 0; i < n; i++) {
            int pivot = find_pivot(i);
            if(pivot != i) {
                swap(matrix[i], matrix[pivot]);
            }
            if(matrix[i][i] == 0) {
                continue;
            }
            for(int j = i + 1; j < n; j++) {
                T factor = matrix[j][i] / matrix[i][i];
                for(int k = i + 1; k <= n; k++) {
                    matrix[j][k] -= factor * matrix[i][k];
                }
                matrix[j][i] = 0;
            }
        }

        vector<T> x(n);
        for (int i = n - 1; i >= 0; i--) {
            if(matrix[i][i] == 0) {
                continue;
            }
            T sum = 0;
            for (int j = i + 1; j < n; j++) {
                sum += matrix[i][j] * x[j];
            }
            x[i] = (matrix[i][n] - sum) / matrix[i][i];
        }
        return x;
    }

private:
    int n;
    vector<vector<T>>& matrix;
    vector<T>& b;

    int find_pivot(int i) {
        int pivot = i;
        for (int j = i + 1; j < n; j++) {
            if (matrix[j][i] > matrix[pivot][i]) {
                pivot = j;
            }
        }
        return pivot;
    }
};



int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n;
    while (cin >> n && n != 0) {
        vector<vector<double>> A(n, vector<double>(n+1));
        vector<double> b(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> A[i][j];
            }
        }
        for (int i = 0; i < n; i++) {
            cin >> b[i];
        }
        LinearEquationSolver<double> les(A, b);
        vector<double> x = les.gauss();
        
        bool inconsistent = false;
        bool multiple = false;
        for(int i= 0; i < n; i++){
            int j = 0;
            while (A[i][j] == 0 && j <= n)
                j++;
            if ( j == n && A[i][j] != 0 ) {
                inconsistent = true;
            }
            if (j == n + 1) multiple = true;
        }
        if(inconsistent) {
            cout << "inconsistent" << endl;
        }
        else if(multiple) {
            cout << "multiple" << endl;
        }
        else {
            for(int i = 0; i < n; i++) {
                cout << x[i] << " ";
            }
            cout << endl;
        }
    }
    return 0;
}



