////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-08-12 15:53:24
////Compiler: Java
//////////////////////////////////////////////////////
////Problem ID: 4570
////Problem Title: 
////Run result: Accept
////Run time:187MS
////Run memory:5564KB
//////////////////System Comment End//////////////////
import java.io.*;
import java.util.*;

public class Main {
	static final int MAXN = 70;
	static final int MAXS = 20;

	long dp[], a[];
	int T, n;
	
	Main() {
		dp = new long[MAXN];
		a = new long[MAXN];
	}
	
	long solve() {
		for(int i = 1; i <= n; ++i) dp[i] = ~(1L << 63);
		for(int i = 1; i <= n; ++i) {
			for(int j = Math.max(1, i - MAXS + 1); j <= i; ++j) {
				dp[i] = Math.min(dp[i], dp[j - 1] + (a[j] << (i - j + 1)));
			}
		}
		return dp[n];
	}
	
	void work() {
		Scanner cin = new Scanner(new BufferedInputStream(System.in));
		T = cin.nextInt();
		while(T-- != 0) {
			n = cin.nextInt();
			for(int i = 1; i <= n; ++i) a[i] = cin.nextLong();
			System.out.println(solve());
		}
		cin.close();
	}
	
	public static void main(String args[]) {
		new Main().work();
	}
}
