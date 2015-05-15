/*
ID: y7618231
LANG: JAVA
TASK: preface
 */
import java.util.*;
import java.math.*;
import java.io.*;

public class preface {
	static final int MAXN = 1010;
	static BufferedReader in;
	static BufferedWriter out;
	static StringTokenizer tokenizer;

	int n, I, V, X, L, C, D, M;

	void add_1(int x) {
		if(x <= 3) I += x;
		if(x == 4) { I++; V++; }
		if(x == 5) V++;
		if(6 <= x && x <= 8) { V++; I += x - 5; }
		if(x == 9) { I++; X++; }
	}
	
	void add_2(int x) {
		if(x <= 3) X += x;
		if(x == 4) { X++; L++; }
		if(x == 5) L++;
		if(6 <= x && x <= 8) { L++; X += x - 5; }
		if(x == 9) { X++; C++; }
	}
	
	void add_3(int x) {
		if(x <= 3) C += x;
		if(x == 4) { C++; D++; }
		if(x == 5) D++;
		if(6 <= x && x <= 8) { D++; C += x - 5; }
		if(x == 9) { C++; M++; }
	}
	
	void add_4(int x) {
		M += x;
	}
	
	void add(int x) {
		if(x >= 1) add_1(x % 10); x /= 10;
		if(x >= 1) add_2(x % 10); x /= 10;
		if(x >= 1) add_3(x % 10); x /= 10;
		if(x >= 1) add_4(x % 10); x /= 10;
	}
	
	void solve() throws Exception{
		in = new BufferedReader(new FileReader("preface.in")); out = new BufferedWriter(new FileWriter("preface.out"));
		//in = new BufferedReader(new InputStreamReader(System.in)); out = new BufferedWriter(new OutputStreamWriter(System.out));

		I = V = X = L = C = D = M = 0;
		n = Integer.parseInt(in.readLine());
		
		for(int i = 1; i <= n; ++i) add(i);
		if(I > 0) out.write("I " + I + "\n");
		if(V > 0) out.write("V " + V + "\n");
		if(X > 0) out.write("X " + X + "\n");
		if(L > 0) out.write("L " + L + "\n");
		if(C > 0) out.write("C " + C + "\n");
		if(D > 0) out.write("D " + D + "\n");
		if(M > 0) out.write("M " + M + "\n");
		
		out.flush();
	}
	
	public static void main(String args[]) throws Exception{
		new preface().solve();
	}
}
