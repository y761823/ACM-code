/*
ID: y7618231
LANG: JAVA
TASK: pprime
 */
import java.util.*;
import java.math.*;
import java.io.*;

public class pprime {
	static final int MAXN = 1010;
	static BufferedReader in;
	static BufferedWriter out;
	static StringTokenizer tokenizer;

	int a, b;
	
	void judge(int x) throws IOException {
		if(x < a || x > b) return ;
		for(int i = 2; i * i <= x; ++i)
			if(x % i == 0) return ;
		out.write(x + "\n");
	}
	
	void solve() throws Exception{
		in = new BufferedReader(new FileReader("pprime.in")); out = new BufferedWriter(new FileWriter("pprime.out"));
		//in = new BufferedReader(new InputStreamReader(System.in)); out = new BufferedWriter(new OutputStreamWriter(System.out));
		
		tokenizer = new StringTokenizer(in.readLine());
		a = Integer.parseInt(tokenizer.nextToken());
		b = Integer.parseInt(tokenizer.nextToken());
		
		for(int i = 1; i <= 9; i += 2)
			judge(i);
		for(int i = 1; i <= 9; i += 2)
			judge(i * 10 + i);

		for(int i = 1; i <= 9; i += 2)
			for(int j = 0; j <= 9; ++j) judge(i * 100 + j * 10 + i);
		for(int i = 1; i <= 9; i += 2)
			for(int j = 0; j <= 9; ++j) judge(i * 1000 + j * 100 + j * 10 + i);
		

		for(int i = 1; i <= 9; i += 2)
			for(int j = 0; j <= 9; ++j)
				for(int k = 0; k <= 9; ++k) judge(i * 10000 + j * 1000 + k * 100 + j * 10 + i);
		for(int i = 1; i <= 9; i += 2)
			for(int j = 0; j <= 9; ++j)
				for(int k = 0; k <= 9; ++k) judge(i * 100000 + j * 10000 + k * 1000 + k * 100 + j * 10 + i);

		for(int i = 1; i <= 9; i += 2)
			for(int j = 0; j <= 9; ++j)
				for(int k = 0; k <= 9; ++k)
					for(int l = 0; l <= 9; ++l) judge(i * 1000000 + j * 100000 + k * 10000 + l * 1000 + k * 100 + j * 10 + i);
		for(int i = 1; i <= 9; i += 2)
			for(int j = 0; j <= 9; ++j)
				for(int k = 0; k <= 9; ++k)
					for(int l = 0; l <= 9; ++l) judge(i * 10000000 + j * 1000000 + k * 100000 + l * 10000 + l * 1000 + k * 100 + j * 10 + i);
		
		out.flush();
	}
	
	public static void main(String args[]) throws Exception{
		new pprime().solve();
	}
}
