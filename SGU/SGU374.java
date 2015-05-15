import java.util.*;
import java.math.*;
import java.io.*;

public class Solution {
	static BufferedReader in;
	static BufferedWriter out;
	static StringTokenizer tokenizer;

	void solve() throws Exception {
		in = new BufferedReader(new InputStreamReader(System.in)); out = new BufferedWriter(new OutputStreamWriter(System.out));
		int a = nextInt(), b = nextInt(), k = nextInt();
		out.write(BigInteger.valueOf(a + b).pow(k) + "\n");
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
		new Solution().solve();
	}
}
