/*
ID: y7618231
LANG: JAVA
TASK: prefix
 */
import java.util.*;
import java.math.*;
import java.io.*;

public class prefix {
	static final int MAXN = 33;
	static final int seed = 131;
	static final int MOD = 1000000007;
	static BufferedReader in;
	static BufferedWriter out;
	static StringTokenizer tokenizer;

	Set<Integer> hash;

	int get_hash(String s) {
		long res = 0;
		for(char c : s.toCharArray()) res = (res * seed + c) % MOD;
		return (int)res;
	}
	
	void solve() throws Exception{
		in = new BufferedReader(new FileReader("prefix.in")); out = new BufferedWriter(new FileWriter("prefix.out"));
		//in = new BufferedReader(new InputStreamReader(System.in)); out = new BufferedWriter(new OutputStreamWriter(System.out));
		
		hash = new HashSet<Integer>();
		while(true) {
			tokenizer = new StringTokenizer(in.readLine());
			String s = tokenizer.nextToken();
			if(s.equals(".")) break;
			hash.add(get_hash(s));
			while(tokenizer.hasMoreTokens())
				hash.add(get_hash(tokenizer.nextToken()));
		}
		
		StringBuilder stmp = new StringBuilder();
		while(in.ready()) stmp.append(in.readLine());
		String s = stmp.toString();
		in.readLine();
		boolean vis[] = new boolean[s.length() + 1];
		vis[0] = true;
		int res = 0;
		for(int i = 0; i <= s.length(); ++i) {
			if(!vis[i]) continue;
			res = i;
			long val = 0;
			for(int j = i; j < i + 10 && j < s.length(); ++j) {
				val = (val * seed + s.charAt(j)) % MOD;
				//out.write(val + "\n");
				if(hash.contains((int)val)) vis[j + 1] = true;
			}
		}
		
		out.write(res + "\n");
		out.flush();
	}
	
	public static void main(String args[]) throws Exception{
		new prefix().solve();
	}
}
