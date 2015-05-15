/*
ID: y7618231
LANG: JAVA
TASK: maze1
 */
import java.util.*;
import java.math.*;
import java.io.*;

public class maze1 {
	static final int MAXN = 110;
	static final int seed = 131;
	static final int MOD = 9901;
	static BufferedReader in;
	static BufferedWriter out;
	static StringTokenizer tokenizer;
	
	static final int fr[] = {-1, 0, 1, 0};
	static final int fc[] = {0, 1, 0, -1};
	
	int dis[][];
	char mat[][];
	int w, h;
	
	boolean check(int r, int c) {
		return 0 <= r && r < h && 0 <= c && c < w;
	}
	
	public class Node {
		int r, c;
		Node() {}
		Node(int _r, int _c) {
			r = _r; c = _c;
		}
		Node move(int f) {
			int nr = r + fr[f], nc = c + fc[f];
			if(mat[nr][nc] != ' ') return null;
			nr += fr[f]; nc += fc[f];
			if(check(nr, nc)) return new Node(nr, nc);
			return null;
		}
	}
	
	int work() {
		dis = new int[h][w];
		for(int i = 1; i < h; i += 2) {
			for(int j = 1; j < w; j += 2) {
				dis[i][j] = Integer.MAX_VALUE;
				if(i == 1 && mat[0][j] == ' ') dis[i][j] = 0;
				if(i == h - 2 && mat[h - 1][j] == ' ') dis[i][j] = 0;
				if(j == 1 && mat[i][0] == ' ') dis[i][j] = 0;
				if(j == w - 2 && mat[i][w - 1] == ' ') dis[i][j] = 0;
			}
		}
		
		Queue<Node> que = new LinkedList<Node>();
		for(int i = 1; i < h; i += 2)
			for(int j = 1; j < w; j += 2) if(dis[i][j] == 0)
				que.add(new Node(i, j));
		
		int res = 0;
		while(!que.isEmpty()) {
			Node a = que.poll();
			for(int f = 0; f < 4; ++f) {
				Node b = a.move(f);
				if(b != null && dis[b.r][b.c] == Integer.MAX_VALUE) {
					res = dis[b.r][b.c] = dis[a.r][a.c] + 1;
					que.add(b);
				}
			}
		}
		return res + 1;
	}
	
	void solve() throws Exception{
		in = new BufferedReader(new FileReader("maze1.in")); out = new BufferedWriter(new FileWriter("maze1.out"));
		//in = new BufferedReader(new InputStreamReader(System.in)); out = new BufferedWriter(new OutputStreamWriter(System.out));
		
		w = 2 * nextInt() + 1;
		h = 2 * nextInt() + 1;
		mat = new char[h][w];
		for(int i = 0; i < h; ++i)
			mat[i] = in.readLine().toCharArray();
		
		out.write(work() + "\n");
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
		new maze1().solve();
	}
}
 