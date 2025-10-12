#include <bits/stdc++.h>
using namespace std;

const int DIM = 1e5 + 1;

vector<int> v[DIM];
int tmp[DIM], wh[DIM], last[DIM];

void dfs(int nod = 1) {
  static int time = 0;
  tmp[nod] = ++time;
  wh[time] = nod;
  for (auto fiu : v[nod]) {
    dfs(fiu);
  }
  last[nod] = time;
}


int main() {
  ifstream fin("magazin.in");
  ofstream fout("magazin.out");

  int n, q;
  fin >> n >> q;
  // Citim arborele
  for (int i = 2; i <= n; ++i) {
    int tt;
    fin >> tt;
    v[tt].push_back(i);
  }

  // Calculam timpii din parcurgerea dfs
  dfs();

  for (int i = 1; i <= q; ++i) {
    int nod, k;
    fin >> nod >> k;
    if (tmp[nod] + k > last[nod])
      fout << -1 << '\n';
    else
      fout << wh[tmp[nod] + k] << '\n';
  }

  return 0;
}
