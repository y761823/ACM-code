import java.util.*;
import java.math.*;
import java.io.*;

public class Solution {
	static BufferedReader in;
	static BufferedWriter out;
	static StringTokenizer tokenizer;

	BigInteger getPower(BigInteger x, int p) {
		BigInteger res = BigInteger.ONE;
		while(p > 0) {
			if((p & 1) != 0) res = res.multiply(x);
			x = x.multiply(x);
			p >>= 1;
		}
		return res;
	}
	
	int gcd(int a, int b) {
		return b == 0 ? a : gcd(b, a % b);
	}
	
	void solve() throws Exception {
		in = new BufferedReader(new InputStreamReader(System.in)); out = new BufferedWriter(new OutputStreamWriter(System.out));
		int n = nextInt();
		
		int cnt[] = new int[n + 1];
		for(int i = 0; i < n; ++i)
			cnt[gcd(n, i)]++;
		
		BigInteger TWO = BigInteger.valueOf(2);
		BigInteger ans = BigInteger.ZERO;
		for(int i = 1; i <= n; ++i) if(cnt[i] > 0) {
			ans = ans.add(getPower(TWO, i).multiply(BigInteger.valueOf(cnt[i])));
		}
		ans = ans.divide(BigInteger.valueOf(n));
		out.write(ans + "\n");
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
