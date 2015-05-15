/*
ID: y7618231
LANG: JAVA
TASK: palsquare
 */
import java.util.*;
import java.math.*;
import java.io.*;

public class palsquare {
	static final int MAXN = 33;
	static BufferedReader in;
	static BufferedWriter out;
	
	palsquare() {
	}
	
	boolean check(int n, int B) {
		String s1 = Integer.toString(n, B);
		String s2 = new StringBuilder(s1).reverse().toString();
		return s1.equals(s2);
	}
	
	void solve() throws Exception{
		in = new BufferedReader(new FileReader("palsquare.in"));
		out = new BufferedWriter(new FileWriter("palsquare.out"));
		int B = Integer.parseInt(in.readLine());
		for(int i = 1; i <= 300; ++i) {
			if(check(i * i, B)) out.write(Integer.toString(i, B).toUpperCase() + " " + Integer.toString(i * i, B).toUpperCase() + "\n");
		}
		out.flush();
	}
	
	public static void main(String args[]) throws Exception{
		new palsquare().solve();
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