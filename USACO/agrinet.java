/*
ID: y7618231
LANG: JAVA
TASK: agrinet
 */
import java.util.*;
import java.math.*;
import java.io.*;

public class agrinet {
	static final int MAXN = 110;
	static BufferedReader in;
	static BufferedWriter out;
	static StringTokenizer tokenizer;

	int dis[][];
	int n;
	
	int prim() {
		boolean vis[] = new boolean[n];
		int mindis[] = new int[n];
		for(int i = 1; i < n; ++i) mindis[i] = Integer.MAX_VALUE;
		int res = 0;
		while(true) {
			int u = -1;
			for(int i = 0; i < n; ++i) if(!vis[i])
				if(u == -1 || mindis[i] < mindis[u]) u = i;
			if(u == -1) break;
			vis[u] = true;
			res += mindis[u];
			for(int i = 0; i < n; ++i) if(!vis[i])
				mindis[i] = Math.min(mindis[i], dis[u][i]);
		}
		return res;
	}
	
	void solve() throws Exception{
		in = new BufferedReader(new FileReader("agrinet.in")); out = new BufferedWriter(new FileWriter("agrinet.out"));
		//in = new BufferedReader(new InputStreamReader(System.in)); out = new BufferedWriter(new OutputStreamWriter(System.out));
		
		n = nextInt();
		dis = new int[n][n];
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j) dis[i][j] = nextInt();
		out.write(prim() + "\n");
		
		out.flush();
	}
	
	String nextString() throws Exception {
		while(tokenizer == null || !tokenizer.hasMoreTokens())
			tokenizer = new StringTokenizer(in.readLine());
		return tokenizer.nextToken();
	}
	
	int nextInt() throws Exception {
		return Integer.parseInt(nextString());
	}
	
	public static void main(String args[]) throws Exception{
		new agrinet().solve();
	}
}
