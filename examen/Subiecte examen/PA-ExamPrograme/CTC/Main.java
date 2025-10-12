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

		int n;
		int m;
		static int time = 0;
		@SuppressWarnings("unchecked")
		ArrayList<Integer> adj[] = new ArrayList[NMAX];
		@SuppressWarnings("unchecked")
		ArrayList<Integer> adjt[] = new ArrayList[NMAX];

		private void readInput() {
			try {
				Scanner sc = new Scanner(new BufferedReader(new FileReader(
								INPUT_FILE)));
				n = sc.nextInt();
				m = sc.nextInt();
				
				for (int i = 1; i <= n; i++) {
					adj[i] = new ArrayList<>();
					adjt[i] = new ArrayList<>();
				}
				for (int i = 1; i <= m; i++) {
					int x, y;
					x = sc.nextInt();
					y = sc.nextInt();
					adj[x].add(y);
					// adjt[y + 1].add(x + 1);
				}
				sc.close();
			} catch (IOException e) {
				throw new RuntimeException(e);
			}
		}

		private void writeOutput(ArrayList<ArrayList<Integer>> result) {
			try {
				PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter(
								OUTPUT_FILE)));
				pw.printf("%d\n", result.size());
				for (ArrayList<Integer> ctc : result) {
					for (int nod : ctc) {
						pw.printf("%d ", nod);
					}
					pw.printf("\n");
				}
				pw.close();
			} catch (IOException e) {
				throw new RuntimeException(e);
			}
		}

		private void tarjan(ArrayList<ArrayList<Integer>> scc, ArrayList<Integer> []adj, int src, int[] disc,
			int []low, boolean []isOnStack, Stack<Integer> st) {
				disc[src] = low[src] = ++time;
				st.push(src);
				isOnStack[src] = true;

				for (Integer it : adj[src]) {
					if (disc[it] == -1) {
						tarjan(scc, adj, it, disc, low, isOnStack, st);
						low[src] = Math.min(low[src], low[it]);
						
					} else if (isOnStack[it] == true) {
						low[src] = Math.min(low[src], disc[it]);
					}
				}


				if (disc[src] == low[src]) {
					ArrayList<Integer> comp = new ArrayList<>();
					int node;
					do {
						comp.add(node = st.peek());
						st.pop();
						isOnStack[node] = false;
					} while (node != src);

					scc.add(comp);
				}
		}

		private ArrayList<ArrayList<Integer>> getResult() {
			// TODO: Gasiti componentele tare conexe ale grafului orientat cu
			// n noduri, stocat in adj. Rezultatul se va returna sub forma
			// unui ArrayList, ale carui elemente sunt componentele tare conexe
			// detectate. Nodurile si componentele tare conexe pot fi puse in orice
			// ordine in arraylist.
			//
			// Atentie: graful transpus este stocat in adjt.
			ArrayList<ArrayList<Integer>> sol = new ArrayList<>();
			int [] disc = new int[n + 1];
			int [] low = new int[n + 1];
			boolean []isOnStack = new boolean[n + 1];
			Arrays.fill(isOnStack, false);
			Arrays.fill(disc, -1);

			Stack<Integer> stack = new Stack<>();

			for (int i = 1 ; i <= n ; ++i) {
				if (disc[i] == -1) {
					tarjan(sol, adj, i, disc, low, isOnStack, stack);
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
