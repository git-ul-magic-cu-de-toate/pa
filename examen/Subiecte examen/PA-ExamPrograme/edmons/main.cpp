#include <bits/stdc++.h>

using namespace std;

const int kNmax = 1005;

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n;
	int m;
	vector<int> adj[kNmax];
  int C[kNmax][kNmax];

	void read_input() {
		ifstream fin("in");
		fin >> n >> m;

		memset(C, 0, sizeof C);
		for (int i = 1, x, y, z; i <= m; i++) {
			fin >> x >> y >> z;
			adj[x].push_back(y);
			adj[y].push_back(x);
      C[x][y] += z;
		}
		fin.close();
	}

	bool bfs(int src, int dest, vector<bool> &visited, vector<vector<int>> &flow, vector<int> &parent) {
		queue<int> q;
		q.push(src);
		visited = vector<bool>(n + 1);
		visited[src] = true;

		while (!q.empty()) {
			int node = q.front();
			q.pop();

			if (node != dest)
				for (const auto &it: adj[node])
					if (!visited[it] && flow[node][it] != C[node][it]) {
						q.push(it);
						visited[it] = true;
						parent[it] = node;
					}
		}

		return visited.back();
	}

	int get_result() {
		/*
		TODO: Calculati fluxul maxim pe graful orientat dat.
		Sursa este nodul 1.
		Destinatia este nodul n.

		In adj este stocat graful neorientat obtinut dupa ce se elimina orientarea
		arcelor, iar in C sunt stocate capacitatile arcelor.
		De exemplu, un arc (x, y) de capacitate z va fi tinut astfel:
		C[x][y] = z, adj[x] contine y, adj[y] contine x.
		*/
		int flow = 0;
		vector<bool> visited;
		vector<int> parent(n + 1);
		vector<vector<int>> flux(n + 1, vector<int> (n + 1));
		int src = 4;
		int dest = 5;
		while (bfs(src, dest, visited, flux, parent))
			for (const auto &it: adj[dest]) {
				if (flux[it][dest] == C[it][dest] || !visited[it]) {
					continue;
				}
				
				parent[dest] = it;

				int cf = INT_MAX;
				for (int node = dest; node != src; node = parent[node]) {
					cf = min(cf, (C[parent[node]][node] - flux[parent[node]][node]));
				}

				flow += cf;

				for (int node = dest; node != src; node = parent[node]) {
					
					if (cf) {
						flux[parent[node]][node] += cf;
						flux[node][parent[node]] -= cf;
					}
					
				}
			}

		return flow;
	}

	void print_output(int result) {
		ofstream fout("out");
		fout << result << '\n';
		fout.close();
	}
};

int main() {
	Task *task = new Task();
	task->solve();
	delete task;
	return 0;
}
