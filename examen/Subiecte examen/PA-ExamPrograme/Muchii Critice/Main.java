import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Arrays;

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

		class Edge {
			int x;
			int y;
			Edge(int x, int y) {
				this.x = x;
				this.y = y;
			}
		}

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

		private void writeOutput(ArrayList<Edge> result) {
			try {
				PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter(
								OUTPUT_FILE)));
				pw.printf("%d\n", result.size());
				for (Edge e : result) {
					pw.printf("%d %d\n", e.x, e.y);
				}
				pw.close();
			} catch (IOException e) {
				throw new RuntimeException(e);
			}
		}

		private void dfs(ArrayList<Edge> sol, ArrayList<Integer> []adj, int src, int[] disc,
							int []low, int crtDad) {
			disc[src] = low[src] = ++time;
			for (Integer it : adj[src]) {
				if (disc[it] == -1) {
					dfs(sol, adj, it, disc, low, src);
					low[src] = Math.min(low[src], low[it]);
					if (low[it] > disc[src]) {
						sol.add(new Edge(src, it));
					}
				} else if (it != crtDad) {
					low[src] = Math.min(low[src], disc[it]);
				}
			}
		}

		private ArrayList<Edge> getResult() {
			int [] disc = new int[n + 1];
			Arrays.fill(disc, -1);
			int [] low = new int[n + 1];
 			ArrayList<Edge> sol = new ArrayList<>();
 			for (int i = 1 ; i <= n ; ++i) {
 				if (disc[i] == -1) {
 					dfs(sol, adj, i, disc, low, 0);
				}
			}
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
