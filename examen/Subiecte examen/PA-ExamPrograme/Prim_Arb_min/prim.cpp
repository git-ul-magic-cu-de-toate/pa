#include <bits/stdc++.h>
using namespace std;
#define INF 1 << 30

const int kNmax = 2e5 + 10;

class Task {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int n;
    int m;
    vector<pair<int, int> > adj[kNmax];

    void read_input() {
        ifstream fin("in");
        fin >> n >> m;
        for (int i = 1, x, y, w; i <= m; i++) {
            fin >> x >> y >> w;
            adj[x].push_back({w, y});
            adj[y].push_back({w, x});
        }
        fin.close();
    }

    int get_result() {
        /*
        TODO: Calculati costul minim al unui arbore de acoperire
        folosind algoritmul lui Prim.
        */
        std::vector<int> used(n+1, 0);;
        int cost = 0;
        vector<int> key(n+1, INF);
        vector<pair<int, int>> arb;
        priority_queue<pair<int, int>, vector<pair<int, int>>,greater<pair<int, int>>> q;
        q.push(make_pair(0, 1));
        int ant = 1;
        key[1] = 0;
        vector<int> parents(n+1, -1);
        while(!q.empty()){
            pair<int, int> edge = q.top();
            
            q.pop();
            if(!used[edge.second]){
                cost += edge.first;
                //arb.push_back(make_pair(parents[edge.second], edge.second));
                cout << "Cost curent: "<< cost << '\n';
                cout <<"Nod curent: "<< edge.second <<'\n';
                used[edge.second] = 1;
                for(auto& edge_yeah : adj[edge.second]){
                    
                    if(!used[edge_yeah.second] && key[edge_yeah.second] > edge_yeah.first){
                        key[edge_yeah.second] = edge_yeah.first;
                        parents[edge_yeah.second] = edge.second;
                        q.push(edge_yeah);
                    }
                }
            }
            cout << "Coada: ";
            priority_queue<pair<int, int>, vector<pair<int, int>>,greater<pair<int, int>>> q1 = q;
            while(!q1.empty()){
               pair<int, int> edge = q1.top();
               cout <<"{"<< edge.first <<", " << edge.second <<"}";
               q1.pop(); 
            }
            cout << '\n';

        }
        for(int i = 2; i <= n; i++){
            cout << parents[i] << " " << i <<'\n';
        }

        return cost;
    }

    void print_output(int result) {
        ofstream fout("out");
        fout << result << "\n";
        fout.close();
    }
};

// Please always keep this simple main function!
int main() {
    // Allocate a Task object on heap in order to be able to
    // declare huge static-allocated data structures inside the class.
    Task *task = new Task();
    task->solve();
    delete task;
    return 0;
}
