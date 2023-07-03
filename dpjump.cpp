#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAX_N = 1005;
const int MAX_W = 1005;

int n;
double W;
double w[MAX_N], v[MAX_N];
double dp[MAX_W];
int prev_idx[MAX_W];
bool best_choice[MAX_N];

void knapsack() {
    memset(dp, 0, sizeof(dp));
    memset(prev_idx, -1, sizeof(prev_idx));
    for (int i = 1; i <= n; i++) {
        for (int j = W; j >= w[i]; j--) {
            double new_v = dp[j-w[i]] + v[i];
            if (new_v > dp[j]) {
                dp[j] = new_v;
                prev_idx[j] = i;
            }
        }
    }
}

void backtrack() {
    int i = W;
    while (i >= 0 && prev_idx[i] != -1) {
        if (dp[i] != dp[i-w[prev_idx[i]]] + v[prev_idx[i]]) {
            best_choice[prev_idx[i]] = true;
            i = i - w[prev_idx[i]];
        } else {
            i--;
        }
    }
    if (i >= 0) {
        best_choice[prev_idx[i]] = true;
    }
}

int main() {
    cin >> n >> W;
    memset(best_choice, false, sizeof(best_choice));
    for (int i = 1; i <= n; i++) {
        cin >> w[i] >> v[i];
    }
    knapsack();
    backtrack();
    printf("%.1lf\n", dp[(int)W]);
    for (int i = 1; i <= n; i++) {
        if (best_choice[i]) {
            cout << i << " ";
        }
    }
    return 0;
}
