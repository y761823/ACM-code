/*
ID: y7618231
LANG: JAVA
TASK: fracdec
 */
import java.util.*;
import java.math.*;
import java.io.*;

public class fracdec {
	static final int MAXN = 110;
	static final int seed = 131;
	static final int MOD = 9901;
	static final int INF = 0x3f3f3f3f;
	static BufferedReader in;
	static BufferedWriter out;
	static StringTokenizer tokenizer;

	int n, d, f;
	
	void write(char c) throws Exception {
		if(++f % 76 == 0) out.write("\n");
		out.write(c + "");
	}
	
	void solve() throws Exception{
		in = new BufferedReader(new FileReader("fracdec.in")); out = new BufferedWriter(new FileWriter("fracdec.out"));
		//in = new BufferedReader(new InputStreamReader(System.in)); out = new BufferedWriter(new OutputStreamWriter(System.out));
		
		n = nextInt(); d = nextInt();
		String str = n / d + ".";
		out.write(str);
		n %= d;
		
		int first[] = new int[1000010];
		for(int i = 0; i < first.length; ++i) first[i] = -1;
		char s[] = new char[100010];
		int cnt = 0;
		
		while(true) {
			n *= 10;
			if(first[n] != -1) break;
			first[n] = cnt;
			s[cnt] = (char)(n / d + '0');
			n %= d;
			cnt++;
			if(n == 0) break;
		}
		
		f = str.length() - 1;
		if(n == 0) {
			for(int i = 0; i < cnt; ++i) write(s[i]);
		} else {
			for(int i = 0; i < first[n]; ++i) write(s[i]);
			write('(');
			for(int i = first[n]; i < cnt; ++i) write(s[i]);
			write(')');
		}
		if(f % 76 != 0) out.write("\n");
		out.flush();
	}
	
	String nextString() throws Exception{
		while(tokenizer == null || !tokenizer.hasMoreTokens())
			tokenizer = new StringTokenizer(in.readLine());
		return tokenizer.nextToken();
	}
	
	int nextInt() throws Exception {
		return Integer.parseInt(nextString());
	}
	
	public static void main(String args[]) throws Exception{
		new fracdec().solve();
	}
}
 