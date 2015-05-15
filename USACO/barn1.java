/*
ID: y7618231
LANG: JAVA
TASK: barn1
 */
import java.util.*;
import java.math.*;
import java.io.*;

public class barn1 {
	static final int MAXN = 33;
	static BufferedReader in;
	static BufferedWriter out;
	static StringTokenizer tokenizer;

	void solve() throws Exception{
		in = new BufferedReader(new FileReader("barn1.in")); out = new BufferedWriter(new FileWriter("barn1.out"));
		//in = new BufferedReader(new InputStreamReader(System.in)); out = new BufferedWriter(new OutputStreamWriter(System.out));
		
		tokenizer = new StringTokenizer(in.readLine());
		int m = Integer.parseInt(tokenizer.nextToken());
		int s = Integer.parseInt(tokenizer.nextToken());
		int c = Integer.parseInt(tokenizer.nextToken());
		
		int cow[] = new int[c];
		for(int i = 0; i < c; ++i)
			cow[i] = Integer.parseInt(in.readLine());
		Arrays.sort(cow);
		
		int del[] = new int[c - 1];
		for(int i = 1; i < c; ++i)
			del[i - 1] = cow[i] - cow[i - 1] - 1;
		Arrays.sort(del);
		
		int res = cow[c - 1] - cow[0] + 1;
		for(int i = c - 2, j = 1; i >= 0 && j < m; --i, ++j) {
			res -= del[i];
		}
		out.write(res + "\n");
		
		out.flush();
	}
	
	public static void main(String args[]) throws Exception{
		new barn1().solve();
	}
}
