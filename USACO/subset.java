/*
ID: y7618231
LANG: JAVA
TASK: subset
 */
import java.util.*;
import java.math.*;
import java.io.*;

public class subset {
	static final int MAXN = 1010;
	static BufferedReader in;
	static BufferedWriter out;
	static StringTokenizer tokenizer;

	long dp[][];
	int n, sum;
	
	long work() {
		if(sum % 2 == 1) return 0;
		dp = new long[n + 1][sum / 2 + 1];
		dp[1][1] = 1;
		for(int i = 1; i < n; ++i) {
			for(int j = 0; j <= sum / 2; ++j) {
				dp[i + 1][j] += dp[i][j];
				if(j + i + 1 <= sum / 2) dp[i + 1][j + i + 1] += dp[i][j];
			}
		}
		return dp[n][sum / 2];
	}
	
	void solve() throws Exception{
		in = new BufferedReader(new FileReader("subset.in")); out = new BufferedWriter(new FileWriter("subset.out"));
		//in = new BufferedReader(new InputStreamReader(System.in)); out = new BufferedWriter(new OutputStreamWriter(System.out));

		n = Integer.parseInt(in.readLine());
		sum = n * (n + 1) / 2;
		out.write(work() + "\n");
		
		out.flush();
	}
	
	public static void main(String args[]) throws Exception{
		new subset().solve();
	}
}
