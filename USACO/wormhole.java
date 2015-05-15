/*
ID: y7618231
LANG: JAVA
TASK: wormhole
 */
import java.util.*;
import java.math.*;
import java.io.*;

public class wormhole {
	static final int MAXN = 33;
	static BufferedReader in;
	static BufferedWriter out;
	static StringTokenizer tokenizer;
	
	void print(int a[]) {
		try {
			for(int i = 0; i < n; ++i) out.write(a[i] + " "); out.write("\n");
		} catch(Exception e) {
			
		}
	}
	
	public class Point {
		int x, y;
	}

	Point p[];
	int n, next[], link[];
	
	void init() {
		next = new int[n];
		for(int i = 0; i < n; ++i) {
			next[i] = -1;
			for(int j = 0; j < n; ++j) {
				if(p[j].y == p[i].y && p[j].x > p[i].x) {
					if(next[i] == -1 || p[j].x < p[next[i]].x)
						next[i] = j;
				}
			}
		}
	}
	
	boolean vis[];
	
	boolean dfs(int u) {
		if(vis[u]) return true;
		vis[u] = true;
		int t = next[link[u]];
		if(t == -1) return false;
		return dfs(t);
	}
	
	boolean check() {
		//print(link);
		for(int i = 0; i < n; ++i) {
			vis = new boolean[n];
			if(dfs(i)) return true;
		}
		//print(link);
		return false;
	}
	
	int dfs_link(int u) {
		if(u == n) {
			if(check()) return 1;
			return 0;
		}
		if(link[u] == -1) {
			int res = 0;
			for(int v = u + 1; v < n; ++v) {
				if(link[v] != -1) continue;
				link[u] = v; link[v] = u;
				//print(link);
				res += dfs_link(u + 1);
				link[u] = link[v] = -1;
			}
			return res;
		} else {
			return dfs_link(u + 1);
		}
	}
	
	int work() {
		init();
		link = new int[n];
		for(int i = 0; i < n; ++i) link[i] = -1;
		return dfs_link(0);
	}
	
	void solve() throws Exception{
		in = new BufferedReader(new FileReader("wormhole.in")); out = new BufferedWriter(new FileWriter("wormhole.out"));
		//in = new BufferedReader(new InputStreamReader(System.in)); out = new BufferedWriter(new OutputStreamWriter(System.out));

		n = Integer.parseInt(in.readLine());
		p = new Point[n];
		for(int i = 0; i < n; ++i) {
			tokenizer = new StringTokenizer(in.readLine());
			p[i] = new Point();
			p[i].x = Integer.parseInt(tokenizer.nextToken());
			p[i].y = Integer.parseInt(tokenizer.nextToken());
		}
		
		out.write(work() + "\n");
		out.flush();
	}
	
	public static void main(String args[]) throws Exception{
		new wormhole().solve();
	}
}
