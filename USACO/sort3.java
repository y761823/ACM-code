/*
ID: y7618231
LANG: JAVA
TASK: sort3
 */
import java.util.*;
import java.math.*;
import java.io.*;

public class sort3 {
	static final int MAXN = 1010;
	static BufferedReader in;
	static BufferedWriter out;
	static StringTokenizer tokenizer;

	int cnt[], a[], b[][];
	int n;
	
	void solve() throws Exception{
		in = new BufferedReader(new FileReader("sort3.in")); out = new BufferedWriter(new FileWriter("sort3.out"));
		//in = new BufferedReader(new InputStreamReader(System.in)); out = new BufferedWriter(new OutputStreamWriter(System.out));

		n = Integer.parseInt(in.readLine());
		a = new int[n];
		cnt = new int[4];
		for(int i = 0; i < n; ++i)
			cnt[a[i] = Integer.parseInt(in.readLine())]++;
		cnt[2] += cnt[1]; cnt[3] += cnt[2];
		
		b = new int[4][4];
		for(int i = 0; i < n; ++i) {
			if(i < cnt[1]) b[1][a[i]]++;
			else if(i < cnt[2]) b[2][a[i]]++;
			else b[3][a[i]]++;
		}
		
		int res = 0, t;
		t = Math.min(b[1][2], b[2][1]);
		res += t;
		b[1][2] -= t; b[2][1] -= t;
		
		t = Math.min(b[1][3], b[3][1]);
		res += t;
		b[1][3] -= t; b[3][1] -= t;
		
		t = Math.min(b[2][3], b[3][2]);
		res += t;
		b[2][3] -= t; b[3][2] -= t;
		
		t = b[2][1];
		res += t;
		b[2][1] -= t; b[2][3] += t; b[1][3] -= t;
		
		t = b[3][1];
		res += t;
		b[3][1] -= t; b[3][2] += t; b[1][2] -= t;
		
		res += b[2][3];

		out.write(res + "\n");
		out.flush();
	}
	
	public static void main(String args[]) throws Exception{
		new sort3().solve();
	}
}
