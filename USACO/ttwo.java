/*
ID: y7618231
LANG: JAVA
TASK: ttwo
 */
import java.util.*;
import java.math.*;
import java.io.*;

public class ttwo {
	static final int MAXN = 110;
	static final int seed = 131;
	static final int MOD = 9901;
	static BufferedReader in;
	static BufferedWriter out;
	static StringTokenizer tokenizer;
	
	static final int fr[] = {-1, 0, 1, 0};
	static final int fc[] = {0, 1, 0, -1};
	
	boolean vis[][];
	char mat[][];
	int n = 10;
	
	boolean check(int r, int c) {
		return 0 <= r && r < n && 0 <= c && c < n && mat[r][c] != '*';
	}
	
	public class Node {
		int r, c, f;
		Node() {}
		Node(int _r, int _c, int _f) {
			r = _r; c = _c; f = _f;
		}
		int encode() {
			return f * n * n + r * n + c;
		}
		void go() {
			int nr = r + fr[f], nc = c + fc[f];
			if(!check(nr, nc)) f = (f + 1) % 4;
			else {
				r = nr;
				c = nc;
			}
		}
		boolean equal(Node rhs) {
			return r == rhs.r && c == rhs.c;
		}
	}
	
	int work() throws Exception{
		Node a = null, b = null;
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < n; ++j) {
				if(mat[i][j] == 'F') a = new Node(i, j, 0);
				if(mat[i][j] == 'C') b = new Node(i, j, 0);
			}
		}
		int v = 4 * n * n + n * n + n + 1;
		vis = new boolean[v][v];
		int cnt = 0;
		while(true) {
			if(a.equal(b)) break;
			cnt++;
			
			int tx = a.encode(), ty = b.encode();
			//out.write(tx + " " + ty + "\n");
			if(vis[tx][ty]) return 0;
			vis[tx][ty] = true;
			
			a.go(); b.go();
		}
		return cnt;
	}
	
	void solve() throws Exception{
		in = new BufferedReader(new FileReader("ttwo.in")); out = new BufferedWriter(new FileWriter("ttwo.out"));
		//in = new BufferedReader(new InputStreamReader(System.in)); out = new BufferedWriter(new OutputStreamWriter(System.out));
		
		mat = new char[n][n];
		for(int i = 0; i < n; ++i)
			mat[i] = nextString().toCharArray();
		
		out.write(work() + "\n");
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
		new ttwo().solve();
	}
}
