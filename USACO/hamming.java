/*
ID: y7618231
LANG: JAVA
TASK: hamming
 */
import java.util.*;
import java.math.*;
import java.io.*;

public class hamming {
	static final int MAXN = 1010;
	static BufferedReader in;
	static BufferedWriter out;
	static StringTokenizer tokenizer;

	int n, b, d;
	
	boolean check(int x, int y) {
		return Integer.bitCount(x ^ y) >= d;
	}
	
	void solve() throws Exception{
		in = new BufferedReader(new FileReader("hamming.in")); out = new BufferedWriter(new FileWriter("hamming.out"));
		//in = new BufferedReader(new InputStreamReader(System.in)); out = new BufferedWriter(new OutputStreamWriter(System.out));

		tokenizer = new StringTokenizer(in.readLine());
		n = Integer.parseInt(tokenizer.nextToken());
		b = Integer.parseInt(tokenizer.nextToken());
		d = Integer.parseInt(tokenizer.nextToken());
		
		int ans[] = new int[n], cnt = 0;
		ans[cnt++] = 0;
		for(int i = 0; i < (1 << b); ++i) {
			boolean flag = true;
			for(int j = 0; j < cnt; ++j)
				if(!check(i, ans[j])) flag = false;
			if(flag) {
				ans[cnt++] = i;
				if(cnt == n) break;
			}
		}
		
		for(int i = 0; i < n; ++i) {
			out.write(ans[i] + "");
			out.write((i + 1) % 10 == 0 || i == n - 1 ? "\n" : " ");
		}

		out.flush();
	}
	
	public static void main(String args[]) throws Exception{
		new hamming().solve();
	}
}
