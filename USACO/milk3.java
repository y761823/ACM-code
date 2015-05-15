/*
ID: y7618231
LANG: JAVA
TASK: milk3
 */
import java.util.*;
import java.math.*;
import java.io.*;

public class milk3 {
	static final int MAXN = 33;
	static BufferedReader in;
	static BufferedWriter out;
	static StringTokenizer tokenizer;
	
	int a, b, c;
	Set<Integer> st, ans;
	
	int[] fill(int x, int y, int c) {
		int res[] = new int[2];
		if(x > c - y) {
			res[1] = c;
			res[0] = x - (c - y);
		} else {
			res[1] = y + x;
			res[0] = 0;
		}
		return res;
	}
	
	void dfs(int x, int y, int z) throws Exception{
		int hash = x * 2222 + y * 22 + z;
		if(st.contains(hash)) return ;
		st.add(hash);
		//out.write(x + " " + y + " " + z + "\n");
		if(x == 0) ans.add(z);
		int tmp[];

		tmp = fill(x, y, b); dfs(tmp[0], tmp[1], z);
		tmp = fill(x, z, c); dfs(tmp[0], y, tmp[1]);
		
		tmp = fill(y, x, a); dfs(tmp[1], tmp[0], z);
		tmp = fill(y, z, c); dfs(x, tmp[0], tmp[1]);

		tmp = fill(z, x, a); dfs(tmp[1], y, tmp[0]);
		tmp = fill(z, y, b); dfs(x, tmp[1], tmp[0]);
	}
	
	void solve() throws Exception{
		in = new BufferedReader(new FileReader("milk3.in")); out = new BufferedWriter(new FileWriter("milk3.out"));
		//in = new BufferedReader(new InputStreamReader(System.in)); out = new BufferedWriter(new OutputStreamWriter(System.out));
		
		tokenizer = new StringTokenizer(in.readLine());
		a = Integer.parseInt(tokenizer.nextToken());
		b = Integer.parseInt(tokenizer.nextToken());
		c = Integer.parseInt(tokenizer.nextToken());

		st = new TreeSet<Integer>();
		ans = new TreeSet<Integer>();
		
		dfs(0, 0, c);
		boolean flag = true;
		for(Integer x : ans) {
			if(!flag) out.write(" "); 
			flag = false;
			out.write(String.valueOf(x));
		}
		out.write("\n");
		
		out.flush();
	}
	
	public static void main(String args[]) throws Exception{
		new milk3().solve();
	}
}
