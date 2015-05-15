/*
ID: y7618231
LANG: JAVA
TASK: milk
 */
import java.util.*;
import java.math.*;
import java.io.*;

public class milk {
	static final int MAXN = 33;
	static BufferedReader in;
	static BufferedWriter out;
	static StringTokenizer tokenizer;

	public class Node {
		int p, a;
	}
	Node milk[];
	
	public class MyComparator implements Comparator<Node> {
		public int compare(Node a, Node b) {
			return a.p - b.p;
		}
	}
	
	milk() {
	}
	
	void solve() throws Exception{
		in = new BufferedReader(new FileReader("milk.in")); out = new BufferedWriter(new FileWriter("milk.out"));
		//in = new BufferedReader(new InputStreamReader(System.in)); out = new BufferedWriter(new OutputStreamWriter(System.out));
		
		tokenizer = new StringTokenizer(in.readLine());
		int n = Integer.parseInt(tokenizer.nextToken()), m = Integer.parseInt(tokenizer.nextToken());
		milk = new Node[m];
		for(int i = 0; i < m; ++i) {
			tokenizer = new StringTokenizer(in.readLine());
			milk[i] = new Node();
			milk[i].p = Integer.parseInt(tokenizer.nextToken());
			milk[i].a = Integer.parseInt(tokenizer.nextToken());
		}
		Arrays.sort(milk, new MyComparator());
		long res = 0;
		for(int i = 0; i < m && n > 0; ++i) {
			int tmp = Math.min(milk[i].a, n);
			n -= tmp;
			res += tmp * (long)milk[i].p;
		}
		out.write(res + "\n");
		out.flush();
	}
	
	public static void main(String args[]) throws Exception{
		new milk().solve();
	}
}
