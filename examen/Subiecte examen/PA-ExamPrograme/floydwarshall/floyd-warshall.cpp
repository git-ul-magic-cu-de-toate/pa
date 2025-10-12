#include <bits/stdc++.h>
#define INF 0x3f3f3f3f

int main() {
	std::ifstream fin ("date.in");
	std::ofstream fout ("date.out");
	int n;

	fin >> n;

	int a[n + 1][n + 1];

	for (int i = 1 ; i <= n ; ++i) {
		for (int j = 1 ; j <= n ; ++j) {
			fin >> a[i][j];
			if (a[i][j] == 0 && i != j) {
				a[i][j] = INF;
			}
		}
	}


	for (int i = 1 ; i<= n; ++i, fout << '\n') {
		for (int j = 1 ; j <= n ; ++j) {
			if (a[i][j] == INF) {
				fout << "INF ";
			} else {
				fout << a[i][j] << " ";
			}
		}
	}
	fout << '\n';

	for (int k = 1 ; k <= 3 ; ++k) {
		for (int i = 1 ; i <= n ; ++i) {
			for (int j = 1 ; j <= n ; ++j) {
				if (a[i][j] > a[i][k] + a[k][j]) {
					fout << "S-a modificat la iteratia: " << k << '\n';
					a[i][j] = a[i][k] + a[k][j];
					fout << "(" << i << ", " << j << ") ->" << a[i][j];
					fout << '\n';
				}
			}
		}
	}

	for (int i = 1 ; i <= n ; ++i, fout << '\n') {
		for (int j = 1 ; j <= n ; ++j) {
			if (i == j) {
				fout << "0 ";
			} else if (a[i][j] == INF) {
				fout << "INF ";
			} else {
				fout << a[i][j] << " ";
			}
		}
	}

	return 0;
}