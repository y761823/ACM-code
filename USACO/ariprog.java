/*
ID: y7618231
LANG: JAVA
TASK: ariprog
 */
import java.util.*;
import java.math.*;
import java.io.*;

public class ariprog {
	static final int MAXN = 33;
	static BufferedReader in;
	static BufferedWriter out;
	static StringTokenizer tokenizer;
	
	boolean good[];
	int n, m, k;
	
	boolean check(int a, int b) {
		for(int i = a, j = 0; j < n; ++j, i += b)
			if(!good[i]) return false;
		return true;
	}
	
	void solve() throws Exception{
		in = new BufferedReader(new FileReader("ariprog.in")); out = new BufferedWriter(new FileWriter("ariprog.out"));
		//in = new BufferedReader(new InputStreamReader(System.in)); out = new BufferedWriter(new OutputStreamWriter(System.out));

		n = Integer.parseInt(in.readLine());
		m = Integer.parseInt(in.readLine());
		k = 2 * m * m;
		
		good = new boolean[k + 1];
		for(int i = 0; i <= m; ++i)
			for(int j = i; j <= m; ++j) good[i * i + j * j] = true;

		boolean flag = false;
		for(int b = 1; b <= k; ++b) {
			for(int a = 0; a <= k; ++a) {
				if(a + (n - 1) * b > k) break;
				if(check(a, b)) {
					out.write(a + " " + b + "\n");
					flag = true;
				}
			}
		}
		if(!flag) out.write("NONE\n");
		out.flush();
	}
	
	public static void main(String args[]) throws Exception{
		new ariprog().solve();
	}
}
