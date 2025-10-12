#include <bits/stdc++.h>
using namespace std;

int solve(int val, vector<int> a, vector<int> gr, vector<vector<int>> &v) {
  int n = a.size() - 1;
  queue <int> q[2];
  vector<int> dst(n + 1, 0);
  // Adaugam in coada toate taskurile pe care le putem rezolva din start
  for (int i = 1; i <= n; ++i) {
    if (a[i] == val && gr[i] == 0)
      q[0].push(i);
    else if (gr[i] == 0)
      q[1].push(i);
  }

  int tmp = 0, rem = 0, wh = 0;
  // Sortare topologica modificata
  while (!q[0].empty() || !q[1].empty()) {
    if (q[wh].empty())
      wh = 1 - wh;

    int nod = q[wh].front();
    q[wh].pop();

    tmp = max(tmp, dst[nod]);
    for (auto it : v[nod]) {
      --gr[it];
      dst[it] = max(dst[it], dst[nod] + (a[it] != a[nod]));
      if (gr[it] == 0) {
        if (a[it] != a[nod])
          q[1 - wh].push(it);
        else
          q[wh].push(it);
      }
    }
  }

  return tmp;
}

int main() {
  ifstream cin("supercomputer.in");
  ofstream cout("supercomputer.out");

  int n, m;
  cin >> n >> m;
  vector<int> a(n + 1);
  for (int i = 1; i <= n; ++i)
    cin >> a[i];

  vector<int> gr(n + 1, 0);
  vector<vector<int>> v(n + 1);

  // Citim graful
  for (int i = 1; i <= m; ++i) {
    int x, y;
    cin >> x >> y;
    v[x].push_back(y);
    ++gr[y];
  }

  // Fie incepem cu un task de tip 1 fie cu un task de tip 2
  cout << min(solve(1, a, gr, v), solve(2, a, gr, v)) << '\n';
  return 0;
}
