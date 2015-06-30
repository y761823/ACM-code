import java.util.*;
import java.math.*;
import java.io.*;

public class Main {
	static BufferedReader in;
	static BufferedWriter out;
	static StringTokenizer tokenizer;

	static final int MAXN = 1000010;
	
	int label[];
	int prime[], total;
	
	void makePrime() {
		int n = 1000000;
		label = new int[n + 1];
		prime = new int[n + 1];
		for(int i = 2; i <= n; ++i) {
			if(label[i] == 0) {
				prime[total++] = i;
				label[i] = total;
			}
			for(int j = 0; j < label[i]; ++j) {
				if(i * prime[j] > n) break;
				label[i * prime[j]] = j + 1;
			}
		}
	}
	
	int check(BigInteger k, int l) {
		for(int i = 0; i < total; ++i) {
			int p = prime[i];
			if(p >= l) break;
			if(k.mod(BigInteger.valueOf(p)).equals(BigInteger.ZERO))
				return p;
		}
		return 0;
	}
	
	void solve() throws Exception {
		in = new BufferedReader(new InputStreamReader(System.in)); out = new BufferedWriter(new OutputStreamWriter(System.out));
		makePrime();
		while(true) {
			BigInteger k = new BigInteger(nextString());
			int l = nextInt();
			if(l == 0) break;
			int res = check(k, l);
			if(res == 0) out.write("GOOD\n");
			else out.write("BAD " + res + "\n");
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
