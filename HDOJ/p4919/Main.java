////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-09-02 17:20:35
////Compiler: Java
//////////////////////////////////////////////////////
////Problem ID: 4919
////Problem Title: 
////Run result: Accept
////Run time:265MS
////Run memory:5756KB
//////////////////System Comment End//////////////////
import java.util.*;
import java.math.*;
import java.io.*;

public class Main {
	static final int MAXN = 33;
	
	Main() {
	}
	
	void test() {
		BigInteger n = BigInteger.valueOf(15);
		for(BigInteger i = BigInteger.valueOf(1); !i.equals(n); i = i.add(BigInteger.valueOf(1))) {
			//System.out.println(n.subtract(i).toString(2) + " " + i.toString(2));
			System.out.println(n.subtract(i).xor(i).toString(2));
		}
	}
	
	void solve() {
		//test();
		Scanner cin = new Scanner(new BufferedInputStream(System.in));
		while(cin.hasNextBigInteger()) {
			BigInteger n = cin.nextBigInteger();
			String s = n.toString(2);
			BigInteger q = BigInteger.ZERO;
			BigInteger m = BigInteger.ONE;
			BigInteger ans = BigInteger.ZERO;
			boolean flag = n.bitCount() == 1;
			for(int i = 0; i < s.length(); ++i) {
				//if(i == s.length() - 1 && flag) break;
				int t = s.charAt(s.length() - i - 1) - '0';
				BigInteger cnt = n.divide(m);
				if(t == 1) {
					BigInteger p = q.add(BigInteger.ONE);
					ans = ans.add(p.multiply(cnt).multiply(m));
					if(cnt.testBit(0)) {
						BigInteger rest = n.subtract(m.multiply(cnt));
						if(rest.compareTo(p) > 0) rest = p;
						ans = ans.add(rest.multiply(m));
					}
					//System.out.println(q);
					q = q.add(m);
				} else {
					BigInteger p = m.subtract(q.add(BigInteger.ONE));
					//System.out.println(p);
					ans = ans.add(p.multiply(cnt).multiply(m));
					if(cnt.testBit(0)) {
						BigInteger rest = n.subtract(m.multiply(cnt));
						if(rest.compareTo(p) > 0) rest = p;
						ans = ans.add(rest.multiply(m));
					}
					//System.out.println(ans);
				}
				m = m.multiply(BigInteger.valueOf(2));
			}
			System.out.println(ans.subtract(n));
		}
		cin.close();
	}
	
	public static void main(String args[]) {
		new Main().solve();
	}
}