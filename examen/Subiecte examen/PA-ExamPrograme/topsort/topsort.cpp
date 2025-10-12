#include <fstream>
#include <assert.h>
#include <stack>
#include <vector>
#include <list>
#include <iterator>

inline int read() {
	int n = 0;
	char c = getchar_unlocked();

	while (!('0' <= c && c <= '9')) {
		c = getchar_unlocked();
	}

	while ('0' <= c && c <= '9') {
		n = (n << 3) + (n << 1) + c - '0';
		c = getchar_unlocked(); 
	}

	return n;
}

inline void print(int n) {
	char snum[65];
	int i = 0;

	do {
		snum[i++] = n % 10 + '0';
		n /= 10;
	} while (n);

	--i;

	while (i >= 0) {
		putchar(snum[i--]);
	}

	putchar(' ');
} 

void dfs(int src, std::vector<bool> &visited, std::vector<int> *adj, std::stack<int> &stack) {
	visited[src] = true;
	for (std::vector<int>::iterator it = adj[src].begin(); it != adj[src].end() ; ++it) {
		if (!visited[*it]) {
			visited[*it] = true;
			dfs(*it, visited, adj, stack);
		}
	}

	stack.push(src);
}

int main() {
	freopen("sortaret.in", "r", stdin);
	freopen("sortaret.out", "w", stdout);
	int n, m, src, dest;
	std::stack<int> stack;
	n = read(), m = read();
	assert(1 <= n && n <= 50000);
	assert(1 <= m && m <= 100000);
	std::vector<bool> visited(n, false);
	std::vector<int> adj[n];

	for(; m ; --m) {
		src = read(), dest = read();
		adj[src - 1].push_back(dest - 1);
	}

	for (int i = 0 ; i < n ; ++i) {
		if (!visited[i]) {
			dfs(i, visited, adj, stack);
		}
	}

	while (!stack.empty()) {
		int node = stack.top();
		stack.pop();
		print(node + 1);
	}

	return 0;
}