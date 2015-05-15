/*
ID: y7618231
LANG: JAVA
TASK: money
 */
import java.util.*;
import java.math.*;
import java.io.*;

public class money {
	static final int MAXN = 10010;
	static final int seed = 131;
	static final int MOD = 9901;
	static BufferedReader in;
	static BufferedWriter out;
	static StringTokenizer tokenizer;

	long dp[];
	int p[], n, m;
	
	long work() {
		dp = new long[m + 1];
		dp[0] = 1;
		for(int i = 0; i < n; ++i) {
			for(int j = p[i]; j <= m; ++j)
				dp[j] += dp[j - p[i]];
		}
		return dp[m];
	}
	
	void solve() throws Exception{
		in = new BufferedReader(new FileReader("money.in")); out = new BufferedWriter(new FileWriter("money.out"));
		//in = new BufferedReader(new InputStreamReader(System.in)); out = new BufferedWriter(new OutputStreamWriter(System.out));

		tokenizer = new StringTokenizer(in.readLine());
		n = Integer.parseInt(tokenizer.nextToken());
		m = Integer.parseInt(tokenizer.nextToken());
		
		p = new int[n];
		for(int i = 0; i < n; ++i) {
			while(!tokenizer.hasMoreTokens()) tokenizer = new StringTokenizer(in.readLine());
			p[i] = Integer.parseInt(tokenizer.nextToken());
		}

		out.write(work() + "\n");
		out.flush();
	}
	
	public static void main(String args[]) throws Exception{
		new money().solve();
	}
}
