#include <bits/stdc++.h>
using namespace std;
#define INF 1 << 30

const int kNmax = 50005;

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n;
	int m;
	int source;
    
	vector<pair<int, int> > adj[kNmax];
	
	
   
	void read_input() {
		ifstream fin("in");
		fin >> n >> m >> source;
		for (int i = 1, x, y, w; i <= m; i++) {
			fin >> x >> y >> w;
			adj[x].push_back(make_pair(y, w));
			//adj[y].push_back(make_pair(x, w));
		}
		fin.close();
	}
	
   
	vector<int> get_result() {
		/*
		TODO: Gasiti distantele minime de la nodul source la celelalte noduri
		folosind Dijkstra pe graful orientat cu n noduri, m arce stocat in adj.
			d[node] = costul minim / lungimea minima a unui drum de la source la nodul
		node;
			d[source] = 0;
			d[node] = -1, daca nu se poate ajunge de la source la node.

		Atentie:
		O muchie este tinuta ca o pereche (nod adiacent, cost muchie):
			adj[x][i].first = nodul adiacent lui x,
			adj[x][i].second = costul.
		*/
		std::vector<bool> used(n+1, false);
        vector<int> d(n+1, INF);
        
		priority_queue<pair<int, int>, vector<pair<int, int>>,greater<pair<int, int>>> q; 
		//used[source] = 1;
		d[source] = 0;
		q.push(make_pair(d[source],source));
		while(!q.empty()){
			int x = q.top().second;
			//used[x] = 0;
			q.pop();
			
			used[x] = true;
			for(auto& road : adj[x]){
				int neighbour = road.first;
				int distance = road.second;
				if(d[neighbour] > d[x] + distance && used[neighbour] == false){
					d[neighbour] = d[x] + distance;
					q.push(make_pair(d[neighbour], neighbour));
				
				}
				
			}
			cout << "Coada: ";
			priority_queue<pair<int, int>, vector<pair<int, int>>,greater<pair<int, int>>> q1 = q;
			while(!q1.empty()){
				cout << q1.top().second <<" ";
				q1.pop();
			}
			cout <<'\n';
			cout << "Distante: ";
			for(int i = 1; i <= d.size()-1; i++){
				cout << d[i] << " ";
			}
			cout <<'\n';

		
		
		}
        for(int i = 1; i <= d.size(); i++){
        	if(d[i] == INF){
        		d[i] = -1;
        	}
        }

		
		return d;
	}

	void print_output(vector<int> result) {
		ofstream fout("out");
		for (int i = 1; i <= n; i++) {
			fout << result[i] << " ";
		}
		fout << "\n";
		fout.close();
	}
};

int main() {
	Task *task = new Task();
	task->solve();
	delete task;
	return 0;
}
