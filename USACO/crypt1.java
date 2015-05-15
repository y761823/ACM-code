/*
ID: y7618231
LANG: JAVA
TASK: crypt1
 */
import java.util.*;
import java.math.*;
import java.io.*;

public class crypt1 {
	static final int MAXN = 33;
	static BufferedReader in;
	static BufferedWriter out;
	static StringTokenizer tokenizer;
	
	boolean exist[];

	boolean check(int x, int n) {
		char[] s = String.valueOf(x).toCharArray();
		if(s.length != n) return false;
		for(int i = 0; i < s.length; ++i)
			if(!exist[s[i] - '0']) return false;
		return true;
	}
	
	boolean check(int a, int b, int c) {
		return check(a, 3) && check(b, 1) && check(c, 1) &&
				check(a * b, 3) && check(a * c, 3) && check(a * (b * 10 + c), 4);
	}
	
	int work() {
		int ans = 0;
		for(int a = 1; a <= 999; ++a)
			for(int b = 1; b <= 9; ++b)
				for(int c = 1; c <= 9; ++c) if(check(a, b, c)) ans++;
		return ans;
	}
	
	void solve() throws Exception{
		in = new BufferedReader(new FileReader("crypt1.in")); out = new BufferedWriter(new FileWriter("crypt1.out"));
		//in = new BufferedReader(new InputStreamReader(System.in)); out = new BufferedWriter(new OutputStreamWriter(System.out));
		
		exist = new boolean[10];
		int n = Integer.parseInt(in.readLine());
		tokenizer = new StringTokenizer(in.readLine());
		for(int i = 0; i < n; ++i)
			exist[Integer.parseInt(tokenizer.nextToken())] = true;
		
		out.write(work() + "\n");
		out.flush();
	}
	
	public static void main(String args[]) throws Exception{
		new crypt1().solve();
	}
}
