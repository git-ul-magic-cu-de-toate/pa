import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.*;

public class Main {
	static class Task {
		public static final String INPUT_FILE = "in";
		public static final String OUTPUT_FILE = "out";
		public static final int NMAX = 100005; // 10^5
		public static int time = 0;
		int n;
		int m;

		@SuppressWarnings("unchecked")
		ArrayList<Integer> adj[] = new ArrayList[NMAX];

		private void readInput() {
			try {
				Scanner sc = new Scanner(new BufferedReader(new FileReader(
								INPUT_FILE)));
				n = sc.nextInt();
				m = sc.nextInt();

				for (int i = 1; i <= n; i++)
					adj[i] = new ArrayList<>();
				for (int i = 1; i <= m; i++) {
					int x, y;
					x = sc.nextInt();
					y = sc.nextInt();
					adj[x].add(y);
					adj[y].add(x);
				}
				sc.close();
			} catch (IOException e) {
				throw new RuntimeException(e);
			}
		}

		private void writeOutput(ArrayList<Integer> result) {
			try {
				PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter(
								OUTPUT_FILE)));
				for (int node : result) {
					pw.printf("%d ", node);
				}
				pw.printf("\n");
				pw.close();
			} catch (IOException e) {
				throw new RuntimeException(e);
			}
		}

		private void dfs(ArrayList<Integer> sol, ArrayList<Integer> []adj, int[] p, int src, int[] disc,
							int []low) {
			disc[src] = low[src] = ++time;
			ArrayList<Integer> children = new ArrayList<>();
			for (Integer it : adj[src]) {
				if (p[src] != it) {
					if (disc[it] == -1) {
						p[it] = src;
						children.add(it);
						dfs(sol, adj, p, it, disc, low);
						low[src] = Math.min(low[src], low[it]);
					} else {
						low[src] = Math.min(low[src], disc[it]);
					}
				}
				
			}


			if (disc[src] == 1 && low[src] == 1) {
				if (children.size() >= 2) {
					sol.add(src);
					System.out.println(src + ": " + disc[src] + " " + low[src]);
				}
			} else {
				for (Integer it : children) {
					if (low[it] >= disc[src]) {
						System.out.println(src + ": " +  disc[src] + " " + low[src]);
						sol.add(src);
						break;
					}
				}
			}
		}

		private ArrayList<Integer> getResult() {
			// TODO: Gasiti nodurile critice ale grafului neorientat stocat cu liste
			// de adiacenta in adj.
			int [] disc = new int[n + 1];
			Arrays.fill(disc, -1);
			int [] low = new int[n + 1];
			ArrayList<Integer> sol = new ArrayList<>();
			int [] p = new int[n + 1];
			Arrays.fill(p, -1);
 			// for (int i = 1 ; i <= n ; ++i) {
 			// 	if (disc[i] == -1) {
 			// 		dfs(sol, adj, i, disc, low);
			// 	}
			// }
			dfs(sol, adj, p, adj[1].get(0), disc, low);
			return sol;
		}

		public void solve() {
			readInput();
			writeOutput(getResult());
		}
	}

	public static void main(String[] args) {
		new Task().solve();
	}
}
