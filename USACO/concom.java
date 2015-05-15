/*
ID: y7618231
LANG: JAVA
TASK: concom
 */
import java.util.*;
import java.math.*;
import java.io.*;

public class concom {
	static final int MAXN = 110;
	static final int seed = 131;
	static final int MOD = 9901;
	static BufferedReader in;
	static BufferedWriter out;
	static StringTokenizer tokenizer;

	boolean vis[][];
	int src[][], mat[][];
	int n, m;
	
	void get(int u) {
		while(true) {
			boolean flag = false;
			for(int v = 1; v <= n; ++v) {
				if(vis[u][v] || mat[u][v] <= 50) continue;
				flag = true;
				vis[u][v] = true;
				for(int i = 1; i <= n; ++i)
					mat[u][i] += src[v][i];
			}
			if(!flag) break;
		}
	}
	
	void work() throws Exception{
		for(int i = 1; i <= n; ++i) {
			vis[i][i] = true;
			get(i);
			for(int j = 1; j <= n; ++j) if(i != j) {
				if(mat[i][j] <= 50) continue;
				out.write(i + " " + j + "\n");
			}
		}
	}
	
	void solve() throws Exception{
		in = new BufferedReader(new FileReader("concom.in")); out = new BufferedWriter(new FileWriter("concom.out"));
		//in = new BufferedReader(new InputStreamReader(System.in)); out = new BufferedWriter(new OutputStreamWriter(System.out));

		m = nextInt();
		mat = new int[MAXN][MAXN];
		src = new int[MAXN][MAXN];
		vis = new boolean[MAXN][MAXN];
		
		for(int i = 0; i < m; ++i) {
			int a = nextInt(), b = nextInt(), c = nextInt();
			mat[a][b] = src[a][b] = c;
			n = Math.max(n, Math.max(a, b));
		}

		work();
		out.flush();
	}
	
	String nextString() throws Exception{
		while(tokenizer == null || !tokenizer.hasMoreTokens())
			tokenizer = new StringTokenizer(in.readLine());
		return tokenizer.nextToken();
	}
	
	int nextInt() throws Exception {
		return Integer.parseInt(nextString());
	}
	
	public static void main(String args[]) throws Exception{
		new concom().solve();
	}
}
