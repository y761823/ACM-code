/*
ID: y7618231
LANG: JAVA
TASK: dualpal
 */
import java.util.*;
import java.math.*;
import java.io.*;

public class dualpal {
	static final int MAXN = 33;
	static BufferedReader in;
	static BufferedWriter out;
	static StringTokenizer tokenizer;
	
	dualpal() {
	}
	
	boolean check(int n, int B) {
		String s1 = Integer.toString(n, B);
		String s2 = new StringBuilder(s1).reverse().toString();
		return s1.equals(s2);
	}
	
	boolean check(int s) {
		int cnt = 0;
		for(int i = 2; i <= 10 && cnt < 2; ++i)
			if(check(s, i)) cnt++;
		return cnt == 2;
	}
	
	void solve() throws Exception{
		in = new BufferedReader(new FileReader("dualpal.in")); out = new BufferedWriter(new FileWriter("dualpal.out"));
		//in = new BufferedReader(new InputStreamReader(System.in)); out = new BufferedWriter(new OutputStreamWriter(System.out));
		
		tokenizer = new StringTokenizer(in.readLine());
		int n = Integer.parseInt(tokenizer.nextToken()), s = Integer.parseInt(tokenizer.nextToken());
		while(n > 0) {
			s++;
			if(check(s)) {
				out.write(String.valueOf(s) + "\n");
				n--;
			}
		}
		out.flush();
	}
	
	public static void main(String args[]) throws Exception{
		new dualpal().solve();
	}
}
