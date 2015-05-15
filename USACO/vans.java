/*
ID: y7618231
LANG: JAVA
TASK: vans
 */
import java.util.*;
import java.math.*;
import java.io.*;

public class vans {
	static final int MAXN = 1010;
	static BufferedReader in;
	static BufferedWriter out;
	static StringTokenizer tokenizer;

	int n;
	
	void solve() throws Exception {
		in = new BufferedReader(new FileReader("vans.in")); out = new BufferedWriter(new FileWriter("vans.out"));
		//in = new BufferedReader(new InputStreamReader(System.in)); out = new BufferedWriter(new OutputStreamWriter(System.out));
		
		n = nextInt();
		BigInteger f[] = new BigInteger[1001], TWO = BigInteger.valueOf(2);
		f[1] = BigInteger.ZERO;
		f[2] = BigInteger.valueOf(2);
		f[3] = BigInteger.valueOf(4);
		f[4] = BigInteger.valueOf(12);
		for(int i = 5; i <= n; ++i)
			f[i] = f[i - 1].multiply(TWO).add(f[i - 2].multiply(TWO)).subtract(f[i - 3].multiply(TWO)).add(f[i - 4]);
		out.write(f[n] + "\n");

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
		new vans().solve();
	}
}
