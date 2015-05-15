/*
ID: y7618231
LANG: JAVA
TASK: holstein
 */
import java.util.*;
import java.math.*;
import java.io.*;

public class holstein {
	static final int MAXN = 1010;
	static BufferedReader in;
	static BufferedWriter out;
	static StringTokenizer tokenizer;

	int mat[][], need[];
	int m, n;
	
	boolean check(int state) {
		int has[] = new int[m];
		for(int i = 0; i < n; ++i) {
			if((state & (1 << i)) != 0)
				for(int j = 0; j < m; ++j) has[j] += mat[i][j];
		}
		for(int i = 0; i < m; ++i)
			if(has[i] < need[i]) return false;
		return true;
	}
	
	int work() {
		int res = (1 << n) - 1;
		for(int i = 0, ed = (1 << n); i < ed; ++i) {
			if(check(i) && Integer.bitCount(i) < Integer.bitCount(res))
				res = i;
		}
		return res;
	}
	
	void solve() throws Exception{
		in = new BufferedReader(new FileReader("holstein.in")); out = new BufferedWriter(new FileWriter("holstein.out"));
		//in = new BufferedReader(new InputStreamReader(System.in)); out = new BufferedWriter(new OutputStreamWriter(System.out));

		m = Integer.parseInt(in.readLine());
		tokenizer = new StringTokenizer(in.readLine());
		need = new int[m];
		for(int i = 0; i < m; ++i)
			need[i] = Integer.parseInt(tokenizer.nextToken());
		
		n = Integer.parseInt(in.readLine());
		mat = new int[n][m];
		for(int i = 0; i < n; ++i) {
			tokenizer = new StringTokenizer(in.readLine());
			for(int j = 0; j < m; ++j)
				mat[i][j] = Integer.parseInt(tokenizer.nextToken());
		}
		
		int ans = work();
		out.write(String.valueOf(Integer.bitCount(ans)));
		for(int i = 0; i < n; ++i)
			if((ans & (1 << i)) != 0) out.write(" " + (i + 1));
		out.write("\n");

		out.flush();
	}
	
	public static void main(String args[]) throws Exception{
		new holstein().solve();
	}
}
