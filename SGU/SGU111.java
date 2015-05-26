import java.util.*;
import java.math.*;
import java.io.*;

public class Solution {
	static BufferedReader in;
	static BufferedWriter out;
	static StringTokenizer tokenizer;

	void solve() throws Exception {
		in = new BufferedReader(new InputStreamReader(System.in)); out = new BufferedWriter(new OutputStreamWriter(System.out));
		BigInteger x = new BigInteger(nextString()), TWO = BigInteger.valueOf(2);
		BigInteger l = BigInteger.ONE, r = BigInteger.valueOf(10).pow(500).add(BigInteger.ONE);
		while(l.compareTo(r) < 0) {
			BigInteger mid = l.add(r).divide(TWO);
			if(mid.multiply(mid).compareTo(x) <= 0) l = mid.add(BigInteger.ONE);
			else r = mid;
		}
		out.write(l.subtract(BigInteger.ONE) + "\n");
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
