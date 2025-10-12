#include <bits/stdc++.h>
using namespace std;

const int DIM = 100001;

int tmp = 0;
int h[DIM], low[DIM], id[DIM];
bool viz[DIM], in_stack[DIM];
stack<int> st;
vector<int> v[DIM];
vector<vector<int>> ctc;

// Algoritmul lui Tarjan pentru determinarea CTC
void tarjan(int nod) {
  st.push(nod);
  low[nod] = h[nod] = ++tmp;
  viz[nod] = true;
  in_stack[nod] = true;

  for (auto it : v[nod]) {
    if (viz[it] && in_stack[it]) {
      low[nod] = min(low[nod], low[it]);
    } else if (!viz[it]) {
      tarjan(it);
      low[nod] = min(low[nod], low[it]);
    }
  }

  if (h[nod] == low[nod]) {
    ctc.emplace_back();
    int x;
    do {
      x = st.top();
      st.pop();
      in_stack[x] = 0;
      id[x] = ctc.size() - 1;
      ctc.back().push_back(x);
    } while (x != nod);
  }
}

int main() {
  ifstream cin("ferate.in");
  ofstream cout("ferate.out");

  int n, m, s;
  cin >> n >> m >> s;

  // Citim graful
  for (int i = 1; i <= m; ++i) {
    int x, y;
    cin >> x >> y;
    v[x].push_back(y);
  }

  // Calculam componentele tare conexe
  for (int i = 1; i <= n; ++i)
    if (!viz[i])
      tarjan(i);

  // Vedem gradul de intrare al fiecare tare conexe
  vector<int> gr(ctc.size(), 0);
  for (auto &comp : ctc) {
    for (auto nod : comp) {
      for (auto it : v[nod]) {
        if (id[it] != id[nod])
          ++gr[id[it]];
      }
    }
  }

  // Tragem muchii la tare conexele cu grad de intrare 0
  // care nu contin nodul s.
  int ans = 0;
  for (int i = 0; i < (int)ctc.size(); ++i) {
    if (gr[i] == 0) {
      bool found = false;
      for (auto it : ctc[i]) {
        if (it == s)
          found = true;
      }
      ans += (!found);
    }
  }

  cout << ans << "\n";
  return 0;
}
