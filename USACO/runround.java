/*
ID: y7618231
LANG: JAVA
TASK: runround
 */
import java.util.*;
import java.math.*;
import java.io.*;

public class runround {
	static final int MAXN = 1010;
	static BufferedReader in;
	static BufferedWriter out;
	static StringTokenizer tokenizer;

	ArrayList<Integer> ans;
	int n;
	
	boolean check(int x) {
		String s = String.valueOf(x);
		boolean vis[] = new boolean[s.length()];
		for(int pos = 0, step = 0; step < s.length(); ++step) {
			pos = (pos + s.charAt(pos) - '0') % s.length();
			if(vis[pos]) return false;
			vis[pos] = true;
		}
		return true;
	}
	
	boolean use[];
	void dfs(int val) {
		if(val > 0 && check(val)) ans.add(val);
		for(int i = 1; i <= 9; ++i) {
			if(use[i]) continue;
			use[i] = true;
			dfs(val * 10 + i);
			use[i] = false;
		}
	}
	
	void solve() throws Exception{
		in = new BufferedReader(new FileReader("runround.in")); out = new BufferedWriter(new FileWriter("runround.out"));
		//in = new BufferedReader(new InputStreamReader(System.in)); out = new BufferedWriter(new OutputStreamWriter(System.out));

		ans = new ArrayList<Integer>();
		use = new boolean[10];
		dfs(0);
		Collections.sort(ans);
		//for(Integer x : ans) out.write(x + "\n");
		
		n = Integer.parseInt(in.readLine()) + 1;
		int t = Collections.binarySearch(ans, n);
		if(t < 0) t = -t - 1;
		//out.write(t + "\n"); out.flush();
		out.write(ans.get(t) + "\n");
		
		out.flush();
	}
	
	public static void main(String args[]) throws Exception{
		new runround().solve();
	}
}
