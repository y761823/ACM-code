/*
ID: y7618231
LANG: JAVA
TASK: nocows
 */
import java.util.*;
import java.math.*;
import java.io.*;

public class nocows {
	static final int MAXN = 33;
	static final int seed = 131;
	static final int MOD = 9901;
	static BufferedReader in;
	static BufferedWriter out;
	static StringTokenizer tokenizer;

	int n, k;
	int dp[][], sum[][];
	
	int work() {
		dp = new int[k + 1][n + 1];
		sum = new int[k + 1][n + 1];
		sum[1][1] = dp[1][1] = 1;
		for(int h = 2; h <= k; ++h) {
			for(int i = 1; i <= n; ++i) {
				for(int j = 1; j < i; ++j) {
					dp[h][i] += 2 * dp[h - 1][j] * sum[h - 1][i - 1 - j];
					dp[h][i] -= (dp[h - 1][j] * dp[h - 1][i - 1 - j]) % MOD;
					dp[h][i] = (dp[h][i] + MOD) % MOD;
				}
			}
			for(int i = 1; i <= n; ++i)
				sum[h][i] = (sum[h - 1][i] + dp[h][i]) % MOD;
		}
		return dp[k][n];
	}
	
	void solve() throws Exception{
		in = new BufferedReader(new FileReader("nocows.in")); out = new BufferedWriter(new FileWriter("nocows.out"));
		//in = new BufferedReader(new InputStreamReader(System.in)); out = new BufferedWriter(new OutputStreamWriter(System.out));
		
		tokenizer = new StringTokenizer(in.readLine());
		n = Integer.parseInt(tokenizer.nextToken());
		k = Integer.parseInt(tokenizer.nextToken());
		
		out.write(work() + "\n");
		out.flush();
	}
	
	public static void main(String args[]) throws Exception{
		new nocows().solve();
	}
}
