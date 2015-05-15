/*
ID: y7618231
LANG: JAVA
TASK: combo
 */
import java.util.*;
import java.math.*;
import java.io.*;

public class combo {
	static final int MAXN = 33;
	static BufferedReader in;
	static BufferedWriter out;
	static StringTokenizer tokenizer;
	
	int a[], b[], c[];
	int n;
	
	boolean check(int x, int y) {
		return Math.min(Math.abs(x - y), Math.min(x, y) + n - Math.max(x, y)) <= 2;
	}
	
	boolean check(int x[], int y[]) {
		for(int i = 0; i < 3; ++i)
			if(!check(x[i], y[i])) return false;
		return true;
	}
	
	int work() {
		int ans = 0;
		for(c[0] = 1; c[0] <= n; ++c[0])
			for(c[1] = 1; c[1] <= n; ++c[1])
				for(c[2] = 1; c[2] <= n; ++c[2])
					if(check(a, c) || check(b, c)) ans++;
		return ans;
	}
	
	void solve() throws Exception{
		in = new BufferedReader(new FileReader("combo.in")); out = new BufferedWriter(new FileWriter("combo.out"));
		//in = new BufferedReader(new InputStreamReader(System.in)); out = new BufferedWriter(new OutputStreamWriter(System.out));

		a = new int[3];
		b = new int[3];
		c = new int[3];
		
		n = Integer.parseInt(in.readLine());
		tokenizer = new StringTokenizer(in.readLine());
		for(int i = 0; i < 3; ++i) a[i] = Integer.parseInt(tokenizer.nextToken());
		tokenizer = new StringTokenizer(in.readLine());
		for(int i = 0; i < 3; ++i) b[i] = Integer.parseInt(tokenizer.nextToken());
		
		out.write(work() + "\n");
		out.flush();
	}
	
	public static void main(String args[]) throws Exception{
		new combo().solve();
	}
}
