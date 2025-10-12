#include <bits/stdc++.h>
using namespace std;

const int DIM = 10001;
const int64_t INF = 1e18;

vector<pair<int, int>> v[DIM];
vector<pair<int, int>> per[DIM];

struct state {
  int nod, tmp;
  int64_t cost;
  bool operator < (const state &aux) const {
    if (cost != aux.cost)
      return cost < aux.cost;
    if (tmp != aux.tmp)
      return tmp < aux.tmp;
    return nod < aux.nod;
  }
};

int main() {
  ifstream cin("teleportare.in");
  ofstream cout("teleportare.out");

  int n, m, k;
  cin >> n >> m >> k;

  // Citim graful
  for (int i = 1; i <= m; ++i) {
    int x, y, t;
    cin >> x >> y >> t;
    v[x].push_back({y, t});
    v[y].push_back({x, t});
  }

  vector<int> frec;
  for (int i = 1; i <= k; ++i) {
    int x, y, t;
    cin >> x >> y >> t;
    per[x].push_back({y, t});
    per[y].push_back({x, t});
    frec.push_back(t);
  }

  sort(frec.begin(), frec.end());
  frec.erase(unique(frec.begin(), frec.end()), frec.end());

  // Calculam perioada pentru care calculam costurile
  int MOD = 1;
  for (auto it : frec)
    MOD = MOD * it / __gcd(MOD, it);

  set<state> q;

  vector<vector<int64_t>> sol(n + 1, vector<int64_t>(MOD, INF));

  // Folosim algoritmul lui Dijkstra
  q.insert({1, 0, 0});
  sol[1][0] = 0;
  while (!q.empty()) {
    int nod = q.begin()->nod, tmp = q.begin()->tmp;
    int64_t cost = q.begin()->cost;
    q.erase(q.begin());

    if (nod == n) {
      // Ne oprim in momentul in care am ajuns la nodul n
      cout << cost << '\n';
      return 0;
    }

    for (auto it : per[nod]) {
      int rest = tmp + 1;
      if (rest >= MOD)
        rest -= MOD;
      if (cost % it.second == 0) {
        if (sol[it.first][rest] > cost + 1) {
          if (sol[it.first][rest] != INF)
            q.erase({it.first, rest, sol[it.first][rest]});
          sol[it.first][rest] = cost + 1;
          q.insert({it.first, (int)(rest), cost + 1});
        }
      }
    }

    for (auto it : v[nod]) {
      int rest = (tmp + it.second) % MOD;
      if (cost + it.second < sol[it.first][rest]) {
        if (sol[it.first][rest] != INF)
          q.erase({it.first, rest, sol[it.first][rest]});
        sol[it.first][rest] = cost + it.second;
        q.insert({it.first, rest, cost + it.second});
      }
    }
  }

  return 0;
}
