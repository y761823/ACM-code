/*
ID: y7618231
LANG: JAVA
TASK: comehome
 */
import java.util.*;
import java.math.*;
import java.io.*;

public class comehome {
	static final int MAXN = 110;
	static final int seed = 131;
	static final int MOD = 9901;
	static final int INF = 0x3f3f3f3f;
	static BufferedReader in;
	static BufferedWriter out;
	static StringTokenizer tokenizer;

	int dis[][];
	int n = 52, m;
	
	int encode(char c) {
		if('a' <= c && c <= 'z') return c - 'a';
		return c - 'A' + 26;
	}
	
	void floyd() {
		for(int k = 0; k < n; ++k)
			for(int i = 0; i < n; ++i)
				for(int j = 0; j < n; ++j)
					dis[i][j] = Math.min(dis[i][j], dis[i][k] + dis[k][j]);
	}
	
	void solve() throws Exception{
		in = new BufferedReader(new FileReader("comehome.in")); out = new BufferedWriter(new FileWriter("comehome.out"));
		//in = new BufferedReader(new InputStreamReader(System.in)); out = new BufferedWriter(new OutputStreamWriter(System.out));
		
		dis = new int[n][n];
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j) dis[i][j] = (i == j ? 0 : INF);
		
		m = nextInt();
		for(int _ = 0; _ < m; ++_) {
			int a = encode(nextString().charAt(0));
			int b = encode(nextString().charAt(0));
			int c = nextInt();
			//out.write(a + " " + b + " " + c + "\n");
			dis[a][b] = dis[b][a] = Math.min(dis[a][b], c);
		}
		floyd();
		
		int res = 26;
		for(int i = 26; i < n - 1; ++i)
			if(dis[i][n - 1] < dis[res][n - 1]) res = i;
		out.write((char)('A' + res - 26) + " " + dis[res][n - 1] + "\n");

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
		new comehome().solve();
	}
}
 