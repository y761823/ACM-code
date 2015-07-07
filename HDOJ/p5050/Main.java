////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-09-27 23:38:18
////Compiler: Java
//////////////////////////////////////////////////////
////Problem ID: 5050
////Problem Title: 
////Run result: Accept
////Run time:187MS
////Run memory:5668KB
//////////////////System Comment End//////////////////
import java.util.*;
import java.math.*;
import java.io.*;

public class Main {
    static final int MAXN = 33;
    
    Main() {
    }
    
    void solve() {
        //test();
        Scanner cin = new Scanner(new BufferedInputStream(System.in));
        int T = cin.nextInt();
        for(int t = 1; t <= T; ++t) {
            BigInteger a = new BigInteger(cin.next(), 2);
            BigInteger b = new BigInteger(cin.next(), 2);
            BigInteger ans = a.gcd(b);
            System.out.println("Case #" + t + ": " + ans.toString(2));
        }
        cin.close();
    }
    
    public static void main(String args[]) {
        new Main().solve();
    }
}