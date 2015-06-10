import java.util.*;
import java.math.*;
import java.io.*;

public class Main {
	static BufferedReader in;
	static BufferedWriter out;
	static StringTokenizer tokenizer;

	void solve() throws Exception {
		in = new BufferedReader(new InputStreamReader(System.in)); out = new BufferedWriter(new OutputStreamWriter(System.out));
		BigInteger res = BigInteger.ZERO, tmp;
		while(true) {
			tmp = new BigInteger(nextString());
			if(tmp.equals(BigInteger.ZERO)) break;
			res = res.add(tmp);
		}
		out.write(res + "\r\n");
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
