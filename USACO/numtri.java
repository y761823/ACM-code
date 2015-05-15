/*
ID: y7618231
LANG: JAVA
TASK: numtri
 */
import java.util.*;
import java.math.*;
import java.io.*;

public class numtri {
	static final int MAXN = 1010;
	static BufferedReader in;
	static BufferedWriter out;
	static StringTokenizer tokenizer;

	int dp[][], n;
	
	void solve() throws Exception{
		in = new BufferedReader(new FileReader("numtri.in")); out = new BufferedWriter(new FileWriter("numtri.out"));
		//in = new BufferedReader(new InputStreamReader(System.in)); out = new BufferedWriter(new OutputStreamWriter(System.out));
		
		n = Integer.parseInt(in.readLine());
		dp = new int[n][n];
		for(int i = 0; i < n; ++i) {
			dp[i] = new int[n];
			tokenizer = new StringTokenizer(in.readLine());
			for(int j = 0; j <= i; ++j)
				dp[i][j] = Integer.parseInt(tokenizer.nextToken());
		}
		
		for(int i = n - 2; i >= 0; --i)
			for(int j = 0; j <= i; ++j)
				dp[i][j] += Math.max(dp[i + 1][j], dp[i + 1][j + 1]);
		out.write(dp[0][0] + "\n");
		
		out.flush();
	}
	
	public static void main(String args[]) throws Exception{
		new numtri().solve();
	}
}
