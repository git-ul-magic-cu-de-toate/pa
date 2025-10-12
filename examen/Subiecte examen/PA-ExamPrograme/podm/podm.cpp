#include <bits/stdc++.h>

const unsigned long long INF = (1e17);
long long dp[505][505], d[505];

long long min(long long a, long long b) {
    return a < b ? a : b;
}

int main() {
    freopen("podm.in", "r", stdin);
    freopen("podm.out", "w", stdout);

    int n;
    scanf("%d", &n);

    for (int i = 0 ; i <= n ; ++i) {
        scanf("%lld", &d[i]);
    }

    for (int l = 2 ; l <= n ; ++l) {
        for (int i = 1 ; i <= n - l + 1; ++i) {
            int j = i + l - 1;
            dp[i][j] = INF;

            for (int k = i ; k < j; ++k) {
                dp[i][j] = min(dp[i][j],  dp[i][k] + dp[k + 1][j] + (d[i - 1] * d[k] * d[j]));
            }
        }
    }

   	printf("%lld\n", dp[1][n]);
    return 0;
}
