/*
ID: y7618231
LANG: JAVA
TASK: zerosum
 */
import java.util.*;
import java.math.*;
import java.io.*;

public class zerosum {
	static final int MAXN = 33;
	static final int seed = 131;
	static final int MOD = 9901;
	static BufferedReader in;
	static BufferedWriter out;
	static StringTokenizer tokenizer;

	int n, k;
	char c[];
	
	void print() throws Exception {
		for(int i = 1; i <= n; ++i) {
			if(i != 1) out.write(c[i] + "");
			out.write(i + "");
		}
		out.write("\n");
	}
	
	void dfs(int sum, int last, int flag, int k) throws Exception {
		if(k == n + 1) {
			if(sum == 0) print();
		} else {
			c[k] = ' ';
			dfs(sum - flag * last + flag * (last * 10 + k), last * 10 + k, flag, k + 1);
			c[k] = '+';
			dfs(sum + k, k, 1, k + 1);
			c[k] = '-';
			dfs(sum - k, k, -1, k + 1);
		}
	}
		
	void solve() throws Exception{
		in = new BufferedReader(new FileReader("zerosum.in")); out = new BufferedWriter(new FileWriter("zerosum.out"));
		//in = new BufferedReader(new InputStreamReader(System.in)); out = new BufferedWriter(new OutputStreamWriter(System.out));
		
		n = Integer.parseInt(in.readLine());
		c = new char[n + 1];
		dfs(1, 1, 1, 2);

		out.flush();
	}
	
	public static void main(String args[]) throws Exception{
		new zerosum().solve();
	}
}
