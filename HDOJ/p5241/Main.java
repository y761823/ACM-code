import java.util.*;
import java.math.*;
import java.io.*;

public class Main {
	static BufferedReader in;
	static BufferedWriter out;
	static StringTokenizer tokenizer;

	void solve() throws Exception {
		in = new BufferedReader(new InputStreamReader(System.in)); out = new BufferedWriter(new OutputStreamWriter(System.out));
		BigInteger res[] = new BigInteger[3001], tmp = BigInteger.valueOf(32);
		res[0] = BigInteger.valueOf(1);
		for(int i = 1; i <= 3000; ++i)
			res[i] = res[i - 1].multiply(tmp);
		
		int T = nextInt();
		for(int t = 1; t <= T; ++t) {
			int n = nextInt();
			out.write("Case #" + t + ": " + res[n] + "\r\n");
		}
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
		new Main().solve();
	}
}
