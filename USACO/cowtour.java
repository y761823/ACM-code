/*
ID: y7618231
LANG: JAVA
TASK: cowtour
 */
import java.util.*;
import java.math.*;
import java.io.*;

public class cowtour {
	static final int MAXN = 110;
	static final int seed = 131;
	static final int MOD = 9901;
	static BufferedReader in;
	static BufferedWriter out;
	static StringTokenizer tokenizer;

	int n;
	int x[], y[];
	double mat[][], dis[][];
	
	double get_dis(int i, int j) {
		double xx = x[i] - x[j], yy = y[i] - y[j];
		return Math.sqrt(xx * xx + yy * yy);
	}
	
	void floyd() {
		for(int k = 0; k < n; ++k)
			for(int i = 0; i < n; ++i)
				for(int j = 0; j < n; ++j) dis[i][j] = Math.min(dis[i][j], dis[i][k] + dis[k][j]);
	}
	
	boolean vis[];
	double mindis[], maxdis[];

	void make_mnmxdis(int st) {
		ArrayList<Integer> arr = new ArrayList<Integer>();
		for(int i = 0; i < n; ++i) {
			if(dis[st][i] < 1e100) {
				arr.add(i);
				vis[i] = true;
			}
		}
		double tmp = 0;
		for(int i = 0; i < arr.size(); ++i) {
			int u = arr.get(i);
			for(int j = 0; j < arr.size(); ++j) {
				int v = arr.get(j);
				tmp = Math.max(tmp, dis[u][v]);
				maxdis[u] = Math.max(maxdis[u], dis[u][v]);
			}
		}
		for(int i = 0; i < arr.size(); ++i)
			mindis[arr.get(i)] = tmp; 
	}
	
	void print(double a[]) { //debug
		try {
			for(int i = 0; i < n; ++i)
				out.write(a[i] + " ");
			out.write("\n");out.flush();
		} catch(Exception e) {
			
		}
	}
	
	double work() {
		floyd();
		vis = new boolean[n];
		mindis = new double[n];
		maxdis = new double[n];
		for(int i = 0; i < n; ++i) if(!vis[i])
			make_mnmxdis(i);
		
		double res = Double.MAX_VALUE;
		for(int u = 0; u < n; ++u) {
			for(int v = 0; v < n; ++v) if(dis[u][v] == 1e100) {
				double tmp = Math.max(mindis[u], mindis[v]);
				tmp = Math.max(tmp, maxdis[u] + get_dis(u, v) + maxdis[v]);
				res = Math.min(res, tmp);
				//out.write(cbuf);
			}
		}
		return res;
	}
	
	void solve() throws Exception{
		in = new BufferedReader(new FileReader("cowtour.in")); out = new BufferedWriter(new FileWriter("cowtour.out"));
		//in = new BufferedReader(new InputStreamReader(System.in)); out = new BufferedWriter(new OutputStreamWriter(System.out));
		
		n = nextInt();
		x = new int[n];
		y = new int[n];
		dis = new double[n][n];
		mat = new double[n][n];
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j) mat[i][j] = dis[i][j] = (i == j ? 0 : 1e100);
		
		for(int i = 0; i < n; ++i) {
			x[i] = nextInt(); y[i] = nextInt();
		}
		for(int i = 0; i < n; ++i) {
			char c[] = in.readLine().toCharArray();
			for(int j = 0; j < n; ++j)
				if(c[j] == '1') mat[i][j] = dis[i][j] = get_dis(i, j);
		}
		out.write(String.format("%.6f\n", work()));
		out.flush();
	}
	
	String nextString() throws Exception{
		while(tokenizer == null || !tokenizer.hasMoreTokens())
			tokenizer = new StringTokenizer(in.readLine());
		return tokenizer.nextToken();
	}
	
	int nextInt() throws Exception {
		return Integer.parseInt(nextString());
	}
	
	public static void main(String args[]) throws Exception{
		new cowtour().solve();
	}
}
 