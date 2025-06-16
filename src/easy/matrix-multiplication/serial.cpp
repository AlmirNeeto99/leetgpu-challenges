#include <iostream>
#include <vector>

using namespace std;

void matmul(vector<vector<float>> a, vector<vector<float>> b,
            vector<vector<float>> c) {}

void fill(vector<vector<float>> &matrix, int M, int N) {
    for (int i = 0; i < M; i++) {
        matrix[i] = vector<float>(N);
        for (int j = 0; j < N; j++) {
            matrix[i][j] = (float)rand() / RAND_MAX;
        }
    }
}

int main() {
    int M1 = 4, N1 = 4;
    int M2 = 4, N2 = 4;

    int M3 = M1, N3 = N2;

    vector<vector<float>> A(M1);
    vector<vector<float>> B(M2);
    vector<vector<float>> C(M3);
    fill(A, M1, N1);
    fill(B, M2, N2);
    fill(C, M3, N3);  // Fill C so its inner vectors are allocated

    return 0;
}