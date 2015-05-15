/*
ID: y7618231
LANG: JAVA
TASK: buylow
 */
import java.util.*;
import java.math.*;
import java.io.*;

public class buylow {
	static final int MAXN = 1010;
	static BufferedReader in;
	static BufferedWriter out;
	static StringTokenizer tokenizer;

	BigInteger sum[];
	int dp[], a[];
	int n;
	
	void work() throws Exception {
		int res1 = 0;
		dp = new int[n];
		for(int i = 0; i < n; ++i) {
			dp[i] = 1;
			for(int j = 0; j < i; ++j) if(a[j] > a[i])
				dp[i] = Math.max(dp[i], dp[j] + 1);
			res1 = Math.max(res1, dp[i]);
		}
		
		sum = new BigInteger[n];
		for(int i = 0; i < n; ++i) sum[i] = dp[i] == 1 ? BigInteger.ONE : BigInteger.ZERO;
		for(int i = 0; i < n; ++i) {
			for(int j = i + 1; j < n; ++j) {
				if(a[i] == a[j]) break;
				if(a[i] > a[j] && dp[i] + 1 == dp[j])
					sum[j] = sum[j].add(sum[i]);
			}
		}
		
		BigInteger res2 = BigInteger.ZERO;
		for(int i = 0; i < n; ++i) if(dp[i] == res1){
			boolean flag = true;
			for(int j = i + 1; flag && j < n; ++j)
				flag = (a[i] != a[j]);
			if(flag) res2 = res2.add(sum[i]);
		}
		out.write(res1 + " " + res2 + "\n");
	}
	
	void solve() throws Exception {
		in = new BufferedReader(new FileReader("buylow.in")); out = new BufferedWriter(new FileWriter("buylow.out"));
		//in = new BufferedReader(new InputStreamReader(System.in)); out = new BufferedWriter(new OutputStreamWriter(System.out));
		
		n = nextInt();
		a = new int[n];
		for(int i = 0; i < n; ++i) a[i] = nextInt();
		work();

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
		new buylow().solve();
	}
}
