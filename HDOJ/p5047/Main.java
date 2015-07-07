////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-09-27 22:12:38
////Compiler: Java
//////////////////////////////////////////////////////
////Problem ID: 5047
////Problem Title: 
////Run result: Accept
////Run time:484MS
////Run memory:3236KB
//////////////////System Comment End//////////////////
import java.util.*;
import java.math.*;
import java.io.*;

public class Main {
	static final int MAXN = 33;
	static BufferedWriter out = new BufferedWriter(new OutputStreamWriter(System.out));
	
	Main() {
	}
	
	void solve() throws Exception{
		InputReader cin = new InputReader(new BufferedInputStream(System.in));
		BigInteger Seven = BigInteger.valueOf(7);
		
		int T = cin.nextInt();
		for(int t = 1; t <= T; ++t) {
			BigInteger n = cin.nextBigInteger();
			BigInteger ans = n.shiftLeft(3).subtract(Seven).multiply(n).add(BigInteger.ONE);
			out.write("Case #" + t + ": ");
			out.write(ans.toString());
			out.newLine();
		}
		out.flush();
	}
	
	public static void main(String args[]) throws Exception{
		new Main().solve();
	}
}

class InputReader {
    private BufferedReader reader;
    private StringTokenizer tokenizer;

    public InputReader(InputStream inputStream) {
        reader = new BufferedReader(new InputStreamReader(inputStream));
    }

    public String nextLine() {
        String line = null;
        try {
            line = reader.readLine();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        return line;
    }

    public String next() {
        while (tokenizer == null || !tokenizer.hasMoreTokens())
            tokenizer = new StringTokenizer(nextLine());
        return tokenizer.nextToken();
    }

    public int nextInt() {
        return Integer.parseInt(next());
    }
    
    public BigInteger nextBigInteger() {
    	return new BigInteger(next());
    }
}