// BEGIN CUT HERE

// END CUT HERE
import java.util.*;
public class BishopMove {
	static final int n = 8;
	static final int INF = 0x3f3f3f3f;
	static final int fx[] = {1, 1, -1, -1};
	static final int fy[] = {1, -1, 1, -1};
	
	public class Node {
		int r, c;
		Node() {}
		Node(int r, int c) {
			this.r = r;
			this.c = c;
		}
	}
	
	boolean check(int x) {
		return 0 <= x && x < n;
	}
	
	boolean check(int r, int c) {
		return check(r) && check(c);
	}
	
	int sgn(int x) {
		return x > 0 ? 1 : -1;
	}
	
	public int howManyMoves(int r1, int c1, int r2, int c2) {
		int dis[][] = new int[n][n];
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j) dis[i][j] = INF;
		dis[r1][c1] = 0;
		Queue<Node> que = new LinkedList<Node>();
		que.offer(new Node(r1, c1));
		while(!que.isEmpty()) {
			Node t = que.poll();
			for(int f = 0; f < 4; ++f) {
				for(int i = 1; i < n; ++i) {
					int nr = t.r + i * fx[f], nc = t.c + i * fy[f];
					if(!check(nr, nc)) break;
					if(dis[t.r][t.c] + 1 < dis[nr][nc]) {
						dis[nr][nc] = dis[t.r][t.c] + 1;
						que.offer(new Node(nr, nc));
					}
				}
			}
		}
		if(dis[r2][c2] == INF) return -1;
		return dis[r2][c2];
	}

	public static void main(String[] args) {
		BishopMove temp = new BishopMove();
		Scanner in = new Scanner(System.in);
		System.out.println(temp.howManyMoves(4, 6, 7, 3));
		in.close();
	}
}
