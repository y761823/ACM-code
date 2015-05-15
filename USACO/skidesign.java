/*
ID: y7618231
LANG: JAVA
TASK: skidesign
 */
import java.util.*;
import java.math.*;
import java.io.*;

public class skidesign {
	static final int MAXN = 33;
	static BufferedReader in;
	static BufferedWriter out;
	static StringTokenizer tokenizer;
	
	int h[], n;
	
	int work() {
		int res = 0x3f3f3f3f;
		for(int low = 0; low <= 100 - 17; ++low) {
			int high = low + 17, cnt = 0;
			for(int i = 0; i < n; ++i) {
				int p = 0;
				if(h[i] < low) p = low - h[i];			
				if(h[i] > high) p = h[i] - high;
				cnt += p * p;
			}
			res = Math.min(res, cnt);
		}
		return res;
	}
	
	void solve() throws Exception{
		in = new BufferedReader(new FileReader("skidesign.in")); out = new BufferedWriter(new FileWriter("skidesign.out"));
		//in = new BufferedReader(new InputStreamReader(System.in)); out = new BufferedWriter(new OutputStreamWriter(System.out));

		n = Integer.parseInt(in.readLine());
		h = new int[n];
		for(int i = 0; i < n; ++i) h[i] = Integer.parseInt(in.readLine());
		
		out.write(work() + "\n");
		out.flush();
	}
	
	public static void main(String args[]) throws Exception{
		new skidesign().solve();
	}
}
