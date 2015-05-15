/*
ID: y7618231
LANG: JAVA
TASK: sprime
 */
import java.util.*;
import java.math.*;
import java.io.*;

public class sprime {
	static final int MAXN = 1010;
	static BufferedReader in;
	static BufferedWriter out;
	static StringTokenizer tokenizer;

	int n;
	
	boolean judge(int x) {
		for(int i = 2; i * i <= x; ++i)
			if(x % i == 0) return false;
		return true;
	}
	
	void dfs(int x, int dep) throws Exception{
		if(dep == n) {
			out.write(x + "\n");
		} else {
			for(int i = 1; i <= 9; i += 2)
				if(judge(x * 10 + i)) dfs(x * 10 + i, dep + 1);
		}
	}
	
	void solve() throws Exception{
		in = new BufferedReader(new FileReader("sprime.in")); out = new BufferedWriter(new FileWriter("sprime.out"));
		//in = new BufferedReader(new InputStreamReader(System.in)); out = new BufferedWriter(new OutputStreamWriter(System.out));
		
		n = Integer.parseInt(in.readLine());

		dfs(2, 1);
		dfs(3, 1);
		dfs(5, 1);
		dfs(7, 1);
		
		out.flush();
	}
	
	public static void main(String args[]) throws Exception{
		new sprime().solve();
	}
}
