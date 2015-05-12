// BEGIN CUT HERE

// END CUT HERE
import java.util.*;
import java.math.*;
public class CandyAddict {
	long work(long x, long y, long z) {
		if(x == y) return 0;
		Arrays.
		long t = 1, num, money = x;
		while(t <= z) {
			num = money / y;
			money -= num * y;
			if(t + num > z) {
				money += (z - t) * x;
				break;
			} else {
				long b = (x - y) * num, k = (y - money + b - 1) / b;
				if(t + num * k > z) k = (z - t) / num;
				t += k * num;
				money = (x - y) * (t - 1) + x;
				//if(true) return t;
			}
		}
		return money;
	}

	public long[] solve(int[] X, int[] Y, int[] Z) {
		long[] res = new long[X.length];
		for(int i = 0; i < X.length; ++i)
			res[i] = work(X[i], Y[i], Z[i]);
		return res;
	}
	
	public static void main(String[] args) {
		CandyAddict temp = new CandyAddict();
		Scanner in = new Scanner(System.in);
		System.out.println("Hello");
		in.close();
	}
}
