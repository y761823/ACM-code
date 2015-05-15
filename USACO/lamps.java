/*
ID: y7618231
LANG: JAVA
TASK: lamps
 */
import java.util.*;
import java.math.*;
import java.io.*;

public class lamps {
	static final int MAXN = 33;
	static BufferedReader in;
	static BufferedWriter out;
	static StringTokenizer tokenizer;

	int state[];
	int n, c, lcm = 12;
	
	boolean input() throws Exception {
		n = Integer.parseInt(in.readLine());
		c = Integer.parseInt(in.readLine());
		state = new int[lcm];
		for(int i = 0; i < lcm; ++i) state[i] = -1;
		
		for(int t = 1; t >= 0; --t) {
			tokenizer = new StringTokenizer(in.readLine());
			while(true) {
				int tmp = Integer.parseInt(tokenizer.nextToken());
				if(tmp == -1) break;
				tmp = (tmp - 1) % lcm;
				if(state[tmp] != -1 && state[tmp] != t) return false;
				state[tmp] = t;
			}
		}
		return true;
	}
	
	String run(int select) throws Exception  {
		int cnt = Integer.bitCount(select);
		if(cnt > c || (c - cnt) % 2 != 0) return "";
		//out.write(Integer.bitCount(select) + " " + select + "\n");
		
		int now[] = new int[lcm];
		for(int i = 0; i < lcm; ++i) now[i] = 1;
		for(int i = 1; i <= 4; ++i) if((select & (1 << (i - 1))) > 0) {
			int st = i == 3 ? 1 : 0, step;
			if(i == 1) step = 1;
			else if(i == 4) step = 3;
			else step = 2;
			for(int j = st; j < lcm; j += step) now[j] ^= 1;
		}
		
		for(int i = 0, ed = Math.min(lcm, n); i < ed; ++i) {
			if(state[i] != -1 && state[i] != now[i]) return "";
		}

		StringBuilder res = new StringBuilder();
		for(int i = 0; i < n; ++i) res.append(now[i % lcm]);
		return res.toString();
	}
	
	boolean work() throws Exception  {
		Set<String> st = new TreeSet<String>();
		for(int i = 0; i < (1 << 4); ++i) {
			String res = run(i);
			if(res.length() != 0) st.add(res);
		}
		for(String s : st) out.write(s + "\n");
		return st.size() > 0;
	}
	
	void solve() throws Exception{
		in = new BufferedReader(new FileReader("lamps.in")); out = new BufferedWriter(new FileWriter("lamps.out"));
		//in = new BufferedReader(new InputStreamReader(System.in)); out = new BufferedWriter(new OutputStreamWriter(System.out));
		
		if(!input() || !work()) out.write("IMPOSSIBLE\n");
		
		out.flush();
	}
	
	public static void main(String args[]) throws Exception{
		new lamps().solve();
	}
}
