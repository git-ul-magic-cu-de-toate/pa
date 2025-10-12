#include <bits/stdc++.h>

#define INF 0x3f3f3f3f

typedef std::pair<int, int> int_pair;

const int BUFFER_SIZE = 1 << 17;

char buffer[BUFFER_SIZE];
int pos = BUFFER_SIZE;

inline char next() {
	if (pos == BUFFER_SIZE) {
		fread(buffer, 1, BUFFER_SIZE, stdin);
		pos = 0;
	}

	return buffer[pos++];
}

inline int read() {
	int n = 0;
	bool neg = false;
	char c = next();
	if (c == '-') {
		neg = true;
	}
	while (!('0' <= c && c <= '9')) {
		c = next();
	}

	while ('0' <= c && c <= '9') {
		n = (n << 3) + (n << 1) + c - '0';
		c = next();
	}

	if (neg) {
		return n *= -1;
	}

	return n;
}

inline void print(int n) {
	char snum[65];
	int i = 0, semn = 1;

	if (n < 0) {
		semn = -1;
	}

	do {
		snum[i++] = (semn * n) % 10 + '0';
		n /= 10;
	} while (n);

	--i;

	if (semn == -1) {
		putchar('-');
	}

	while (i >= 0) {
		putchar(snum[i--]);
	}

	putchar(' ');
}

class Graph {
 private:
	int nr_nodes;
	std::vector<std::pair<int, int>> *adj;

 public:
	explicit Graph(int nr_nodes) {
		this->nr_nodes = nr_nodes;
		adj = new std::vector<int_pair> [nr_nodes];
	}

	~Graph() {
		delete [] adj;
	}

	void addEdge(int src, int dest, int cost) {
		adj[src].push_back(std::make_pair(dest, cost));
        adj[dest].push_back(std::make_pair(src, cost));
	}

	void bfs(int src) {
        std::vector<int> visited(nr_nodes + 1, false);
		std::deque<int> Q;
		std::vector<int> distance(nr_nodes + 1, 0);
		
		Q.push_back(src);
		visited[src] = true;

        std::cout << "BFS(" << src << ") : " << Q.front() << '\n'; 
		while (!Q.empty()) {
			int index = Q.front();
            Q.pop_front();

			for (auto it = adj[index].begin() ; it != adj[index].end() ; ++it) {
				if (visited[it->first]) {
					continue;
				}

				distance[it->first] = distance[index] + 1;
				Q.push_back(it->first);
				visited[it->first] = true;
			}

            std::cout << index << " : ";
            for (auto it = Q.cbegin(); it != Q.cend() ; ++it) {
                std::cout << *it << " ";
            }

            std::cout << '\n';
		}

		std::cout << "Vectorul de distante\n";

		for (int i = 1 ; i < distance.size() - 1; ++i) {
				printf("%d ", distance[i]);
		}

		printf("\n");	
    }
};

int main() {
    freopen("date.in", "r", stdin);

	int n, m, src, dest, cost;
	n = read(), m = read();
	Graph graph(n);
	for (; m ; --m) {
		src = read(), dest = read();
		graph.addEdge(src, dest, 1);
	}

    graph.bfs(5);
	
	return 0;
}
