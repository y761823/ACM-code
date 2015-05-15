/*
ID: y7618231
LANG: JAVA
TASK: inflate
 */
import java.util.*;
import java.math.*;
import java.io.*;

public class inflate {
	static final int MAXN = 110;
	static BufferedReader in;
	static BufferedWriter out;
	static StringTokenizer tokenizer;

	int n, m;
	
	void solve() throws Exception{
		in = new BufferedReader(new FileReader("inflate.in")); out = new BufferedWriter(new FileWriter("inflate.out"));
		//in = new BufferedReader(new InputStreamReader(System.in)); out = new BufferedWriter(new OutputStreamWriter(System.out));

		m = nextInt(); n = nextInt();
		int dp[] = new int[m + 1];
		for(int i = 0; i < n; ++i) {
			int val = nextInt(), cost = nextInt();
			for(int j = cost; j <= m; ++j)
				dp[j] = Math.max(dp[j], dp[j - cost] + val);
		}
		
		out.write(dp[m] + "\n");
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
		new inflate().solve();
	}
}
