/*
ID: y7618231
LANG: JAVA
TASK: frac1
 */
import java.util.*;
import java.math.*;
import java.io.*;

public class frac1 {
	static final int MAXN = 1010;
	static BufferedReader in;
	static BufferedWriter out;
	static StringTokenizer tokenizer;

	int gcd(int a, int b) {
		return b == 0 ? a : gcd(b, a % b);
	}
	
	int n;
	
	public class Node implements Comparable<Node> {
		int a, b;// a/b
		void simplify() {
			int t = gcd(a, b);
			a /= t; b /= t;
		}
		Node() {}
		Node(int _a, int _b) {
			a = _a; b = _b;
		}
		@Override
		public int compareTo(Node rhs) {
			// TODO Auto-generated method stub
			return a * rhs.b - b * rhs.a;
		}
	}
	
	void solve() throws Exception{
		in = new BufferedReader(new FileReader("frac1.in")); out = new BufferedWriter(new FileWriter("frac1.out"));
		//in = new BufferedReader(new InputStreamReader(System.in)); out = new BufferedWriter(new OutputStreamWriter(System.out));

		n = Integer.parseInt(in.readLine());
		
		ArrayList<Node> arr = new ArrayList<Node>();
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= i; ++j) {
				arr.add(new Node(j, i));
			}
		for(Node x : arr) x.simplify();
		Collections.sort(arr);
		
		Node pre = null;
		out.write("0/1\n");
		for(Node now : arr) {
			if(pre != null && pre.compareTo(now) == 0) continue;
			out.write(now.a + "/" + now.b + "\n");
			pre = now;
		}
		out.flush();
	}
	
	public static void main(String args[]) throws Exception{
		new frac1().solve();
	}
}
